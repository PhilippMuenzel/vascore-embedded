///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2005-2011 Alexander Wemmer, Philipp Münzel and Anton Volkov
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
///////////////////////////////////////////////////////////////////////////////



#include "FMSSystem.h"
#include "../../Library/FMS/navcalc.h"
#include "XPLMUtilities.h"
#include "XPLMNavigation.h"

FMSSystem::FMSSystem():
    m_fms_database(new FMSDatabase),
    m_fms_irs(new FMSIRS),
    m_fms_pad(new FMSPad),
    m_fms_pref(new FMSPref),
    hold_prepare_left(true)
{
    m_fms_database->load();
    m_cdu_page = cdu_page_index;

    m_dep_arr_page = 0;
    m_legs_page = 0;
    m_wpt_sel_page = 0;
    m_fpln2_page = 0;

    x_fms_hdg.find(X_FMS_HDG);
    x_fms_def.find(X_FMS_DEF);

    ground_speed.find("sim/flightmodel/position/groundspeed");
    true_heading.find("sim/flightmodel/position/psi");
    true_track.find("sim/flightmodel/position/hpath");
    altimeter_readout.find("sim/cockpit2/gauges/indicators/altitude_ft_pilot");
    zulu_hours.find("sim/cockpit2/clock_timer/zulu_time_hours");
    zulu_minutes.find("sim/cockpit2/clock_timer/zulu_time_minutes");
    onground.find("sim/flightmodel/failures/onground_any");

    time_sec.find("sim/time/zulu_time_sec");
    advance_override.find("sim/operation/override/override_fms_advance");
    nav_override_crs.find("sim/cockpit/autopilot/nav_steer_deg_mag");
    nav_override.find("sim/operation/override/override_nav_heading");
    hdg.find("sim/flightmodel/position/magpsi");

    m_flight_route = new FlightRoute();
    m_saved_route = m_flight_route;
    //m_icao_route = new ICAORoute();

    m_last_apt_zoom = -1;
    m_last_vor_zoom = -1;
    m_last_ndb_zoom = -1;
    m_last_fix_zoom = -1;
    m_last_vor_pos = Waypoint("", "", 0.0, 0.0);
    m_last_fix_pos = Waypoint("", "", 0.0, 0.0);
    m_last_apt_pos = Waypoint("", "", 0.0, 0.0);
    m_last_ndb_pos = Waypoint("", "", 0.0, 0.0);
    advance_override.set(1);
};

FMSSystem::~FMSSystem()
{
    advance_override.set(0);
}


