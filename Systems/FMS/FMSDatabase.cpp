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


#include "FMSDatabase.h"
#include "../../Library/FMS/navcalc.h"
#include <XPLMUtilities.h>


FMSDatabase::FMSDatabase()
{
    m_path_airport = NAVDATA_AIRPORTS;
    m_path_runway = NAVDATA_RUNWAYS;
    m_path_navaid = NAVDATA_NAVAIDS;
    m_path_intersection = NAVDATA_FIXES;
    m_path_airway = NAVDATA_AIRWAYS;
};

void FMSDatabase::load()
{
    char msg[128];

    XPLMDebugString("[CRJ] Loading navdata.\n");

    loadAirports();
    loadRunways();
    sprintf(msg, "[CRJ] %d airports were loaded.\n", m_airport_map.size());
    XPLMDebugString(msg);

    loadNavaid();
    sprintf(msg, "[CRJ] %d ndb were loaded.\n", m_ndb_map.size());
    XPLMDebugString(msg);
    sprintf(msg, "[CRJ] %d vor were loaded.\n", m_vor_map.size());
    XPLMDebugString(msg);
    sprintf(msg, "[CRJ] %d ils were loaded.\n", m_ils_map.size());
    XPLMDebugString(msg);

    loadIntersections();
    sprintf(msg, "[CRJ] %d intersections were loaded.\n", m_intersection_map.size());
    XPLMDebugString(msg);

    loadAirways();
    sprintf(msg, "[CRJ] %d airways were loaded.\n", m_airway_map.size());
    XPLMDebugString(msg);

};

void FMSDatabase::loadAirports()
{
    ifstream file;
    string line;
    string id, lat, lon;
    int i;
    Airport *obj;

    file.open(m_path_airport.c_str());
    if(!file.is_open())
        return;

    while (getline(file, line))
    {
        if(line[0] != ';')
        {
            // ICAO
            id = "";
            for (i = 0; i < 4; i++)
                id += line[i];

            // Lat
            lat = "";
            for (i = 4; i < 14; i++)
                lat += line[i];

            // Lon
            lon = "";
            for (i = 14; i < 24; i++)
                lon += line[i];

            // create new object and add to map
            obj = new Airport(id.c_str(), "", atof(lat.c_str()), atof(lon.c_str()), 0);
            m_airport_map.insert(pair<string, Airport*>(id, obj));
        } else if (line.substr(1,5) == "AIRAC") {
            validity = line.substr(15);
        }
    }

    file.close();
};

void FMSDatabase::loadRunways()
{
    //char temp[16];
    ifstream file;
    string line;
    string apt, id, length, hdg, lat, lon, ils_freq, ils_hdg, elev;
    bool has_ils = false;
    int i;
    Airport *airport;
    //Runway *rwy;

    file.open(m_path_runway.c_str());
    if (!file.is_open()) {
        XPLMDebugString("Can't open runways\n");
        return;
    }

    while (getline(file, line))
    {
        if(line[0] != ';')
        {
            apt = "";
            for(i = 24; i < 28; i++)
                apt += line[i];

            id = "";
            id += line[28];
            id += line[29];
            if(line[30] != ' ')
                id += line[30];

            length = "";
            for(i = 31; i < 36; i++)
                length += line[i];

            hdg = "";
            for(i = 36; i < 39; i++)
                hdg += line[i];

            lat = "";
            for(i = 39; i < 49; i++)
                lat += line[i];

            lon = "";
            for(i = 49; i < 60; i++)
                lon += line[i];

            ils_freq = "";
            for(i = 60; i < 66; i++)
                ils_freq += line[i];

            ils_hdg = "";
            for(i = 66; i < 69; i++)
                ils_hdg += line[i];

            elev = "";
            for(i = 69; i < 74; i++)
                elev += line[i];

            if(atoi(ils_freq.c_str()) == 0)
                has_ils = false;
            else
                has_ils = true;

            if((airport = getAirport(apt)) != NULL)
            {
                airport->addRunway(Runway(id.c_str(), atof(lat.c_str()), atof(lon.c_str()),
                                          atoi(hdg.c_str()), 0, has_ils, atof(ils_freq.c_str())*1000,
                                          atoi(ils_hdg.c_str()), atoi(elev.c_str()), 0, 0));

                //sprintf(temp, "%s %s %d\n", apt.c_str(), id.c_str(), airport->runwayCount());
                //XPLMDebugString(temp);
                m_airport_map.insert(pair<string, Airport*>(apt, airport));
                //m_airport_map[apt] = airport;
            }
        }
    }

    file.close();
}

