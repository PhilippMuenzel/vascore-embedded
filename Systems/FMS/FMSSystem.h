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


#ifndef FMSSystem_h
#define FMSSystem_h

#include <memory>
#include <cstdlib>
#include "FMSDatabase.h"
#include "FMSPad.h"
#include "FMSIRS.h"
#include "FMSPref.h"
#include "../../Library/FMS/flightroute.h"
#include "../../Library/FMS/icaoroute.h"
#include "../../Library/FMS/airport.h"
#include "../../Library/FMS/MProjection.h"
#include "../../Library/FMS/projection_greatcircle.h"
#include "../../../CRJ/Systems/FMS/IFMSSystem.h"
#include "../../Library/Dataref/DInteger.h"


class FMSSystem : public IFMSSystem {
public:
    FMSSystem();
    ~FMSSystem();

    void update();

    FMSIRS* irs() { return m_fms_irs.get(); }
    FMSPad* pad() { return m_fms_pad.get(); }
    FMSDatabase* data() { return m_fms_database.get(); }
    FMSPref* pref() { return m_fms_pref.get(); }

    bool isHoldPrepareLeft() const { return hold_prepare_left; }
    void setHoldPrepareLeft(bool b) { hold_prepare_left = b; }

    void setCDUPage(CDUPages page) { m_cdu_page = page; }
    CDUPages cduPage() { return m_cdu_page; }
    void setLastCDUPage(CDUPages page) { m_last_cdu_page = page; }
    CDUPages lastCDUPage() { return m_last_cdu_page; }

    void setDepPage(int value) { m_dep_arr_page = value; }
    int depPage() { return m_dep_arr_page; }
    void setLegsPage(int value) { m_legs_page = value; }
    int legsPage() { return m_legs_page; }
    void setWptSelPage(int value) { m_wpt_sel_page = value; }
    int wptSelPage() { return m_wpt_sel_page; }
    void setFpln2Page(int value) { m_fpln2_page = value; }
    int fpln2Page() { return m_fpln2_page; }

    FlightRoute* route() { return m_flight_route; }

    void setTempWptList(StdWaypointList list_to_copy) { m_wpt_list = list_to_copy; }
    void setTempWptListIndex(int index_to_copy) { m_wpt_index = index_to_copy; }
    StdWaypointList tempWptList() { return m_wpt_list; }
    int tempWptListIndex() { return m_wpt_index; }
    void clearTempWptList() { m_wpt_list.clear(); m_wpt_index = -1; }

    bool isExec();

    // x-plane fms
    float fmsHeading() { return x_fms_hdg.get(); }
    float fmsDeflection() { return x_fms_def.get(); }

    float distanceToActiveWptNm() const { return m_distanceToActiveWptNm; }
    float distanceFromPreviousWptNm() const { return m_distanceFromPreviousWptNm; }
    float trueTrackToActiveWpt() const { return m_trueTrackToActiveWpt; }
    float hoursToActiveWpt() const { return m_hoursToActiveWpt; }
    float crossTrackDistanceNm() const { return m_crossTrackDistanceNm; }

    // mfd
    StdWaypointList getVorList(int zoom);
    StdWaypointList getFixList(int zoom);
    StdWaypointList getNdbList(int zoom);
    StdWaypointList getAptList(int zoom);

private:

    std::auto_ptr<FMSDatabase> m_fms_database;
    std::auto_ptr<FMSIRS> m_fms_irs;
    std::auto_ptr<FMSPad> m_fms_pad;
    std::auto_ptr<FMSPref> m_fms_pref;

    FlightRoute *m_flight_route;
    FlightRoute *m_saved_route;
    //ICAORoute *m_icao_route;

    CDUPages m_cdu_page;
    CDUPages m_last_cdu_page;
    int m_dep_arr_page;
    int m_legs_page;
    int m_wpt_sel_page;
    int m_fpln2_page;

    // temp
    StdWaypointList m_wpt_list;
    int m_wpt_index;

    // x-plane
    DFloat x_fms_hdg;
    DFloat x_fms_def;

    float m_distanceToActiveWptNm;
    float m_distanceFromPreviousWptNm;
    float m_trueTrackToActiveWpt;
    float m_hoursToActiveWpt;
    float m_crossTrackDistanceNm;

    // mfd
    StdWaypointList m_defined_vor_list;
    StdWaypointList m_defined_fix_list;
    StdWaypointList m_defined_apt_list;
    StdWaypointList m_defined_ndb_list;
    int m_last_vor_zoom;
    int m_last_fix_zoom;
    int m_last_apt_zoom;
    int m_last_ndb_zoom;
    Waypoint m_last_vor_pos;
    Waypoint m_last_fix_pos;
    Waypoint m_last_apt_pos;
    Waypoint m_last_ndb_pos;

    DFloat ground_speed;
    DFloat true_heading;
    DFloat true_track;
    DFloat altimeter_readout;
    DInteger zulu_hours;
    DInteger zulu_minutes;
    DInteger onground;

    DInteger advance_override;
    DInteger nav_override;
    DFloat nav_override_crs;
    DFloat time_sec;
    DFloat hdg;
    float timer_start;

    bool hold_prepare_left;
};

#endif /* FMSSystem_h */
