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


#ifndef FMSDatabase_h
#define FMSDatabase_h

#include "FMSData.h"
#include "../../Library/FMS/airport.h"
#include "../../Library/FMS/runway.h"
#include "../../Library/FMS/vor.h"
#include "../../Library/FMS/ndb.h"
#include "../../Library/FMS/ils.h"
#include "../../Library/FMS/intersection.h"
#include "../../Library/FMS/airway.h"
#include "../../Library/FMS/sid.h"
#include "../../Library/FMS/star.h"
#include "../../Library/FMS/approach.h"
#include "../../Library/FMS/transition.h"
#include "../../Library/FMS/waypoint_hdg_to_alt.h"
#include <stdlib.h>
#include <string>
#include <fstream>
#include <vector>
#include "../../Library/tinyxml/tinyxml.h"

#include "../../../CRJ/Systems/FMS/IFMSDatabase.h"

using namespace std;

typedef map<string, Airport*> AirportMap;
typedef AirportMap::iterator AirportMapIterator;

typedef multimap<string, Ndb*> NdbMap;
typedef NdbMap::iterator NdbMapIterator;

typedef multimap<string, Vor*> VorMap;
typedef VorMap::iterator VorMapIterator;

typedef multimap<string, Ils*> IlsMap;
typedef IlsMap::iterator IlsMapIterator;

typedef multimap<string, Intersection*> IntersectionMap;
typedef IntersectionMap::iterator IntersectionMapIterator;

typedef map<string, Airway*> AirwayMap;
typedef AirwayMap::iterator AirwayMapIterator;

typedef multimap<string, ProcedureList> ProcedureMap;
typedef ProcedureMap::iterator ProcedureMapIterator;

typedef vector<Waypoint*> StdWaypointList;

class FMSDatabase : public IFMSDatabase
{
public:

    FMSDatabase();

    void load();
    void loadAirports();
    void loadRunways();
    void loadNavaid();
    void loadIntersections();
    void loadAirways();
    void loadProcedure(const string &name);

    Airport* getAirport(const std::string &id);

    ProcedureList getSids(const std::string &id);
    ProcedureList getSids(const std::string &id, const std::string &rwy);
    ProcedureList getSidTrans(const string &id, const string &sid);
    ProcedureList getStar(const QString &id);
    ProcedureList getAppr(const QString &id);
    ProcedureList getApprTrans(const string &id, const string &appr);

    void getNdb(const std::string &id, StdWaypointList *list);
    void getVor(const std::string &id, StdWaypointList *list);
    void getIls(const std::string &id, StdWaypointList *list);
    void getFix(const std::string &id, StdWaypointList *list);

    Airway* getAirway(const std::string &id);

    void getVorByCoordinates(const Waypoint& current_position,
                             int distance_nm,
                             StdWaypointList *list);
    void getFixByCoordinates(const Waypoint& current_position,
                             int distance_nm,
                             StdWaypointList *list);
    void getAptByCoordinates(const Waypoint& current_position,
                             int distance_nm,
                             StdWaypointList *list);
    void getNdbByCoordinates(const Waypoint& current_position,
                             int distance_nm,
                             StdWaypointList *list);

    string effective() const { return validity; }

protected:
    Waypoint parseWaypoint(TiXmlElement *elem, const QString& flag);

    ProcedureList getProcedure(const std::string &id);

private:
    static FMSDatabase* instance;

    string m_path_airport;
    string m_path_runway;
    string m_path_navaid;
    string m_path_intersection;
    string m_path_airway;

    AirportMap m_airport_map;
    NdbMap m_ndb_map;
    VorMap m_vor_map;
    IlsMap m_ils_map;
    IntersectionMap m_intersection_map;
    AirwayMap m_airway_map;
    ProcedureMap m_procedure_map;

    string validity;
};

#endif /* FMSDatabase_h */
