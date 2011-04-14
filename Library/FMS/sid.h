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

#ifndef SID_H
#define SID_H

#include "procedure.h"
#include <vector>
using namespace std;

/////////////////////////////////////////////////////////////////////////////

typedef vector<Transition*> TransitionList;

class Sid : public Procedure
{
public:
    Sid();

    Sid(const QString& id, const QStringList& runway_list);

    virtual ~Sid() {};

    virtual const Sid* asSID() const { return this; }
    virtual Sid* asSID() { return this; }

    virtual QString toString() const;

    void addTransition(Transition *trans_to_add) { m_transition_list.push_back((Procedure*)trans_to_add); }
    ProcedureList transitions() { return m_transition_list; }

protected:
    ProcedureList m_transition_list;
};

#endif
