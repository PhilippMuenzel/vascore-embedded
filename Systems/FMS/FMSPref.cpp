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


#include "FMSPref.h"
#include "../../Library/FMS/navcalc.h"

#define VS_INDEX  0.278483297397047

FMSPref::FMSPref()
{
    m_to_thrust = 0.0;
    m_ga_thrust = 0.0;
    m_clb_thrust = 0.0;
    m_crz_thrust = 0.0;
    m_tgt_thrust = 0.0;
    m_mct_thrust = 0.0;

    m_thrust_oat = -4000;

    m_thrust_limit = thrust_none;
    m_eng_bleed = bleed_off;

    initThrustLimits();

    m_bow = 30500.0f;
    m_pass_number = -1.0f;
    m_pass_weight = 0.0f;
    m_one_pass_weight = 170.0f;
    m_default_pass_weight = 170.0f;
    m_cargo = -1.0f;
    m_zfw = 0.0f;
    m_fuel = 0.0f;
    m_gwt = 0.0f;
};

/////////////////////////////////////

void FMSPref::initThrustLimits()
{
    Thrust_Limit limit;

    /// -40
    {
        // 0"
        limit.altitude = 0;
        limit.temperature = -40;
        limit.thrust = 81.2f;
        thr_limit.push_back(limit);
        // 1000"
        limit.altitude = 1000;
        limit.temperature = -40;
        limit.thrust = 81.6;
        thr_limit.push_back(limit);
        // 2000"
        limit.altitude = 2000;
        limit.temperature = -40;
        limit.thrust = 82.0;
        thr_limit.push_back(limit);
        // 3000"
        limit.altitude = 3000;
        limit.temperature = -40;
        limit.thrust = 82.4;
        thr_limit.push_back(limit);
        // 4000"
        limit.altitude = 4000;
        limit.temperature = -40;
        limit.thrust = 82.8;
        thr_limit.push_back(limit);
        // 5000"
        limit.altitude = 5000;
        limit.temperature = -40;
        limit.thrust = 83.3;
        thr_limit.push_back(limit);
        // 6000"
        limit.altitude = 6000;
        limit.temperature = -40;
        limit.thrust = 83.8;
        thr_limit.push_back(limit);
        // 7000"
        limit.altitude = 7000;
        limit.temperature = -40;
        limit.thrust = 84.3;
        thr_limit.push_back(limit);
        // 8000"
        limit.altitude = 8000;
        limit.temperature = -40;
        limit.thrust = 85.8;
        thr_limit.push_back(limit);
        // 10000"
        limit.altitude = 10000;
        limit.temperature = -40;
        limit.thrust = 85.7;
        thr_limit.push_back(limit);
    }
    /// -35
    {
        // 0"
        limit.altitude = 0;
        limit.temperature = -35;
        limit.thrust = 82.0;
        thr_limit.push_back(limit);
        // 1000"
        limit.altitude = 1000;
        limit.temperature = -35;
        limit.thrust = 82.5;
        thr_limit.push_back(limit);
        // 2000"
        limit.altitude = 2000;
        limit.temperature = -35;
        limit.thrust = 82.9;
        thr_limit.push_back(limit);
        // 3000"
        limit.altitude = 3000;
        limit.temperature = -35;
        limit.thrust = 83.3;
        thr_limit.push_back(limit);
        // 4000"
        limit.altitude = 4000;
        limit.temperature = -35;
        limit.thrust = 83.7;
        thr_limit.push_back(limit);
        // 5000"
        limit.altitude = 5000;
        limit.temperature = -35;
        limit.thrust = 84.2;
        thr_limit.push_back(limit);
        // 6000"
        limit.altitude = 6000;
        limit.temperature = -35;
        limit.thrust = 84.7;
        thr_limit.push_back(limit);
        // 7000"
        limit.altitude = 7000;
        limit.temperature = -35;
        limit.thrust = 85.1;
        thr_limit.push_back(limit);
        // 8000"
        limit.altitude = 8000;
        limit.temperature = -35;
        limit.thrust = 85.6;
        thr_limit.push_back(limit);
        // 10000"
        limit.altitude = 10000;
        limit.temperature = -35;
        limit.thrust = 86.6;
        thr_limit.push_back(limit);
    }
    /// -30
    {
        // 0"
        limit.altitude = 0;
        limit.temperature = -30;
        limit.thrust = 82.9;
        thr_limit.push_back(limit);
        // 1000"
        limit.altitude = 1000;
        limit.temperature = -30;
        limit.thrust = 83.3;
        thr_limit.push_back(limit);
        // 2000"
        limit.altitude = 2000;
        limit.temperature = -30;
        limit.thrust = 83.7;
        thr_limit.push_back(limit);
        // 3000"
        limit.altitude = 3000;
        limit.temperature = -30;
        limit.thrust = 84.1;
        thr_limit.push_back(limit);
        // 4000"
        limit.altitude = 4000;
        limit.temperature = -30;
        limit.thrust = 84.6;
        thr_limit.push_back(limit);
        // 5000"
        limit.altitude = 5000;
        limit.temperature = -30;
        limit.thrust = 85.0;
        thr_limit.push_back(limit);
        // 6000"
        limit.altitude = 6000;
        limit.temperature = -30;
        limit.thrust = 85.5;
        thr_limit.push_back(limit);
        // 7000"
        limit.altitude = 7000;
        limit.temperature = -30;
        limit.thrust = 86.0;
        thr_limit.push_back(limit);
        // 8000"
        limit.altitude = 8000;
        limit.temperature = -30;
        limit.thrust = 86.5;
        thr_limit.push_back(limit);
        // 10000"
        limit.altitude = 10000;
        limit.temperature = -30;
        limit.thrust = 87.6;
        thr_limit.push_back(limit);
    }
    /// -25
    {
        // 0"
        limit.altitude = 0;
        limit.temperature = -25;
        limit.thrust = 83.7;
        thr_limit.push_back(limit);
        // 1000"
        limit.altitude = 1000;
        limit.temperature = -25;
        limit.thrust = 84.1;
        thr_limit.push_back(limit);
        // 2000"
        limit.altitude = 2000;
        limit.temperature = -25;
        limit.thrust = 84.6;
        thr_limit.push_back(limit);
        // 3000"
        limit.altitude = 3000;
        limit.temperature = -25;
        limit.thrust = 85.0;
        thr_limit.push_back(limit);
        // 4000"
        limit.altitude = 4000;
        limit.temperature = -25;
        limit.thrust = 85.4;
        thr_limit.push_back(limit);
        // 5000"
        limit.altitude = 5000;
        limit.temperature = -25;
        limit.thrust = 85.9;
        thr_limit.push_back(limit);
        // 6000"
        limit.altitude = 6000;
        limit.temperature = -25;
        limit.thrust = 86.4;
        thr_limit.push_back(limit);
        // 7000"
        limit.altitude = 7000;
        limit.temperature = -25;
        limit.thrust = 86.9;
        thr_limit.push_back(limit);
        // 8000"
        limit.altitude = 8000;
        limit.temperature = -25;
        limit.thrust = 87.4;
        thr_limit.push_back(limit);
        // 10000"
        limit.altitude = 10000;
        limit.temperature = -25;
        limit.thrust = 88.4;
        thr_limit.push_back(limit);
    }
    /// -20
    {
        // 0"
        limit.altitude = 0;
        limit.temperature = -20;
        limit.thrust = 84.5;
        thr_limit.push_back(limit);
        // 1000"
        limit.altitude = 1000;
        limit.temperature = -20;
        limit.thrust = 85.0;
        thr_limit.push_back(limit);
        // 2000"
        limit.altitude = 2000;
        limit.temperature = -20;
        limit.thrust = 85.3;
        thr_limit.push_back(limit);
        // 3000"
        limit.altitude = 3000;
        limit.temperature = -20;
        limit.thrust = 85.8;
        thr_limit.push_back(limit);
        // 4000"
        limit.altitude = 4000;
        limit.temperature = -20;
        limit.thrust = 86.2;
        thr_limit.push_back(limit);
        // 5000"
        limit.altitude = 5000;
        limit.temperature = -20;
        limit.thrust = 86.7;
        thr_limit.push_back(limit);
        // 6000"
        limit.altitude = 6000;
        limit.temperature = -20;
        limit.thrust = 87.2;
        thr_limit.push_back(limit);
        // 7000"
        limit.altitude = 7000;
        limit.temperature = -20;
        limit.thrust = 87.8;
        thr_limit.push_back(limit);
        // 8000"
        limit.altitude = 8000;
        limit.temperature = -20;
        limit.thrust = 88.3;
        thr_limit.push_back(limit);
        // 10000"
        limit.altitude = 10000;
        limit.temperature = -20;
        limit.thrust = 89.3;
        thr_limit.push_back(limit);
    }
    /// -15
    {
        // 0"
        limit.altitude = 0;
        limit.temperature = -15;
        limit.thrust = 85.1;
        thr_limit.push_back(limit);
        // 1000"
        limit.altitude = 1000;
        limit.temperature = -15;
        limit.thrust = 85.7;
        thr_limit.push_back(limit);
        // 2000"
        limit.altitude = 2000;
        limit.temperature = -15;
        limit.thrust = 86.2;
        thr_limit.push_back(limit);
        // 3000"
        limit.altitude = 3000;
        limit.temperature = -15;
        limit.thrust = 86.6;
        thr_limit.push_back(limit);
        // 4000"
        limit.altitude = 4000;
        limit.temperature = -15;
        limit.thrust = 87.1;
        thr_limit.push_back(limit);
        // 5000"
        limit.altitude = 5000;
        limit.temperature = -15;
        limit.thrust = 87.6;
        thr_limit.push_back(limit);
        // 6000"
        limit.altitude = 6000;
        limit.temperature = -15;
        limit.thrust = 88.1;
        thr_limit.push_back(limit);
        // 7000"
        limit.altitude = 7000;
        limit.temperature = -15;
        limit.thrust = 88.6;
        thr_limit.push_back(limit);
        // 8000"
        limit.altitude = 8000;
        limit.temperature = -15;
        limit.thrust = 89.1;
        thr_limit.push_back(limit);
        // 10000"
        limit.altitude = 10000;
        limit.temperature = -15;
        limit.thrust = 90.2;
        thr_limit.push_back(limit);
    }
    /// -10
    {
        // 0"
        limit.altitude = 0;
        limit.temperature = -10;
        limit.thrust = 81.1;
        thr_limit.push_back(limit);
        // 1000"
        limit.altitude = 1000;
        limit.temperature = -10;
        limit.thrust = 86.6;
        thr_limit.push_back(limit);
        // 2000"
        limit.altitude = 2000;
        limit.temperature = -10;
        limit.thrust = 87.0;
        thr_limit.push_back(limit);
        // 3000"
        limit.altitude = 3000;
        limit.temperature = -10;
        limit.thrust = 87.5;
        thr_limit.push_back(limit);
        // 4000"
        limit.altitude = 4000;
        limit.temperature = -10;
        limit.thrust = 87.9;
        thr_limit.push_back(limit);
        // 5000"
        limit.altitude = 5000;
        limit.temperature = -10;
        limit.thrust = 88.4;
        thr_limit.push_back(limit);
        // 6000"
        limit.altitude = 6000;
        limit.temperature = -10;
        limit.thrust = 88.9;
        thr_limit.push_back(limit);
        // 7000"
        limit.altitude = 7000;
        limit.temperature = -10;
        limit.thrust = 89.5;
        thr_limit.push_back(limit);
        // 8000"
        limit.altitude = 8000;
        limit.temperature = -10;
        limit.thrust = 90.0;
        thr_limit.push_back(limit);
        // 10000"
        limit.altitude = 10000;
        limit.temperature = -10;
        limit.thrust = 91.1;
        thr_limit.push_back(limit);
    }
    /// -5
    {
        // 0"
        limit.altitude = 0;
        limit.temperature = -5;
        limit.thrust = 86.9;
        thr_limit.push_back(limit);
        // 1000"
        limit.altitude = 1000;
        limit.temperature = -5;
        limit.thrust = 87.4;
        thr_limit.push_back(limit);
        // 2000"
        limit.altitude = 2000;
        limit.temperature = -5;
        limit.thrust = 87.8;
        thr_limit.push_back(limit);
        // 3000"
        limit.altitude = 3000;
        limit.temperature = -5;
        limit.thrust = 88.3;
        thr_limit.push_back(limit);
        // 4000"
        limit.altitude = 4000;
        limit.temperature = -5;
        limit.thrust = 88.8;
        thr_limit.push_back(limit);
        // 5000"
        limit.altitude = 5000;
        limit.temperature = -5;
        limit.thrust = 89.3;
        thr_limit.push_back(limit);
        // 6000"
        limit.altitude = 6000;
        limit.temperature = -5;
        limit.thrust = 89.8;
        thr_limit.push_back(limit);
        // 7000"
        limit.altitude = 7000;
        limit.temperature = -5;
        limit.thrust = 90.3;
        thr_limit.push_back(limit);
        // 8000"
        limit.altitude = 8000;
        limit.temperature = -5;
        limit.thrust = 90.8;
        thr_limit.push_back(limit);
        // 10000"
        limit.altitude = 10000;
        limit.temperature = -5;
        limit.thrust = 91.8;
        thr_limit.push_back(limit);
    }
    /// 0
    {
        // 0"
        limit.altitude = 0;
        limit.temperature = 0;
        limit.thrust = 87.8;
        thr_limit.push_back(limit);
        // 1000"
        limit.altitude = 1000;
        limit.temperature = 0;
        limit.thrust = 82.2;
        thr_limit.push_back(limit);
        // 2000"
        limit.altitude = 2000;
        limit.temperature = 0;
        limit.thrust = 88.6;
        thr_limit.push_back(limit);
        // 3000"
        limit.altitude = 3000;
        limit.temperature = 0;
        limit.thrust = 89.1;
        thr_limit.push_back(limit);
        // 4000"
        limit.altitude = 4000;
        limit.temperature = 0;
        limit.thrust = 89.6;
        thr_limit.push_back(limit);
        // 5000"
        limit.altitude = 5000;
        limit.temperature = 0;
        limit.thrust = 90.1;
        thr_limit.push_back(limit);
        // 6000"
        limit.altitude = 6000;
        limit.temperature = 0;
        limit.thrust = 90.6;
        thr_limit.push_back(limit);
        // 7000"
        limit.altitude = 7000;
        limit.temperature = 0;
        limit.thrust = 90.1;
        thr_limit.push_back(limit);
        // 8000"
        limit.altitude = 8000;
        limit.temperature = 0;
        limit.thrust = 91.7;
        thr_limit.push_back(limit);
        // 10000"
        limit.altitude = 10000;
        limit.temperature = 0;
        limit.thrust = 92.8;
        thr_limit.push_back(limit);
    }
    /// 5
    {
        // 0"
        limit.altitude = 0;
        limit.temperature = 5;
        limit.thrust = 88.6;
        thr_limit.push_back(limit);
        // 1000"
        limit.altitude = 1000;
        limit.temperature = 5;
        limit.thrust = 89.0;
        thr_limit.push_back(limit);
        // 2000"
        limit.altitude = 2000;
        limit.temperature = 5;
        limit.thrust = 89.4;
        thr_limit.push_back(limit);
        // 3000"
        limit.altitude = 3000;
        limit.temperature = 5;
        limit.thrust = 89.9;
        thr_limit.push_back(limit);
        // 4000"
        limit.altitude = 4000;
        limit.temperature = 5;
        limit.thrust = 90.4;
        thr_limit.push_back(limit);
        // 5000"
        limit.altitude = 5000;
        limit.temperature = 5;
        limit.thrust = 90.9;
        thr_limit.push_back(limit);
        // 6000"
        limit.altitude = 6000;
        limit.temperature = 5;
        limit.thrust = 91.4;
        thr_limit.push_back(limit);
        // 7000"
        limit.altitude = 7000;
        limit.temperature = 5;
        limit.thrust = 92.0;
        thr_limit.push_back(limit);
        // 8000"
        limit.altitude = 8000;
        limit.temperature = 5;
        limit.thrust = 92.5;
        thr_limit.push_back(limit);
        // 10000"
        limit.altitude = 10000;
        limit.temperature = 5;
        limit.thrust = 91.7;
        thr_limit.push_back(limit);
    }
    /// 10
    {
        // 0"
        limit.altitude = 0;
        limit.temperature = 10;
        limit.thrust = 89.3;
        thr_limit.push_back(limit);
        // 1000"
        limit.altitude = 1000;
        limit.temperature = 10;
        limit.thrust = 89.8;
        thr_limit.push_back(limit);
        // 2000"
        limit.altitude = 2000;
        limit.temperature = 10;
        limit.thrust = 90.2;
        thr_limit.push_back(limit);
        // 3000"
        limit.altitude = 3000;
        limit.temperature = 10;
        limit.thrust = 90.7;
        thr_limit.push_back(limit);
        // 4000"
        limit.altitude = 4000;
        limit.temperature = 10;
        limit.thrust = 91.2;
        thr_limit.push_back(limit);
        // 5000"
        limit.altitude = 5000;
        limit.temperature = 10;
        limit.thrust = 91.7;
        thr_limit.push_back(limit);
        // 6000"
        limit.altitude = 6000;
        limit.temperature = 10;
        limit.thrust = 92.3;
        thr_limit.push_back(limit);
        // 7000"
        limit.altitude = 7000;
        limit.temperature = 10;
        limit.thrust = 91.2;
        thr_limit.push_back(limit);
        // 8000"
        limit.altitude = 8000;
        limit.temperature = 10;
        limit.thrust = 92.2;
        thr_limit.push_back(limit);
        // 10000"
        limit.altitude = 10000;
        limit.temperature = 10;
        limit.thrust = 91.2;
        thr_limit.push_back(limit);
    }
    /// 15
    {
        // 0"
        limit.altitude = 0;
        limit.temperature = 15;
        limit.thrust = 90.1;
        thr_limit.push_back(limit);
        // 1000"
        limit.altitude = 1000;
        limit.temperature = 15;
        limit.thrust = 90.6;
        thr_limit.push_back(limit);
        // 2000"
        limit.altitude = 2000;
        limit.temperature = 15;
        limit.thrust = 91.0;
        thr_limit.push_back(limit);
        // 3000"
        limit.altitude = 3000;
        limit.temperature = 15;
        limit.thrust = 91.5;
        thr_limit.push_back(limit);
        // 4000"
        limit.altitude = 4000;
        limit.temperature = 15;
        limit.thrust = 90.8;
        thr_limit.push_back(limit);
        // 5000"
        limit.altitude = 5000;
        limit.temperature = 15;
        limit.thrust = 90.8;
        thr_limit.push_back(limit);
        // 6000"
        limit.altitude = 6000;
        limit.temperature = 15;
        limit.thrust = 90.8;
        thr_limit.push_back(limit);
        // 7000"
        limit.altitude = 7000;
        limit.temperature = 15;
        limit.thrust = 90.8;
        thr_limit.push_back(limit);
        // 8000"
        limit.altitude = 8000;
        limit.temperature = 15;
        limit.thrust = 90.8;
        thr_limit.push_back(limit);
        // 10000"
        limit.altitude = 10000;
        limit.temperature = 15;
        limit.thrust = 90.7;
        thr_limit.push_back(limit);
    }
    /// 20
    {
        // 0"
        limit.altitude = 0;
        limit.temperature = 20;
        limit.thrust = 90.1;
        thr_limit.push_back(limit);
        // 1000"
        limit.altitude = 1000;
        limit.temperature = 20;
        limit.thrust = 90.6;
        thr_limit.push_back(limit);
        // 2000"
        limit.altitude = 2000;
        limit.temperature = 20;
        limit.thrust = 91.0;
        thr_limit.push_back(limit);
        // 3000"
        limit.altitude = 3000;
        limit.temperature = 20;
        limit.thrust = 91.5;
        thr_limit.push_back(limit);
        // 4000"
        limit.altitude = 4000;
        limit.temperature = 20;
        limit.thrust = 90.8;
        thr_limit.push_back(limit);
        // 5000"
        limit.altitude = 5000;
        limit.temperature = 20;
        limit.thrust = 90.8;
        thr_limit.push_back(limit);
        // 6000"
        limit.altitude = 6000;
        limit.temperature = 20;
        limit.thrust = 90.8;
        thr_limit.push_back(limit);
        // 7000"
        limit.altitude = 7000;
        limit.temperature = 20;
        limit.thrust = 90.8;
        thr_limit.push_back(limit);
        // 8000"
        limit.altitude = 8000;
        limit.temperature = 20;
        limit.thrust = 90.8;
        thr_limit.push_back(limit);
        // 10000"
        limit.altitude = 10000;
        limit.temperature = 20;
        limit.thrust = 90.7;
        thr_limit.push_back(limit);
    }
    /// 25
    {
        // 0"
        limit.altitude = 0;
        limit.temperature = 25;
        limit.thrust = 90.0;
        thr_limit.push_back(limit);
        // 1000"
        limit.altitude = 1000;
        limit.temperature = 25;
        limit.thrust = 90.0;
        thr_limit.push_back(limit);
        // 2000"
        limit.altitude = 2000;
        limit.temperature = 25;
        limit.thrust = 90.0;
        thr_limit.push_back(limit);
        // 3000"
        limit.altitude = 3000;
        limit.temperature = 25;
        limit.thrust = 89.9;
        thr_limit.push_back(limit);
        // 4000"
        limit.altitude = 4000;
        limit.temperature = 25;
        limit.thrust = 89.9;
        thr_limit.push_back(limit);
        // 5000"
        limit.altitude = 5000;
        limit.temperature = 25;
        limit.thrust = 89.9;
        thr_limit.push_back(limit);
        // 6000"
        limit.altitude = 6000;
        limit.temperature = 25;
        limit.thrust = 89.8;
        thr_limit.push_back(limit);
        // 7000"
        limit.altitude = 7000;
        limit.temperature = 25;
        limit.thrust = 89.7;
        thr_limit.push_back(limit);
        // 8000"
        limit.altitude = 8000;
        limit.temperature = 25;
        limit.thrust = 89.6;
        thr_limit.push_back(limit);
        // 10000"
        limit.altitude = 10000;
        limit.temperature = 25;
        limit.thrust = 89.4;
        thr_limit.push_back(limit);
    }
    /// 30
    {
        // 0"
        limit.altitude = 0;
        limit.temperature = 30;
        limit.thrust = 89.5;
        thr_limit.push_back(limit);
        // 1000"
        limit.altitude = 1000;
        limit.temperature = 30;
        limit.thrust = 89.4;
        thr_limit.push_back(limit);
        // 2000"
        limit.altitude = 2000;
        limit.temperature = 30;
        limit.thrust = 89.5;
        thr_limit.push_back(limit);
        // 3000"
        limit.altitude = 3000;
        limit.temperature = 30;
        limit.thrust = 89.4;
        thr_limit.push_back(limit);
        // 4000"
        limit.altitude = 4000;
        limit.temperature = 30;
        limit.thrust = 89.3;
        thr_limit.push_back(limit);
        // 5000"
        limit.altitude = 5000;
        limit.temperature = 30;
        limit.thrust = 89.2;
        thr_limit.push_back(limit);
        // 6000"
        limit.altitude = 6000;
        limit.temperature = 30;
        limit.thrust = 89.1;
        thr_limit.push_back(limit);
        // 7000"
        limit.altitude = 7000;
        limit.temperature = 30;
        limit.thrust = 89.0;
        thr_limit.push_back(limit);
        // 8000"
        limit.altitude = 8000;
        limit.temperature = 30;
        limit.thrust = 89.2;
        thr_limit.push_back(limit);
        // 10000"
        limit.altitude = 10000;
        limit.temperature = 30;
        limit.thrust = 89.2;
        thr_limit.push_back(limit);
    }
    /// 35
    {
        // 0"
        limit.altitude = 0;
        limit.temperature = 35;
        limit.thrust = 88.6;
        thr_limit.push_back(limit);
        // 1000"
        limit.altitude = 1000;
        limit.temperature = 35;
        limit.thrust = 88.6;
        thr_limit.push_back(limit);
        // 2000"
        limit.altitude = 2000;
        limit.temperature = 35;
        limit.thrust = 88.6;
        thr_limit.push_back(limit);
        // 3000"
        limit.altitude = 3000;
        limit.temperature = 35;
        limit.thrust = 88.6;
        thr_limit.push_back(limit);
        // 4000"
        limit.altitude = 4000;
        limit.temperature = 35;
        limit.thrust = 88.6;
        thr_limit.push_back(limit);
        // 5000"
        limit.altitude = 5000;
        limit.temperature = 35;
        limit.thrust = 88.5;
        thr_limit.push_back(limit);
        // 6000"
        limit.altitude = 6000;
        limit.temperature = 35;
        limit.thrust = 89.0;
        thr_limit.push_back(limit);
        // 7000"
        limit.altitude = 7000;
        limit.temperature = 35;
        limit.thrust = 89.5;
        thr_limit.push_back(limit);
        // 8000"
        limit.altitude = 8000;
        limit.temperature = 35;
        limit.thrust = 89.5;
        thr_limit.push_back(limit);
        // 10000"
        limit.altitude = 10000;
        limit.temperature = 35;
        limit.thrust = 89.5;
        thr_limit.push_back(limit);
    }
    /// 40
    {
        // 0"
        limit.altitude = 0;
        limit.temperature = 40;
        limit.thrust = 87.8;
        thr_limit.push_back(limit);
        // 1000"
        limit.altitude = 1000;
        limit.temperature = 40;
        limit.thrust = 87.8;
        thr_limit.push_back(limit);
        // 2000"
        limit.altitude = 2000;
        limit.temperature = 40;
        limit.thrust = 87.8;
        thr_limit.push_back(limit);
        // 3000"
        limit.altitude = 3000;
        limit.temperature = 40;
        limit.thrust = 88.1;
        thr_limit.push_back(limit);
        // 4000"
        limit.altitude = 4000;
        limit.temperature = 40;
        limit.thrust = 88.7;
        thr_limit.push_back(limit);
        // 5000"
        limit.altitude = 5000;
        limit.temperature = 40;
        limit.thrust = 88.7;
        thr_limit.push_back(limit);
        // 6000"
        limit.altitude = 6000;
        limit.temperature = 40;
        limit.thrust = 88.7;
        thr_limit.push_back(limit);
        // 7000"
        limit.altitude = 7000;
        limit.temperature = 40;
        limit.thrust = 88.7;
        thr_limit.push_back(limit);
        // 8000"
        limit.altitude = 8000;
        limit.temperature = 40;
        limit.thrust = 88.7;
        thr_limit.push_back(limit);
        // 10000"
        limit.altitude = 10000;
        limit.temperature = 40;
        limit.thrust = 88.7;
        thr_limit.push_back(limit);
    }
    /// 45
    {
        // 0"
        limit.altitude = 0;
        limit.temperature = 45;
        limit.thrust = 87.0;
        thr_limit.push_back(limit);
        // 1000"
        limit.altitude = 1000;
        limit.temperature = 45;
        limit.thrust = 87.6;
        thr_limit.push_back(limit);
        // 2000"
        limit.altitude = 2000;
        limit.temperature = 45;
        limit.thrust = 88.0;
        thr_limit.push_back(limit);
        // 3000"
        limit.altitude = 3000;
        limit.temperature = 45;
        limit.thrust = 88.0;
        thr_limit.push_back(limit);
        // 4000"
        limit.altitude = 4000;
        limit.temperature = 45;
        limit.thrust = 88.0;
        thr_limit.push_back(limit);
        // 5000"
        limit.altitude = 5000;
        limit.temperature = 45;
        limit.thrust = 88.0f;
        thr_limit.push_back(limit);
        // 6000"
        limit.altitude = 6000;
        limit.temperature = 45;
        limit.thrust = 88.0;
        thr_limit.push_back(limit);
        // 7000"
        limit.altitude = 7000;
        limit.temperature = 45;
        limit.thrust = 88.0;
        thr_limit.push_back(limit);
        // 8000"
        limit.altitude = 8000;
        limit.temperature = 45;
        limit.thrust = 88.0;
        thr_limit.push_back(limit);
        // 10000"
        limit.altitude = 10000;
        limit.temperature = 45;
        limit.thrust = 88.0;
        thr_limit.push_back(limit);
    }
};

