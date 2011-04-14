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

#ifndef DFloat_h
#define DFloat_h

#include <XPLMDataAccess.h>
#include <string>
using namespace std;

class DFloat {
public:
    DFloat() {}
    virtual ~DFloat() {}

    void share(string path, float value)
    {
        XPLMShareData(path.c_str(), xplmType_Float, NULL, NULL);
        find(path);
        set(value);
    }
    void find(string path) { dataref = XPLMFindDataRef(path.c_str()); }

    float get() { return XPLMGetDataf(dataref); }
    void set(float value) { XPLMSetDataf(dataref, value); m_value = value; }

    bool check()
    {
        if (m_value == get())
            return false;
        else
            return true;
    }

    void save() { m_value = get(); }
    void undo() { set(m_value); }

private:
    XPLMDataRef dataref;
    float m_value;
};

#endif