void FMSDatabase::loadNavaid()
{
    // char ce[128];
    ifstream file;
    string line;
    int i;
    // parse
    string id;
    string type;
    string lat;
    string lon;
    string freq;

    file.open(m_path_navaid.c_str());
    if (!file.is_open())
        return;
    // XPLMDebugString("file was opened\n");

    while (getline(file, line)) {
        id = "";
        for (i = 24; i < 29; i++) {
            if (line[i] == ' ')
                break;
            id += line[i];
        }

        type = "";
        for (i = 29; i < 33; i++) {
            if (line[i] == ' ')
                break;
            type += line[i];
        }

        lat = "";
        for (i = 33; i < 43; i++) {
            lat += line[i];
        }

        lon = "";
        for (i = 43; i < 54; i++) {
            lon += line[i];
        }

        freq = "";
        for (i = 54; i < 60; i++) {
            freq += line[i];
        }
        //sprintf(ce, "%s %s %s %s %s\n", id.c_str(), type.c_str(), lat.c_str(), lon.c_str(), freq.c_str());
        //XPLMDebugString(ce);

        if (type == "NDB") {
            Ndb *ndb_aid = new Ndb(id.c_str(), "", atof(lat.c_str()), atof(lon.c_str()),
                                   atof(freq.c_str())*100, 0, 0, "");
            //sprintf(ce, "NDB %s, %d\n", ndb_aid->id().toStdString().c_str(), ndb_aid->freq());
            //XPLMDebugString(ce);
            m_ndb_map.insert(pair<string, Ndb*>(id, ndb_aid));
        }
        if (type == "VOR") {
            Vor *vor_aid = new Vor(id.c_str(), "", atof(lat.c_str()), atof(lon.c_str()),
                                   atof(freq.c_str())*1000, false, 0, 0, "");
            m_vor_map.insert(pair<string, Vor*>(id, vor_aid));
        }
        if (type == "VORD") {
            Vor *vord_aid = new Vor(id.c_str(), "", atof(lat.c_str()), atof(lon.c_str()),
                                    atof(freq.c_str())*1000, true, 0, 0, "");
            m_vor_map.insert(pair<string, Vor*>(id, vord_aid));
        }
        if (type == "ILS") {
            Ils *ils_aid = new Ils(id.c_str(), "", atof(lat.c_str()), atof(lon.c_str()),
                                   atoi(freq.c_str())*1000, false, 0, 0, "", 0);
            m_ils_map.insert(pair<string, Ils*>(id, ils_aid));
        }
        if (type == "ILSD") {
            Ils *ilsd_aid = new Ils(id.c_str(), "", atof(lat.c_str()), atof(lon.c_str()),
                                    atoi(freq.c_str())*1000, true, 0, 0, "", 0);
            m_ils_map.insert(pair<string, Ils*>(id, ilsd_aid));
        }
    };

    file.close();
};

void FMSDatabase::loadIntersections()
{
    std::ifstream txtfile;
    std::string line;
    std::string name, icao, lat, lon;
    int i;

    // airport & runways
    txtfile.open(m_path_intersection.c_str());
    if (!txtfile.is_open()) {
        XPLMDebugString("[CRJAvionics ERROR]: Can't open fix\n");
        return;
    }

    while (getline(txtfile, line)) {
        if (line[0] != ';') {
            //NavPoint *fix = new NavPoint();

            name = "";
            for (i = 0; i < 24; i++) {
                if (line[i] == ' ')
                    break;
                name += line[i];
            }

            icao = "";
            for (i = 24; i < 29; i++) {
                if (line[i] == ' ')
                    break;
                icao += line[i];
            }

            lat = "";
            for (i = 29; i < 39; i++) {
                lat += line[i];
            }

            lon = "";
            for (i = 39; i < 50; i++) {
                lon += line[i];
            }

            Intersection *fix = new Intersection(icao.c_str(), icao.c_str(), atof(lat.c_str()),
                                                 atof(lon.c_str()), "");
            //			XPLMDebugString(fix->toString().toStdString().c_str());
            //			XPLMDebugString("\n");
            m_intersection_map.insert(pair<string, Intersection*>(icao, fix));
        }
    }

    txtfile.close();
};