/////////////////////////////////////

float FMSPref::getThrustLimit(int altitude, int temperature)
{
    float thrust = 100;
    //char debug[128];

    // (1) temperature borders
    int min_temp;
    int max_temp;
    if ((temperature % 5) != 0) {
        min_temp = (int)temperature/10;
        max_temp = (int)(temperature/10)+1;
        min_temp = min_temp*10;
        max_temp = max_temp*10;
    } else {
        min_temp = max_temp = temperature;
    }

    // (2) altitude borders
    int min_alt;
    int max_alt;
    if ((altitude % 1000) != 0) {
        min_alt = (int)altitude/1000;
        max_alt = (int)(altitude/1000)+1;
        min_alt = min_alt*1000;
        max_alt = max_alt*1000;
    } else {
        min_alt = max_alt = altitude;
    }

    // (3) count
    float max_alt_thrust = findThrust(min_temp, max_alt);
    float min_alt_thrust = findThrust(min_temp, min_alt);
    float alt_thrust_dif = (max_alt_thrust - min_alt_thrust)/10;
    //sprintf(debug, "float max_alt_thrust = FindThrust(min_temp, max_alt); |||| %f = FindThrust(%d, %d)\n",
    //		max_alt_thrust, min_temp, max_alt);
    //XPLMDebugString(debug);
    //sprintf(debug, "float min_alt_thrust = FindThrust(min_temp, min_alt); |||| %f = FindThrust(%d, %d)\n",
    //		min_alt_thrust, min_temp, min_alt);
    //XPLMDebugString(debug);

    float max_temp_thrust = findThrust(max_temp, min_alt);
    float min_temp_thrust = findThrust(min_temp, min_alt);
    float temp_thrust_dif = (max_temp_thrust - min_temp_thrust)/5;

    float alt_thrust = min_alt_thrust + ((altitude-min_alt)/100)*alt_thrust_dif;
    float temp_thrust = min_temp_thrust + (temperature-min_temp)*temp_thrust_dif;



    thrust = (alt_thrust + temp_thrust)/2;

    return thrust;
};

