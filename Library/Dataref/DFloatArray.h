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

#ifndef DFloatArray_h
#define DFloatArray_h

#include <XPLMDataAccess.h>
#include <string>
using namespace std;

class DFloatArray {
public:
    DFloatArray() {}
    virtual ~DFloatArray() {}

    void find(string path) { m_dataref = XPLMFindDataRef(path.c_str()); }

    float get(int index)
    {
        float val;
        XPLMGetDatavf(m_dataref, &val, index, 1);
        return val;
    }

    void set(int index, float *value)
    {
        XPLMSetDatavf(m_dataref, value, index, 1);
    }

private:
    XPLMDataRef m_dataref;
};

#endif
