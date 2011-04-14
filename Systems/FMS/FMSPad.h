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


#ifndef FMSPad_h
#define FMSPad_h

#include <stdlib.h>
#include <string>
#include "FMSData.h"
#include "../../Library/FMS/waypoint.h"
#include "../../../CRJ/Systems/FMS/IFMSPad.h"

#define DEL_MSG     "DEL@"

using namespace std;

class FMSPad : public IFMSPad {
public:
    FMSPad();

    void push(const string &str);
    string pop() { return m_pad_text; }
    QString qpop() { return QString::fromStdString(m_pad_text); }
    void clear() {
        if (m_pad_text.length() != 0) m_pad_text.resize(m_pad_text.length()-1);
    }
    void clearAll() { m_pad_text = ""; }

    void pushData(Waypoint *wpt) { m_data = wpt; }
    Waypoint* popData() { return m_data; }
    void clearData() { m_data = NULL; }

private:

    string m_pad_text;
    bool m_del_flag;

    Waypoint *m_data;
};

#endif /* FMSPad_h */
