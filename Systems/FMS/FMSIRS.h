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


#ifndef FMSIRS_h
#define FMSIRS_h

#include <stdlib.h>
#include "FMSData.h"
#include "../../Library/Dataref/DFloat.h"
#include "../../Library/FMS/waypoint.h"

#include "../../../CRJ/Systems/FMS/IFMSIRS.h"

class FMSIRS : public IFMSIRS{
public:

    FMSIRS();
    IRSStatus irs1Status() { return m_irs_1; }
    IRSStatus irs2Status() { return m_irs_2; }
    void setIrs1Status(IRSStatus value) { m_irs_1 = value; if (value == irs_off) m_time_counter = 0; }
    void setIrs2Status(IRSStatus value) { m_irs_2 = value; if (value == irs_off) m_time_counter = 0; }

    Waypoint* position() { return m_irs_position; }
    Waypoint* userPosition() { return m_user_position; }
    void setUserPosition(Waypoint *wpt);

    void update();

private:
    static FMSIRS* instance;

    IRSStatus m_irs_1;
    IRSStatus m_irs_2;

    DFloat x_gps_position_lat;
    DFloat x_gps_position_lon;

    Waypoint *m_irs_position;
    Waypoint *m_user_position;

    int m_time_counter;
};

#endif /* FMSIRS_h */