void FMSDatabase::loadAirways()
{
    //char debug[256];
    ifstream file;
    string line;
    int i;
    //
    string name, icao, lat, lon, number;
    string last_name = "";
    Airway *rte = NULL;

    file.open(m_path_airway.c_str());
    if (!file.is_open())
        return;

    while (getline(file, line)) {
        if (line[0] != ';') {
            name = "";
            for (i = 0; i < 100; i++) {
                if (line[i] == ' ') {
                    i++;
                    break;
                };
                name += line[i];
            }
            number = "";
            for (i; i < 256; i++) {
                if (line[i] == ' ') {
                    i++;
                    break;
                }
                number += line[i];
            }
            icao = "";
            for (i+1; i < 256; i++) {
                if (line[i] == ' ') {
                    i++;
                    break;
                }
                icao += line[i];
            }
            lat = "";
            for (i+1; i < 256; i++) {
                if (line[i] == ' ') {
                    i++;
                    break;
                }
                lat += line[i];
            }
            lon = "";
            for (i+1; i < line.size(); i++) {
                /*if (line[i] == '\n') {
         i++;
         break;
         }*/
                lon += line[i];
            }
            //sprintf(debug, "%s %s %s %s %s\n", name.c_str(), number.c_str(), icao.c_str(), lat.c_str(), lon.c_str());
            //XPLMDebugString(debug);

            if (last_name != name) { // new route
                if (rte != NULL) {
                    m_airway_map.insert(pair<string, Airway*>(last_name, rte));
                }
                rte = new Airway(name.c_str());
                //sprintf(debug, "Create new route [ %s ]\n", name.c_str());
                //XPLMDebugString(debug);

                rte->appendWaypoint(Waypoint(icao.c_str(), "", atof(lat.c_str()), atof(lon.c_str())));
                //sprintf(debug, "Add point %s to route %s(%d)\n", icao.c_str(), name.c_str(), rte->Size());
                //XPLMDebugString(debug);

                last_name = name;
            }
            else { // new waypoint
                rte->appendWaypoint(Waypoint(icao.c_str(), "", atof(lat.c_str()), atof(lon.c_str())));
                //rte->AddNavPoint(icao, atof(lat.c_str()), atof(lon.c_str()));
                //sprintf(debug, "Add point %s to route %s(%d)\n", icao.c_str(), name.c_str(), rte->Size());
                //XPLMDebugString(debug);
            }
        }
    };

    file.close();
};

