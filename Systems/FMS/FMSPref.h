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

#ifndef FMSPref_h
#define FMSPref_h

#include <stdlib.h>
#include <vector>
#include "FMSData.h"
#include "../../Library/Dataref/DFloat.h"
#include "../../../CRJ/Systems/FMS/IFMSPref.h"

#define THRUST_OAT_NOT_DEFINED -4000

using namespace std;

class FMSPref : public IFMSPref{
public:
    FMSPref();

    // Thrust
    void initThrustLimits();
    ActiveEngBleed engBleed() { return m_eng_bleed; }
    void setEngBleed(ActiveEngBleed value) { m_eng_bleed = value; }

    ActiveThrustLimit thrustLimit() { return m_thrust_limit; }
    void setThrustLimit(ActiveThrustLimit value) { m_thrust_limit = value; }

    // if method returns -4000 than it's not defined
    int thrustOAT() { return m_thrust_oat; }
    void setThrustOAT(int value) { m_thrust_oat = value; }

    float toThrust() { return m_to_thrust; }
    float gaThrust() { return m_ga_thrust; }
    float clbThrust() { return m_clb_thrust; }
    float crzThrust() { return m_crz_thrust; }
    float tgtThrust() { return m_tgt_thrust; }
    float mctThrust() { return m_mct_thrust; }

    void setTgtThrust(float value) { m_tgt_thrust = value; m_thrust_limit = thrust_tgt; }

    void calculateThrustLimits(int altitude_ft, int rwy_altitude_ft, int cruise_altitude_ft);

    float basicOperationWeight() { return m_bow; }
    void setBasicOperationWeight(float bow) { m_bow = bow; }

    float passNumber() { return m_pass_number; }
    void calculatePassWeight() { m_pass_weight = m_pass_number * m_one_pass_weight; }
    void setPassNumber(float pass_number) { m_pass_number = pass_number; }

    float passWeight() { return m_pass_weight; }

    float defaultPassWeight() { return m_default_pass_weight; }

    float cargo() { return m_cargo; }
    void setCargo(float cargo) { m_cargo = cargo; }

    float zeroFuelWeight() { return m_zfw; }
    void setZeroFuelWeight(float zfw) { m_zfw = zfw; }

    float fuel() { return m_fuel; }
    void setFuel(float fuel) { m_fuel = fuel; }

    float grossWeight() { return m_gwt; }
    void setGrossWeight(float gwt) { m_gwt = gwt; }

    void calculateZFWandGWT();

    double optimumVerticalSpeed(double gwt_lbs, int altitude_ft);

private:
    float getThrustLimit(int altitude_ft, int temperature);
    float findThrust(int temperature, int altitude);

private:

    // thrust
    float m_to_thrust;
    float m_ga_thrust;
    float m_clb_thrust;
    float m_crz_thrust;
    float m_tgt_thrust;
    float m_mct_thrust;

    ActiveThrustLimit m_thrust_limit;
    ActiveEngBleed m_eng_bleed;
    int m_thrust_oat;

    typedef vector<Thrust_Limit> ThrLimit;
    ThrLimit thr_limit;

    float m_bow;
    float m_pass_number;
    float m_pass_weight;
    float m_one_pass_weight;
    float m_default_pass_weight;
    float m_cargo;
    float m_zfw;
    float m_fuel;
    float m_gwt;
};

#endif /* FMSPref_h */