void FMSSystem::update()
{

    Waypoint* active_wpt = route()->activeWaypoint();
    const Waypoint* prev_wpt = route()->previousWaypoint();
    //const Waypoint* next_wpt = route()->nextWaypoint();

    if (ground_speed.get()*Navcalc::METER_PER_SECOND_TO_KNOTS > 40)
        advance_override.set(0);
    else
        advance_override.set(1);

    if (active_wpt)
    {
        m_distanceToActiveWptNm =
                Navcalc::getDistBetweenWaypoints(*irs()->position(), *active_wpt);

        m_trueTrackToActiveWpt =
                Navcalc::getTrackBetweenWaypoints(*irs()->position(), *active_wpt);
    }
    if (prev_wpt)
        m_distanceFromPreviousWptNm =
                Navcalc::getDistBetweenWaypoints(*irs()->position(), *prev_wpt);

    if (ground_speed.get() < 30.0)
        m_hoursToActiveWpt = 0.0;
    else
        m_hoursToActiveWpt = m_distanceToActiveWptNm / (ground_speed.get()*Navcalc::METER_PER_SECOND_TO_KNOTS);

    if (active_wpt && !active_wpt->holding().isValid())
    {
        static int last_dest = XPLMGetDestinationFMSEntry();

        if (last_dest < XPLMGetDestinationFMSEntry())
        {
            QTime overflown(zulu_hours.get(), zulu_minutes.get());
            if (route()->nextWaypoint())
                route()->switchToNextWaypoint(overflown);
        }
        last_dest = XPLMGetDestinationFMSEntry();
    }

    if (active_wpt &&
            active_wpt->holding().isValid())
    {
        advance_override.set(1);
        if (m_distanceToActiveWptNm < 0.5 && nav_override.get() == 0)
        {
            timer_start = time_sec.get();
            nav_override.set(1);
        }
        if (nav_override.get() && (time_sec.get() - timer_start < 10)) {
            if (active_wpt->holding().isLeftHolding())
                nav_override_crs.set(hdg.get() - 6);
            else
                nav_override_crs.set(hdg.get() + 6);
        } else if (nav_override.get() && (time_sec.get() - timer_start > 10 && time_sec.get() - timer_start < 180))
            nav_override_crs.set(active_wpt->holding().holdingOutTrack());
        else if (nav_override.get() && (time_sec.get() - timer_start > 180 && time_sec.get() - timer_start < 190))
        {
            if (active_wpt->holding().isLeftHolding())
                nav_override_crs.set(hdg.get() - 6);
            else
                nav_override_crs.set(hdg.get() + 6);
        } else if (nav_override.get() && (time_sec.get() - timer_start < 240))
            nav_override_crs.set(active_wpt->holding().holdingTrack());
        else if (nav_override.get() && (time_sec.get() - timer_start > 360) && active_wpt->holding().isActive())
        {
            nav_override_crs.set(active_wpt->holding().holdingOutTrack());
            timer_start = time_sec.get();
        } else if (nav_override.get() && (time_sec.get() - timer_start > 360) && !active_wpt->holding().isActive())
        {
            nav_override.set(0);
            advance_override.set(0);
            active_wpt->setHolding(Holding());
        }
    }


    route()->resetAndRecalcSpecialWaypoints();
};

bool FMSSystem::isExec() {
    return (m_saved_route != m_flight_route);
}

StdWaypointList FMSSystem::getVorList(int zoom)
{
    if (m_last_vor_zoom != zoom ||
            Navcalc::getDistBetweenWaypoints(m_last_vor_pos, *irs()->position()) > zoom/10) {
        m_defined_vor_list.clear();
        data()->getVorByCoordinates(*irs()->position(), zoom, &m_defined_vor_list);
        m_last_vor_zoom = zoom;
        m_last_vor_pos = *irs()->position();
    }
    return m_defined_vor_list;
}

StdWaypointList FMSSystem::getFixList(int zoom)
{
    if (m_last_fix_zoom != zoom ||
            Navcalc::getDistBetweenWaypoints(m_last_fix_pos, *irs()->position()) > zoom/10) {
        m_defined_fix_list.clear();
        data()->getFixByCoordinates(*irs()->position(), zoom, &m_defined_fix_list);
        m_last_fix_zoom = zoom;
        m_last_fix_pos = *irs()->position();
    }
    return m_defined_fix_list;
}

StdWaypointList FMSSystem::getAptList(int zoom)
{
    if (m_last_apt_zoom != zoom ||
            Navcalc::getDistBetweenWaypoints(m_last_apt_pos, *irs()->position()) > zoom/10) {
        m_defined_apt_list.clear();
        data()->getAptByCoordinates(*irs()->position(), zoom, &m_defined_apt_list);
        m_last_apt_zoom = zoom;
        m_last_apt_pos = *irs()->position();
    }
    return m_defined_apt_list;
}

StdWaypointList FMSSystem::getNdbList(int zoom)
{
    if (m_last_ndb_zoom != zoom ||
            Navcalc::getDistBetweenWaypoints(m_last_ndb_pos, *irs()->position()) > zoom/10) {
        m_defined_ndb_list.clear();
        data()->getNdbByCoordinates(*irs()->position(), zoom, &m_defined_ndb_list);
        m_last_ndb_zoom = zoom;
        m_last_ndb_pos = *irs()->position();
    }
    return m_defined_ndb_list;
}