void FMSDatabase::loadProcedure(const string &name)
{
    char debug[256];
    string filename = NAVDATA_PROC;
    filename += name;
    filename += ".xml";

    TiXmlDocument doc(filename.c_str());
    if (!doc.LoadFile()) {
        XPLMDebugString("Can't open file.\n");
    }

    TiXmlHandle h_doc(&doc);
    TiXmlElement* pElem;
    TiXmlElement* subElem;
    TiXmlElement* sub2Elem;
    TiXmlHandle hRoot(0);
    TiXmlHandle hSid(0);
    TiXmlHandle hTrans(0);
    TiXmlHandle hWpt(0);
    TiXmlHandle hApp(0);

    ProcedureList procedure_list;
    Sid *m_sid = NULL;
    Star *m_star = NULL;
    Approach *m_approach = NULL;

    pElem=h_doc.FirstChildElement().Element();
    hRoot=TiXmlHandle(pElem);

    pElem = hRoot.FirstChild("Airport").FirstChild().Element();
    for(pElem; pElem; pElem=pElem->NextSiblingElement()) {
        string value = pElem->Value();
        if (value == "Sid") {
            // Create Sid
            QStringList m_rwy_list(pElem->Attribute("Runways"));
            m_sid = new Sid(pElem->Attribute("Name"), m_rwy_list);
            hSid = TiXmlHandle(pElem);
            subElem = hSid.FirstChild().Element();
            for (subElem; subElem; subElem=subElem->NextSiblingElement()) {
                value = subElem->Value();
                if (value == "Sid_Waypoint") {
                    Waypoint wpt = parseWaypoint(subElem, Waypoint::FLAG_SID);
                    if (wpt!=Waypoint())
                        m_sid->appendWaypoint(wpt);
                }
                if (value == "Sid_Transition") {
                    Transition *trans = new Transition(subElem->Attribute("Name"), m_rwy_list);
                    hTrans = TiXmlHandle(subElem);
                    sub2Elem = hTrans.FirstChild().Element();
                    for (sub2Elem; sub2Elem; sub2Elem=sub2Elem->NextSiblingElement()) {
                        Waypoint wpt = parseWaypoint(sub2Elem, Waypoint::FLAG_SID_TRANS);
                        if (wpt!=Waypoint())
                            trans->appendWaypoint(wpt);
                    }
                    m_sid->addTransition(trans);
                }
            }
            procedure_list.push_back(m_sid);
        }
        if (value == "Star") {
            QStringList m_rwy_list(pElem->Attribute("Runways"));
            m_star = new Star(pElem->Attribute("Name"), m_rwy_list);

            hSid = TiXmlHandle(pElem);
            subElem = hSid.FirstChild().Element();
            for (subElem; subElem; subElem=subElem->NextSiblingElement()) {
                value = subElem->Value();
                if (value == "Star_Waypoint") {
                    Waypoint wpt = parseWaypoint(subElem, Waypoint::FLAG_STAR);
                    if (wpt!=Waypoint())
                        m_star->appendWaypoint(wpt);
                }
                if (value == "Star_Transition") {
                    XPLMDebugString("Skip STAR Transition");
                }
            }
            procedure_list.push_back(m_star);
        }
        if (value == "Approach") {
            bool miss_app = false;
            m_approach = new Approach(pElem->Attribute("Name"), QStringList());
            hSid = TiXmlHandle(pElem);
            subElem = hSid.FirstChild().Element();
            for (subElem; subElem; subElem=subElem->NextSiblingElement()) {
                hApp = TiXmlHandle(subElem);
                value = subElem->Value();
                if (value == "App_Waypoint") {
                    if (!miss_app)
                    {
                        Waypoint wpt = parseWaypoint(subElem, Waypoint::FLAG_APPROACH);
                        if (wpt!=Waypoint())
                            m_approach->appendWaypoint(wpt);
                    } else {
                        Waypoint wpt = parseWaypoint(subElem, Waypoint::FLAG_MISSED_APPROACH);
                        if (wpt!=Waypoint())
                            m_sid->appendWaypoint(wpt);
                    }
                    if (hApp.FirstChild("Type").ToElement()->GetText() == "Runway")
                        miss_app = true;
                }
                if (value == "App_Transition") {
                    Transition *trans = new Transition(subElem->Attribute("Name"), QStringList());
                    hTrans = TiXmlHandle(subElem);
                    sub2Elem = hTrans.FirstChild().Element();
                    for (sub2Elem; sub2Elem; sub2Elem=sub2Elem->NextSiblingElement()) {
                        Waypoint wpt = parseWaypoint(sub2Elem, Waypoint::FLAG_APP_TRANS);
                        if (wpt!=Waypoint())
                            trans->appendWaypoint(wpt);
                    }
                    m_approach->addTransition(trans);
                }
            }
            procedure_list.push_back(m_approach);
        }
    }

    m_procedure_map.insert(pair<string, ProcedureList>(name, procedure_list));
};

