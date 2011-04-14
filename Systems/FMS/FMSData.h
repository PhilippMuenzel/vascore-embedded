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


#ifndef FMSData_h
#define FMSData_h

///////////////////////////

// Path to AIRAC files
#if IBM
#define NAVDATA_AIRPORTS  "JRollonPlanes\\NavData\\airports.dat"
#define NAVDATA_RUNWAYS   "JRollonPlanes\\NavData\\wpNavAPT.txt"
#define NAVDATA_NAVAIDS   "JRollonPlanes\\NavData\\wpNavAID.txt"
#define NAVDATA_FIXES     "JRollonPlanes\\NavData\\wpNavFIX.txt"
#define NAVDATA_AIRWAYS   "JRollonPlanes\\NavData\\wpNavRTE.txt"
#define NAVDATA_PROC      "JRollonPlanes\\SidStar\\"
#define SAVED_ROUTES      "JRollonPlanes\\SavedRoutes\\"
#else
#define NAVDATA_AIRPORTS  "JRollonPlanes/NavData/airports.dat"
#define NAVDATA_RUNWAYS   "JRollonPlanes/NavData/wpNavAPT.txt"
#define NAVDATA_NAVAIDS   "JRollonPlanes/NavData/wpNavAID.txt"
#define NAVDATA_FIXES     "JRollonPlanes/NavData/wpNavFIX.txt"
#define NAVDATA_AIRWAYS   "JRollonPlanes/NavData/wpNavRTE.txt"
#define NAVDATA_PROC      "JRollonPlanes/SidStar/"
#define SAVED_ROUTES      "JRollonPlanes/SavedRoutes/"
#endif /* IBM */

///////////////////////////
// PAGES

typedef enum {
    cdu_page_index,
    cdu_page_menu,
    cdu_page_plane_menu,
    cdu_page_status,
    cdu_page_pos_init,
    cdu_page_pref_menu,
    cdu_page_thrust_limit_1,
    cdu_page_fpln_1,
    cdu_page_fpln_2,
    cdu_page_dep_arr_index,
    cdu_page_dep,
    cdu_page_arr,
    cdu_page_legs,
    cdu_page_hold,
    cdu_page_wpt_select,
    cdu_page_mfd_menu,
    cdu_page_radio,
} CDUPages;

///////////////////////////
// BUTTONS

// Left 1-6
#define CRJ_FMS_BUTTON_L1			"CRJ/fms/L1_button"
#define CRJ_FMS_BUTTON_L2			"CRJ/fms/L2_button"
#define CRJ_FMS_BUTTON_L3			"CRJ/fms/L3_button"
#define CRJ_FMS_BUTTON_L4			"CRJ/fms/L4_button"
#define CRJ_FMS_BUTTON_L5			"CRJ/fms/L5_button"
#define CRJ_FMS_BUTTON_L6			"CRJ/fms/L6_button"

// Right 1-6
#define CRJ_FMS_BUTTON_R1			"CRJ/fms/R1_button"
#define CRJ_FMS_BUTTON_R2			"CRJ/fms/R2_button"
#define CRJ_FMS_BUTTON_R3			"CRJ/fms/R3_button"
#define CRJ_FMS_BUTTON_R4			"CRJ/fms/R4_button"
#define CRJ_FMS_BUTTON_R5			"CRJ/fms/R5_button"
#define CRJ_FMS_BUTTON_R6			"CRJ/fms/R6_button"

