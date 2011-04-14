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


#ifndef APPROACH_H
#define APPROACH_H

#include "procedure.h"

/////////////////////////////////////////////////////////////////////////////

class Approach : public Procedure
{
public:

    Approach();

    Approach(const QString& id, const QStringList& runway_list);

    virtual ~Approach() {};

    virtual const Approach* asApproach() const { return this; }
    virtual Approach* asApproach() { return this; }

    virtual QString toString() const;

    const ProcedureList& transitions() const { return m_transition_list; }
    ProcedureList& transitions() { return m_transition_list; }

    void addTransition(Transition *trans_to_add) { m_transition_list.push_back((Procedure*)trans_to_add); }

    const QString& runway() const;
protected:

    ProcedureList m_transition_list;
};

#endif