Waypoint FMSDatabase::parseWaypoint(TiXmlElement *elem, const QString& flag)
{
    TiXmlHandle hWpt = TiXmlHandle(elem);
    string name, type, lat, lon;
    // Get Data
    name = hWpt.FirstChild("Name").ToElement()->GetText();
    type = hWpt.FirstChild("Type").ToElement()->GetText();
    lat = hWpt.FirstChild("Latitude").ToElement()->GetText();
    lon = hWpt.FirstChild("Longitude").ToElement()->GetText();

    // Create Waypoint
    if (type == "Normal") {
        string spd, alt, altcons, altrest, flytype, banklimit, turn;
        spd = hWpt.FirstChild("Speed").ToElement()->GetText();
        alt = hWpt.FirstChild("Altitude").ToElement()->GetText();
        altcons = hWpt.FirstChild("AltitudeCons").ToElement()->GetText();
        altrest = hWpt.FirstChild("AltitudeRestriction").ToElement()->GetText();
        flytype = hWpt.FirstChild("Flytype").ToElement()->GetText();
        banklimit = hWpt.FirstChild("BankLimit").ToElement()->GetText();
        turn = hWpt.FirstChild("Sp_Turn").ToElement()->GetText();

        Waypoint m_wpt(name.c_str(), "", atof(lat.c_str()), atof(lon.c_str()));
        m_wpt.restrictions().setSpeedRestrictionKts(atoi(spd.c_str()));
        m_wpt.restrictions().setAltitudeRestrictionFt(atoi(alt.c_str()));
        if (altrest == "at")
            m_wpt.restrictions().setAltitudeRestrictionType(WaypointRestrictions::RESTRICTION_ALT_EQUAL);
        else if (altrest == "above")
            m_wpt.restrictions().setAltitudeRestrictionType(WaypointRestrictions::RESTRICTION_ALT_GREATER);
        else
            m_wpt.restrictions().setAltitudeRestrictionType(WaypointRestrictions::RESTRICTION_ALT_SMALLER);
        if (flytype == "Fly-by")
            m_wpt.restrictions().setOverflyRestriction(false);
        else
            m_wpt.restrictions().setOverflyRestriction(true);
        if (turn == "Right")
            m_wpt.restrictions().setTurnRestriction(WaypointRestrictions::RESTRICTION_TURN_RIGHT);
        if (turn == "Left")
            m_wpt.restrictions().setTurnRestriction(WaypointRestrictions::RESTRICTION_TURN_LEFT);
        m_wpt.setFlag(flag);
        return m_wpt;
    }
    else if (type == "Runway") {
        string spd, alt, altcons, altrest, flytype, banklimit, turn;
        spd = hWpt.FirstChild("Speed").ToElement()->GetText();
        alt = hWpt.FirstChild("Altitude").ToElement()->GetText();
        altcons = hWpt.FirstChild("AltitudeCons").ToElement()->GetText();
        altrest = hWpt.FirstChild("AltitudeRestriction").ToElement()->GetText();
        flytype = hWpt.FirstChild("Flytype").ToElement()->GetText();
        banklimit = hWpt.FirstChild("BankLimit").ToElement()->GetText();
        turn = hWpt.FirstChild("Sp_Turn").ToElement()->GetText();

        Waypoint m_wpt(name.c_str(), "", atof(lat.c_str()), atof(lon.c_str()));
        m_wpt.restrictions().setSpeedRestrictionKts(atoi(spd.c_str()));
        m_wpt.restrictions().setAltitudeRestrictionFt(atoi(alt.c_str()));
        if (altrest == "at")
            m_wpt.restrictions().setAltitudeRestrictionType(WaypointRestrictions::RESTRICTION_ALT_EQUAL);
        else if (altrest == "above")
            m_wpt.restrictions().setAltitudeRestrictionType(WaypointRestrictions::RESTRICTION_ALT_GREATER);
        else
            m_wpt.restrictions().setAltitudeRestrictionType(WaypointRestrictions::RESTRICTION_ALT_SMALLER);
        if (flytype == "Fly-by")
            m_wpt.restrictions().setOverflyRestriction(false);
        else
            m_wpt.restrictions().setOverflyRestriction(true);
        if (turn == "Right")
            m_wpt.restrictions().setTurnRestriction(WaypointRestrictions::RESTRICTION_TURN_RIGHT);
        if (turn == "Left")
            m_wpt.restrictions().setTurnRestriction(WaypointRestrictions::RESTRICTION_TURN_LEFT);
        m_wpt.setFlag(flag);
        return m_wpt;
    }
    else if (type == "Hold") {
        string spd, alt, altcons, altrest, flytype, banklimit, turn;
        spd = hWpt.FirstChild("Speed").ToElement()->GetText();
        alt = hWpt.FirstChild("Altitude").ToElement()->GetText();
        altcons = hWpt.FirstChild("AltitudeCons").ToElement()->GetText();
        altrest = hWpt.FirstChild("AltitudeRestriction").ToElement()->GetText();
        flytype = hWpt.FirstChild("Flytype").ToElement()->GetText();
        banklimit = hWpt.FirstChild("BankLimit").ToElement()->GetText();
        turn = hWpt.FirstChild("Sp_Turn").ToElement()->GetText();

        Waypoint m_wpt(name.c_str(), "", atof(lat.c_str()), atof(lon.c_str()));
        m_wpt.restrictions().setSpeedRestrictionKts(atoi(spd.c_str()));
        m_wpt.restrictions().setAltitudeRestrictionFt(atoi(alt.c_str()));
        if (altrest == "at")
            m_wpt.restrictions().setAltitudeRestrictionType(WaypointRestrictions::RESTRICTION_ALT_EQUAL);
        else if (altrest == "above")
            m_wpt.restrictions().setAltitudeRestrictionType(WaypointRestrictions::RESTRICTION_ALT_GREATER);
        else
            m_wpt.restrictions().setAltitudeRestrictionType(WaypointRestrictions::RESTRICTION_ALT_SMALLER);
        if (flytype == "Fly-by")
            m_wpt.restrictions().setOverflyRestriction(false);
        else
            m_wpt.restrictions().setOverflyRestriction(true);
        if (turn == "Right")
            m_wpt.restrictions().setTurnRestriction(WaypointRestrictions::RESTRICTION_TURN_RIGHT);
        if (turn == "Left")
            m_wpt.restrictions().setTurnRestriction(WaypointRestrictions::RESTRICTION_TURN_LEFT);
        m_wpt.setFlag(flag);
        m_wpt.setId(m_wpt.id().append(" (HOLD)"));
        return m_wpt;
    }
    else if (type == "ConstHdgtoAlt") {
        string spd, alt, altcons, altrest, flytype, banklimit, turn, hdg_crs, hdg_crs_value;
        spd = hWpt.FirstChild("Speed").ToElement()->GetText();
        alt = hWpt.FirstChild("Altitude").ToElement()->GetText();
        altcons = hWpt.FirstChild("AltitudeCons").ToElement()->GetText();
        altrest = hWpt.FirstChild("AltitudeRestriction").ToElement()->GetText();
        flytype = hWpt.FirstChild("Flytype").ToElement()->GetText();
        banklimit = hWpt.FirstChild("BankLimit").ToElement()->GetText();
        turn = hWpt.FirstChild("Sp_Turn").ToElement()->GetText();
        hdg_crs = hWpt.FirstChild("Hdg_Crs").ToElement()->GetText();
        hdg_crs_value = hWpt.FirstChild("Hdg_Crs_value").ToElement()->GetText();

        Waypoint a_wpt(name.c_str(), "", 0.0, 0.0);
        a_wpt.setTypeHdgToAlt();
        a_wpt.restrictions().setSpeedRestrictionKts(atoi(spd.c_str()));
        a_wpt.restrictions().setAltitudeRestrictionFt(atoi(alt.c_str()));
        if (altrest == "at")
            a_wpt.restrictions().setAltitudeRestrictionType(WaypointRestrictions::RESTRICTION_ALT_EQUAL);
        else if (altrest == "above")
            a_wpt.restrictions().setAltitudeRestrictionType(WaypointRestrictions::RESTRICTION_ALT_GREATER);
        else
            a_wpt.restrictions().setAltitudeRestrictionType(WaypointRestrictions::RESTRICTION_ALT_SMALLER);
        if (flytype == "Fly-by")
            a_wpt.restrictions().setOverflyRestriction(false);
        else
            a_wpt.restrictions().setOverflyRestriction(true);
        if (turn == "Right")
            a_wpt.restrictions().setTurnRestriction(WaypointRestrictions::RESTRICTION_TURN_RIGHT);
        if (turn == "Left")
            a_wpt.restrictions().setTurnRestriction(WaypointRestrictions::RESTRICTION_TURN_LEFT);
        a_wpt.setHdgToHold(atoi(hdg_crs_value.c_str()));
        a_wpt.setFlag(flag);
        a_wpt.setId("(INTC)");

        //XPLMDebugString(a_wpt.toString().toStdString().c_str());
        //XPLMDebugString("\n");

        return a_wpt;
    }
    else {
        return Waypoint();
    }
};