// Letters
#define CRJ_FMS_BUTTON_A			"CRJ/click/fms_a"
#define CRJ_FMS_BUTTON_B			"CRJ/click/fms_b"
#define CRJ_FMS_BUTTON_C			"CRJ/click/fms_c"
#define CRJ_FMS_BUTTON_D			"CRJ/click/fms_d"
#define CRJ_FMS_BUTTON_E			"CRJ/click/fms_e"
#define CRJ_FMS_BUTTON_F			"CRJ/click/fms_f"
#define CRJ_FMS_BUTTON_G			"CRJ/click/fms_g"
#define CRJ_FMS_BUTTON_H			"CRJ/click/fms_h"
#define CRJ_FMS_BUTTON_I			"CRJ/click/fms_i"
#define CRJ_FMS_BUTTON_J			"CRJ/click/fms_j"
#define CRJ_FMS_BUTTON_K			"CRJ/click/fms_k"
#define CRJ_FMS_BUTTON_L			"CRJ/click/fms_l"
#define CRJ_FMS_BUTTON_M			"CRJ/click/fms_m"
#define CRJ_FMS_BUTTON_N			"CRJ/click/fms_n"
#define CRJ_FMS_BUTTON_O			"CRJ/click/fms_o"
#define CRJ_FMS_BUTTON_P			"CRJ/click/fms_p"
#define CRJ_FMS_BUTTON_Q			"CRJ/click/fms_q"
#define CRJ_FMS_BUTTON_R			"CRJ/click/fms_r"
#define CRJ_FMS_BUTTON_S			"CRJ/click/fms_s"
#define CRJ_FMS_BUTTON_T			"CRJ/click/fms_t"
#define CRJ_FMS_BUTTON_U			"CRJ/click/fms_u"
#define CRJ_FMS_BUTTON_V			"CRJ/click/fms_v"
#define CRJ_FMS_BUTTON_W			"CRJ/click/fms_w"
#define CRJ_FMS_BUTTON_X			"CRJ/click/fms_x"
#define CRJ_FMS_BUTTON_Y			"CRJ/click/fms_y"
#define CRJ_FMS_BUTTON_Z			"CRJ/click/fms_z"
#define CRJ_FMS_BUTTON_SP			"CRJ/click/fms_space"
#define CRJ_FMS_BUTTON_DEL          "CRJ/click/fms_delete"
#define CRJ_FMS_BUTTON_BAR          "CRJ/click/fms_bar"
#define CRJ_FMS_BUTTON_CLR          "CRJ/click/fms_clr"
#define CRJ_FMS_BUTTON_POINT        "CRJ/click/fms_point"
#define CRJ_FMS_BUTTON_MINUS        "CRJ/click/fms_plus_minus"

#define CRJ_FMS_BUTTON_0			"CRJ/click/fms_0"
#define CRJ_FMS_BUTTON_1			"CRJ/click/fms_1"
#define CRJ_FMS_BUTTON_2			"CRJ/click/fms_2"
#define CRJ_FMS_BUTTON_3			"CRJ/click/fms_3"
#define CRJ_FMS_BUTTON_4			"CRJ/click/fms_4"
#define CRJ_FMS_BUTTON_5			"CRJ/click/fms_5"
#define CRJ_FMS_BUTTON_6			"CRJ/click/fms_6"
#define CRJ_FMS_BUTTON_7			"CRJ/click/fms_7"
#define CRJ_FMS_BUTTON_8			"CRJ/click/fms_8"
#define CRJ_FMS_BUTTON_9			"CRJ/click/fms_9"

// MCDU Menu
#define CRJ_FMS_BUTTON_MCDU			"CRJ/fms/mcdu_menu_button"
// Index
#define CRJ_FMS_BUTTON_INDEX		"CRJ/fms/index_button"
// FlightPlan
#define CRJ_FMS_BUTTON_FPLN			"CRJ/fms/fpln_button"
// NextPage
#define CRJ_FMS_BUTTON_NPAGE		"CRJ/fms/next_page_button"
// Prev Page
#define CRJ_FMS_BUTTON_PPAGE		"CRJ/fms/prev_page_button"
// Dep & Arr
#define CRJ_FMS_BUTTON_DEPARR		"CRJ/fms/dep_arr_button"
// legs page
#define CRJ_FMS_BUTTON_LEGS			"CRJ/fms/legs_button"
// hold page
#define CRJ_FMS_BUTTON_HOLD			"CRJ/fms/hold_button"
// radio tunning
#define CRJ_FMS_BUTTON_RADIO		"CRJ/fms/radio_button"
// pref button
#define CRJ_FMS_BUTTON_PREF			"CRJ/fms/perf_button"
#define CRJ_FMS_BUTTON_EXEC         "CRJ/fms/exec_button"
#define CRJ_FMS_BUTTON_MFD_MENU     "CRJ/fms/mfd_menu_button"
#define CRJ_FMS_BUTTON_VNAV         "CRJ/fms/vnav_button"

///////////////////////////
// IRS

typedef enum {
    irs_off,
    irs_waiting,
    irs_in_align1,
    irs_in_align2,
    irs_on
} IRSStatus;

#define CRJ_IRS_1_SWITCH        "CRJ/fms/irs_1_button"
#define CRJ_IRS_2_SWITCH        "CRJ/fms/irs_2_button"

#define X_LATITUDE              "sim/flightmodel/position/latitude"
#define X_LONGITUDE             "sim/flightmodel/position/longitude"


#define X_FMS_HDG               "sim/cockpit/gps/course"
#define X_FMS_DEF               "sim/cockpit/radios/gps_hdef_dot"

///////////////////////////
// Thrust Limit

enum ActiveThrustLimit {
    thrust_to,
    thrust_ga,
    thrust_clb,
    thrust_crz,
    thrust_tgt,
    thrust_mct,
    thrust_none
};

enum ActiveEngBleed {
    bleed_wg_cowl,
    bleed_cowl,
    bleed_10th,
    bleed_off
};

struct Thrust_Limit {
    int altitude;
    int temperature;
    float thrust;
};

#endif /* FMSData_h */
