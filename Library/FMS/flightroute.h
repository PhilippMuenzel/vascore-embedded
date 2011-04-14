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

#ifndef FLIGHTROUTE_H
#define FLIGHTROUTE_H

//#include "logger.h"

#include "route.h"

class Navdata;
class ProjectionBase;
class QRegExp;
class FlightStatus;

#include <vector>
using namespace std;

typedef vector<QString> ICAOList;

/////////////////////////////////////////////////////////////////////////////

//TODO add change detection to holding and route data and connect them to our signalChanged()

//! complete route with adep, ades, etc.
class FlightRoute : public Route
{
public:

    //! Standard Constructor
    FlightRoute(const QString& id = QString::null);

    //! Destructor
    virtual ~FlightRoute();

    FlightRoute(const FlightRoute& other):Route(other)  { *this = other; }
    const FlightRoute& operator=(const FlightRoute& other);

    //-----

    virtual void clear();
    virtual void appendWaypoint(const Waypoint& wpt, bool remove_double_wtps = false);
    virtual void insertWaypoint(const Waypoint& wpt, int pos, bool remove_double_wtps = false, bool remove_inbetween = false);
    virtual void goDirect(const uint dct_wpt_index, double turn_radius_nm, QString direct_wpt_name, QTime overflown_time);
    virtual bool removeWaypoint(int pos);

    //! applies the given holding to the waypoint with the given index
    bool setHolding(uint wpt_index, const Holding& holding);

    //! sets the overfly restriction of the waypoint at the given index
    bool setWaypointOverflyRestriction(uint index, bool is_overfly);

    //-----

    // departure airport
    void setAsDepartureAirport(uint wpt_index, const QString& active_runway);
    int departureAirportIndex() const;
    const Airport* departureAirport() const;
    Airport* departureAirport();
    inline const QString& departureAirportId() const { return m_adep_id; }

    // SID sets the given SID, clears any SID and SID transition points
    bool setSid(const Sid& sid, const QString& runway);
    inline const QString& sidId() const { return m_sid_id; }
    void deleteSid();

    // SID TRANS set the given SID transition, make sure setSid() was called before
    bool setSidTransition(const Transition& sid_transition);
    inline const QString& sidTransitionId() const { return m_sid_transition_id; }

    // STAR set the given star, removes any STAR, transition and approach points from the route
    bool setStar(const Star& star, const QString& runway);
    inline const QString& starId() const { return m_star_id; }
    void deleteStar();

    // APP TRANS sets the given APP transition, make sure setStar() was called before
    bool setAppTransition(const Transition& app_transition, const QString& runway);
    inline const QString& appTransitionId() const { return m_app_transition_id; }

    // Approach sets the given approach, make sure setStar() was called before
    bool setApproach(const Approach& approach, const QString& runway);
    inline const QString& approachId() const { return m_approach_id; }

    // destination airport
    void setAsDestinationAirport(uint wpt_index, const QString& active_runway);
    int destinationAirportIndex() const;
    const Airport* destinationAirport() const;
    Airport* destinationAirport();
    inline const QString& destinationAirportId() const { return m_ades_id; }

    const double& distanceActiveWptToDestination() const { return m_distance_from_active_wpt_to_destination; }

    //----- waypoint

    inline double trueTrackFromPreviousToActiveWpt() const
    {
        return trueTrackToNextWaypoint(m_active_wpt_index-1);
    }

    inline double trueTrackFromActiveToNextWpt() const
    {
        return trueTrackToNextWaypoint(m_active_wpt_index);
    }

    void switchToNextWaypoint(QTime overflown_time);
    void switchToPrevWaypoint() { m_active_wpt_index = m_active_wpt_index - 1; }

    //----- previous waypoint

    //! ATTENTION: the return value will be negative if there is no previous waypoint
    inline int previousWaypointIndex() const { return m_active_wpt_index - 1; }

    inline const Waypoint* previousWaypoint() const
    {
        if ((int)m_active_wpt_index < 1 || count() == 0) return 0;
        return waypoint(m_active_wpt_index-1);
    }

    inline Waypoint* previousWaypoint()
    {
        if ((int)m_active_wpt_index == 0 || count() == 0) return 0;
        return waypoint(m_active_wpt_index-1);
    }

    //----- active waypoint

    inline int activeWaypointIndex() const { return m_active_wpt_index; }

    inline const Waypoint* activeWaypoint() const
    {
        if ((int)m_active_wpt_index >= count() || count() == 0) return 0;
        //MYASSERT((int)m_active_wpt_index < count());
        return waypoint(m_active_wpt_index);
    }