Airport* FMSDatabase::getAirport(const std::string &id)
{
    AirportMapIterator i = m_airport_map.find(id);
    if(i != m_airport_map.end())
        return (Airport*)(*i).second;
    else
        return NULL;
};

ProcedureList FMSDatabase::getProcedure(const std::string &id)
{
    ProcedureMapIterator i = m_procedure_map.find(id);
    if (i != m_procedure_map.end())
        return (*i).second;
    else {
        ProcedureList list;
        return list;
    }
};

ProcedureList FMSDatabase::getSids(const std::string &id)
{
    ProcedureList sids_list;

    ProcedureList apt_list = getProcedure(id);
    if (apt_list.size() != 0) {
        int i;
        for (i = 0; i < apt_list.size(); i++) {
            if (apt_list[i]->type() == Route::TYPE_SID) {
                sids_list.push_back(apt_list[i]);
            }
        }
    }
    return sids_list;
};

ProcedureList FMSDatabase::getSids(const std::string &id, const std::string &rwy)
{
    ProcedureList sids_list;

    ProcedureList apt_list = getProcedure(id);
    if (apt_list.size() != 0) {
        int i;
        for (i = 0; i < apt_list.size(); i++) {
            if (apt_list[i]->type() == Route::TYPE_SID) {
                QStringList rwy_list = apt_list[i]->runwayList();
                int j;
                bool has_rwy = false;
                for (j = 0; j < rwy_list.size(); j++) {
                    if (rwy_list.at(j).toStdString() == rwy)
                        has_rwy = true;
                }
                if (has_rwy)
                    sids_list.push_back(apt_list[i]);
            }
        }
    }
    return sids_list;
};

