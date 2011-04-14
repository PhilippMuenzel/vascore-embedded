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

#ifndef DIntegerArray_h
#define DIntegerArray_h

#include <XPLMDataAccess.h>
#include <string>
using namespace std;

class DIntegerArray {
public:
    DIntegerArray() {}
    virtual ~DIntegerArray() {}

    void find(string path) { m_dataref = XPLMFindDataRef(path.c_str()); }

    char get(int index)
    {
        char val;
        XPLMGetDatab(m_dataref, &val, index, 1);
        return val;
    }

    int size()
    {
        return XPLMGetDatavi(m_dataref, NULL, 0, 500);
    }

    void set(int index, int *value)
    {
        XPLMSetDatavi(m_dataref, value, index, 1);
    }

    string getAsChar()
    {
        string text = "";
        int i;
        for (i = 0; i < 10; i++) {
            char ch;
            ch = get(i);
            text += ch;
        }
        return text;
    }

private:
    XPLMDataRef m_dataref;
};


#endif
