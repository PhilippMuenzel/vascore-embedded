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


#ifndef icaoroute_h
#define icaoroute_h

#include "route.h"
#include "waypoint.h"
#include <vector>

using namespace std;

typedef struct {
    Route *via;
    Waypoint *to;
} ICAOPair;

typedef vector<ICAOPair> ICAOPairList;

class ICAORoute {
public:
    ICAORoute() {}
    virtual ~ICAORoute() {}

    //void appendVia(Route *via);
    //void appendTo(Waypoint *to);
    void appendViaTo(ICAOPair via_to) { m_icao_route.push_back(via_to); }

    int count() { return m_icao_route.size(); }

private:
    ICAOPairList m_icao_route;
};

#endif /* icaoroute_h */