    inline Waypoint* activeWaypoint()
    {
        if ((int)m_active_wpt_index >= count() || count() == 0) return 0;
        //MYASSERT((int)m_active_wpt_index < count());
        return waypoint(m_active_wpt_index);
    }

    inline const RouteData* activeWaypointRouteData() const
    {
        if ((int)m_active_wpt_index >= count() || count() == 0) return 0;
        return &routeData(m_active_wpt_index);
    }

    //----- next waypoint

    inline const Waypoint* nextWaypoint() const
    {
        if ((int)m_active_wpt_index >= count()-1) return 0;
        return waypoint(m_active_wpt_index+1);
    }

    inline Waypoint* nextWaypoint()
    {
        if ((int)m_active_wpt_index >= count()-1) return 0;
        return waypoint(m_active_wpt_index+1);
    }

    //----- additional fields

    // getter

    const double& hoursActiveWptToDestination() const { return m_hours_from_active_wpt_to_destination; }

    int cruiseFl() const { return m_cruise_fl; }
    const QString& companyRoute() const { return m_company_route; }
    const QString& flightNumber() const { return m_flight_number; }
    int dryOpWeight() const { return m_dow; }
    int passNumber() const { return m_pass; }
    int defaultPassWeight() const { return m_default_pass_wt; }
    int cargoWeight() const { return m_cargo_wt; }
    int fuelWeight() const { return m_fuel_wt; }
    int zeroFuelWeight() const { return m_zfw; }
    int grossWeight() const { return m_gwt; }
    int climbSpeedKnots() const { return m_climb_speed_knots; }
    float climbSpeedMach() const { return m_climb_speed_mach; }
    int climbTransAltitude() const { return m_climb_trans_alt; }
    int climbSpeedLimit1() const { return m_climb_speed_limit_1; }
    int climbAltitudeLimit1() const { return m_climb_alt_limit_1; }
    int climbSpeedLimit2() const { return m_climb_speed_limit_2; }
    int climbAltitudeLimit2() const { return m_climb_alt_limit_2; }
    int cruiseSpeedKnots() const { return m_cruise_speed_knots; }
    float cruiseSpeedMach() const { return m_cruise_speed_mach; }
    int descentSpeedKnots() const { return m_descent_speed_knots; }
    float descentSpeedMach() const { return m_descent_speed_mach; }
    int descentTransAltitude() const { return m_descent_trans_alt; }
    int descentSpeedLimit1() const { return m_descent_speed_limit_1; }
    int descentAltitudeLimit1() const { return m_descent_alt_limit_1; }
    int descentSpeedLimit2() const { return m_descent_speed_limit_2; }
    int descentAltitudeLimit2() const { return m_descent_alt_limit_2; }
    float descentVPA() const { return m_descent_vpa; }

    // setter

    void setHoursActiveWptToDestination(const double& hours_from_active_wpt_to_destination)
    { m_hours_from_active_wpt_to_destination = hours_from_active_wpt_to_destination; }

    void setCruiseFl(int cruise_fl)
    {
        m_cruise_fl = cruise_fl;
        m_need_save = true;
    }

    void setCompanyRoute(const QString& company_route)
    {
        m_company_route = company_route;
    }

    void setFlightNumber(const QString& flight_number)
    {
        m_flight_number = flight_number;
    }

    void setDryOpWeight(int dow)
    {
        m_dow = dow;
        m_need_save = true;
    }

    void setPassNumber(int pass)
    {
        m_pass = pass;
        m_need_save = true;
    }

    void setDefaultPassWeight(int default_pass_wt)
    {
        m_default_pass_wt = default_pass_wt;
        m_need_save = true;
    }

    void setCargoWeight(int cargo_wt)
    {
        m_cargo_wt = cargo_wt;
        m_need_save = true;
    }

    void setFuelWeight(int fuel_wt)
    {
        m_fuel_wt = fuel_wt;
        m_need_save = true;
    }

    void setZeroFuelWeight(int zfw)
    {
        m_zfw = zfw;
        m_need_save = true;
    }

    void setClimbSpeedKnots(int knots)
    {
        m_climb_speed_knots = knots;
        m_need_save = true;
    }

    void setClimbSpeedMach(float mach)
    {
        m_climb_speed_mach = mach;
        m_need_save = true;
    }

    void setClimbSpeedLimit1(int speed)
    {
        m_climb_speed_limit_1 = speed;
        m_need_save = true;
    }

    void setClimbAltitudeLimit1(int altitude)
    {
        m_climb_alt_limit_1 = altitude;
        m_need_save = true;
    }

    void setClimbSpeedLimit2(int speed)
    {
        m_climb_speed_limit_2 = speed;
        m_need_save = true;
    }

    void setClimbAltitudeLimit2(int altitude)
    {
        m_climb_alt_limit_2 = altitude;
        m_need_save = true;
    }