ProcedureList FMSDatabase::getSidTrans(const string &id, const string &sid)
{
    ProcedureList sid_trans;
    int i;

    ProcedureList apt_list = getProcedure(id);
    if (apt_list.size() != 0) {
        for (i = 0; i < apt_list.size(); i++) {
            if (apt_list[i]->type() == Route::TYPE_SID && apt_list[i]->id() == sid.c_str()) {
                Sid *sid = (Sid*)apt_list[i];
                sid_trans = sid->transitions();
            }
        }
    }

    return sid_trans;
}

ProcedureList FMSDatabase::getStar(const QString &id)
{
    ProcedureList star_list;

    ProcedureList apt_list = getProcedure(id.toStdString().c_str());
    if (apt_list.size() != 0) {
        int i;
        for (i = 0; i < apt_list.size(); i++) {
            if (apt_list[i]->type() == Route::TYPE_STAR) {
                star_list.push_back(apt_list[i]);
            }
        }
    }
    return star_list;
}

ProcedureList FMSDatabase::getAppr(const QString &id)
{
    ProcedureList star_list;

    ProcedureList apt_list = getProcedure(id.toStdString().c_str());
    if (apt_list.size() != 0) {
        int i;
        for (i = 0; i < apt_list.size(); i++) {
            if (apt_list[i]->type() == Route::TYPE_APPROACH) {
                star_list.push_back(apt_list[i]);
            }
        }
    }
    return star_list;
}