/////////////////////////////////////

float FMSPref::findThrust(int temperature, int altitude)
{
    int i;
    for (i = 0; i <  thr_limit.size(); i++) {
        if (thr_limit[i].temperature == temperature && thr_limit[i].altitude == altitude) {
            return thr_limit[i].thrust;
        }
    }

    return 85.0f;
};

/////////////////////////////////////

void FMSPref::calculateThrustLimits(int altitude_ft, int rwy_altitude_ft, int cruise_altitude_ft)
{
    // Take Off (Use altitude or rwy altitude)
    if (rwy_altitude_ft == -1)
        rwy_altitude_ft = altitude_ft;
    m_to_thrust = findThrust(thrustOAT(), rwy_altitude_ft);

    // Go Around (need destination altitude)

    // Climb (cruise altitude / 2)
    m_clb_thrust = findThrust(Navcalc::getAltTemp(thrustOAT(), altitude_ft, cruise_altitude_ft/2),
                              cruise_altitude_ft/2);

    // Cruise
    m_crz_thrust = findThrust(Navcalc::getAltTemp(thrustOAT(), altitude_ft, cruise_altitude_ft),
                              cruise_altitude_ft);

    // MCT (to with -10C)
};

void FMSPref::calculateZFWandGWT()
{
    if (m_bow != 0 && m_pass_weight != 0 && m_cargo != -1) {
        m_zfw = m_bow + m_pass_weight + m_cargo;
    }

    if (m_zfw != 0 && m_fuel != 0) {
        m_gwt = m_zfw + m_fuel;
    }
}

double FMSPref::optimumVerticalSpeed(double gwt_lbs, int altitude_ft)
{
    double vertical_speed_fpm = 0.0;

    vertical_speed_fpm = 1645.0;

    return vertical_speed_fpm;
}
