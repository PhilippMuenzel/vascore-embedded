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


#include "FMSIRS.h"
#include <XPLMUtilities.h>


FMSIRS::FMSIRS()
{
    m_irs_1 = irs_off;
    m_irs_2 = irs_off;

    x_gps_position_lat.find(X_LATITUDE);
    x_gps_position_lon.find(X_LONGITUDE);

    m_time_counter = 0;

    m_irs_position = new Waypoint("PLANE", "", x_gps_position_lat.get(), x_gps_position_lon.get());
};

void FMSIRS::setUserPosition(Waypoint *wpt)
{
    m_user_position = wpt;
    setIrs1Status(irs_in_align1);
    setIrs2Status(irs_in_align1);
};

void FMSIRS::update()
{
    //if (irs1Status() < irs_in_align2) {
    m_irs_position->setLat(x_gps_position_lat.get());
    m_irs_position->setLon(x_gps_position_lon.get());
    //}
    if (irs1Status() == irs_in_align1 || irs1Status() == irs_in_align2) {
        m_time_counter++;
    }
    if (m_time_counter == 1120) {
        setIrs1Status(irs_in_align2);
        setIrs2Status(irs_in_align2);
    }
    if (m_time_counter == 1920) {
        setIrs1Status(irs_on);
        setIrs2Status(irs_on);
        m_time_counter = 0;
    }

    // DEBUG
    //char de[128];
    //sprintf(de, "%d\n", m_time_counter);
    //XPLMDebugString(de);
};