ProcedureList FMSDatabase::getApprTrans(const string &id, const string &app)
{
    ProcedureList app_trans;
    int i;

    ProcedureList apt_list = getProcedure(id);
    if (apt_list.size() != 0) {
        for (i = 0; i < apt_list.size(); i++) {
            if (apt_list[i]->type() == Route::TYPE_APPROACH && apt_list[i]->id() == app.c_str()) {
                Approach *app = (Approach*)apt_list[i];
                app_trans = app->transitions();
            }
        }
    }

    return app_trans;
}

void FMSDatabase::getNdb(const std::string &id, StdWaypointList *list)
{
    int cnt = m_ndb_map.count(id);
    if (cnt != 0) {
        NdbMapIterator it = m_ndb_map.find(id);
        int i;
        for (i = 0; i < cnt; i++) {
            Waypoint *wpt = (*it).second->asWaypoint();
            list->push_back(wpt);
            it++;
        }
    }
};

void FMSDatabase::getVor(const std::string &id,  StdWaypointList *list)
{
    int cnt = m_vor_map.count(id);
    if (cnt != 0) {
        VorMapIterator it = m_vor_map.find(id);
        int i;
        for (i = 0; i < cnt; i++) {
            list->push_back((*it).second->asWaypoint());
            it++;
        }
    }
};

void FMSDatabase::getIls(const std::string &id,  StdWaypointList *list)
{
    int cnt = m_ils_map.count(id);
    if (cnt != 0) {
        IlsMapIterator it = m_ils_map.find(id);
        int i;
        for (i = 0; i < cnt; i++) {
            list->push_back((*it).second->asWaypoint());
            it++;
        }
    }
};

void FMSDatabase::getFix(const std::string &id,  StdWaypointList *list)
{
    int cnt = m_intersection_map.count(id);
    if (cnt != 0) {
        IntersectionMapIterator it = m_intersection_map.find(id);
        int i;
        for (i = 0; i < cnt; i++) {
            Waypoint *wpt = (*it).second->asWaypoint();
            if (wpt->id().toStdString() == id)
                list->push_back(wpt);
            it++;
        }
    }
};

Airway* FMSDatabase::getAirway(const std::string &id)
{
    AirwayMapIterator it = m_airway_map.find(id);
    if (it != m_airway_map.end())
        return (*it).second;
    else
        return NULL;
}

void FMSDatabase::getVorByCoordinates(const Waypoint& current_position,
                                      int distance_nm,
                                      StdWaypointList *list)
{
    VorMapIterator it = m_vor_map.begin();
    while (it != m_vor_map.end()) {
        Vor *vor = (*it).second;
        if (Navcalc::getDistBetweenWaypoints(current_position, *vor) < distance_nm) {
            list->push_back(vor);
        }
        it++;
    }
};

void FMSDatabase::getFixByCoordinates(const Waypoint& current_position,
                                      int distance_nm,
                                      StdWaypointList *list)
{
    IntersectionMapIterator it = m_intersection_map.begin();
    while (it != m_intersection_map.end()) {
        Intersection *fix = (*it).second;
        if (Navcalc::getDistBetweenWaypoints(current_position, *fix) < distance_nm) {
            list->push_back(fix);
        }
        it++;
    }
};

void FMSDatabase::getAptByCoordinates(const Waypoint& current_position,
                                      int distance_nm,
                                      StdWaypointList *list)
{
    AirportMapIterator it = m_airport_map.begin();
    while (it != m_airport_map.end()) {
        Airport *apt = (*it).second;
        if (Navcalc::getDistBetweenWaypoints(current_position, *apt) < distance_nm) {
            list->push_back(apt);
        }
        it++;
    }
};

void FMSDatabase::getNdbByCoordinates(const Waypoint& current_position,
                                      int distance_nm,
                                      StdWaypointList *list)
{
    NdbMapIterator it = m_ndb_map.begin();
    while (it != m_ndb_map.end()) {
        Ndb *ndb = (*it).second;
        if (Navcalc::getDistBetweenWaypoints(current_position, *ndb) < distance_nm) {
            list->push_back(ndb);
        }
        it++;
    }
};