    void setClimbTransAltitude(int altitude)
    {
        m_climb_trans_alt = altitude;
        m_need_save = true;
    }

    // counter

    void countPerfWeight();
    void countVnavAltitudeAndSpeed();

    //----- virtual waypoints

    inline const Waypoint& altReachWpt() const { return m_alt_reach_wpt; }
    inline Waypoint& altReachWpt() { return m_alt_reach_wpt; }
    inline const Waypoint& todWpt() const { return  m_tod_wpt; }
    inline Waypoint& todWpt() { return  m_tod_wpt; }

    //----- load/save

    bool loadFP(const QString& filename, const Navdata* navdata);
    bool saveFP(const QString& filename) const;

    //----- extract from ICAO conform input

    //! Awaits a route in ICAO format (like LOWG GRZ P978 VIW RTT LOWI).
    //! The first point of the route should be the departure airport, the last
    //! point should be the arrival airport.
    //! Clears the route and inserts the given one.
    //! Returns true on success, false otherwise, "error" will return an error
    //! text when appropriate.
    bool extractICAORoute(const QString& route, const Navdata& navdata,
                          const QRegExp& lat_lon_wpt_regexp, QString& error);

    //-----

    //TODO move the view wpt index to the FCM data, this has nothing to do with the route itself

    inline int viewWptIndex() const { return qMin((int)count()-1, (int)m_view_wpt_index); }
    inline const Waypoint* viewWpt() const { return waypoint(viewWptIndex()); }

    inline void setViewWptIndex(int index)
    {
        int new_index = qMin(qMax(index, -1), (int)count()-1);
        if (new_index == m_view_wpt_index) return;
        m_view_wpt_index = new_index;
        //emit signalChanged(m_flag, true, QString("FlightRoute:setViewWptIndex: index=%1").arg(m_view_wpt_index));
    }

    ICAOList icao(bool ignoreSidStar = false);

    bool isNeedSave() { return m_need_save; }
    void saveToXPlane();
    std::list<std::string> loadCompanyRoute(const std::string&);
    void saveCompanyRoute();

protected:

    void setAsDepartureAirportInternal(uint wpt_index, const QString& active_runway);
    void setAsDestinationAirportInternal(uint wpt_index, const QString& active_runway);

    void resetCacheFields() const
    {
        m_adep_wpt_index = -2;
        m_ades_wpt_index = -2;
    }

    void calcDistanceActiveWptToDestination();

protected slots:

    void slotChanged(const QString&, bool, const QString&);

protected:

    //const ProjectionBase* m_projection;

    mutable int m_adep_wpt_index;
    QString m_adep_id;

    QString m_sid_id;
    QString m_sid_transition_id;
    QString m_star_id;
    QString m_app_transition_id;
    QString m_approach_id;

    mutable int m_ades_wpt_index;
    QString m_ades_id;

    bool m_need_save;
    int m_xplane_count;

    //-----

    //TODO move those into the route with according waypoint flags!
    Waypoint m_alt_reach_wpt;
    Waypoint m_tod_wpt;

    //-----

    //! index to the currently active route waypoint
    uint m_active_wpt_index;

    //----- additional fields

    double m_distance_from_active_wpt_to_destination;
    double m_hours_from_active_wpt_to_destination;


    int m_cruise_temp;
    QString m_company_route;
    QString m_flight_number;
    int m_cost_index;
    int m_tropo_pause;
    //! to be used when the actual waypoint to view differs from the active waypoint
    int m_view_wpt_index;

    // perf init 1
    int m_cruise_fl;
    int m_default_dow;
    int m_dow;
    int m_default_pass_wt;
    int m_pass;
    int m_pass_wt;
    int m_cargo_wt;
    int m_fuel_wt;
    int m_zfw;
    int m_gwt;

    // vnav climb (1)
    int m_climb_speed_knots;
    float m_climb_speed_mach;
    int m_climb_trans_alt;
    int m_climb_speed_limit_1;
    int m_climb_alt_limit_1;
    int m_climb_speed_limit_2;
    int m_climb_alt_limit_2;

    // vnav cruise (2)
    int m_cruise_speed_knots;
    float m_cruise_speed_mach;

    // vnav descent (3)
    int m_descent_speed_knots;
    float m_descent_speed_mach;
    int m_descent_trans_alt;
    int m_descent_speed_limit_1;
    int m_descent_alt_limit_1;
    int m_descent_speed_limit_2;
    int m_descent_alt_limit_2;
    float m_descent_vpa;

    //

    uint m_thrust_reduction_altitude_ft;
    uint m_acceleration_altitude_ft;
};

#endif /* FLIGHTROUTE_H */

// End of file

