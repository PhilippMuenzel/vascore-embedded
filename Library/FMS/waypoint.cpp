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


#include "navcalc.h"

#include "waypoint.h"

/////////////////////////////////////////////////////////////////////////////

QString WaypointRestrictions::speedAndAltitudeRestrictionText() const
{
    QString text;
    if (m_speed_restriction_kts > 0)
        text += QString::number(m_speed_restriction_kts) + "/";
    else
        text += "---/";
    text += altitudeRestrictionText();
    return text;
}

/////////////////////////////////////////////////////////////////////////////

QString WaypointRestrictions::speedRestrictionText() const
{
    return QString::number(m_speed_restriction_kts);
}

/////////////////////////////////////////////////////////////////////////////

QString WaypointRestrictions::altitudeRestrictionText() const
{
    if (m_altitude_restriction_ft != 0) {
        if (altitudeGreaterRestriction())      return QString("A") + QString::number(m_altitude_restriction_ft);
        else if (altitudeSmallerRestriction()) return QString("B") + QString::number(m_altitude_restriction_ft);
        else                                   return QString::number(m_altitude_restriction_ft);
    }
    else {
        return "-----";
    }

}

/////////////////////////////////////////////////////////////////////////////

bool WaypointRestrictions::setSpeedAndAltitudeRestrictionFromText(const QString& text)
{
    uint speed = 0;
    QString alt_text;
    bool convok = false;

    if (text.contains("/"))
    {
        speed = text.section('/', 0, 0).toUInt(&convok);
        if (!convok || speed > 999 || speed < 50) return false;

        if (!text.endsWith("/")) alt_text = text.section('/', 1, 1);
    }
    else
    {
        alt_text = text;
    }

    uint alt = 0;
    if (!alt_text.isEmpty()) alt = qAbs(alt_text.toInt(&convok));
    if (!convok || alt > 99999) return false;

    if (speed != 0) m_speed_restriction_kts = speed;
    if (alt != 0)
    {
        m_altitude_restriction_ft = alt;
        if (alt_text.startsWith("-"))      m_altitude_restriction_type = WaypointRestrictions::RESTRICTION_ALT_SMALLER;
        else if (alt_text.startsWith("+")) m_altitude_restriction_type = WaypointRestrictions::RESTRICTION_ALT_GREATER;
        else                           m_altitude_restriction_type = WaypointRestrictions::RESTRICTION_ALT_EQUAL;
    }

    return true;
}

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

const double Waypoint::LAT_LON_COMPARE_EPSILON = 0.0001;

const QString Waypoint::TYPE_WAYPOINT = "WAYPOINT";
const QString Waypoint::TYPE_AIRPORT = "AIRPORT";
const QString Waypoint::TYPE_RUNWAY = "RUNWAY";
const QString Waypoint::TYPE_INTERSECTION = "INTERSECTION";
const QString Waypoint::TYPE_NDB = "NDB";
const QString Waypoint::TYPE_VOR = "VOR";
const QString Waypoint::TYPE_ILS = "ILS";
const QString Waypoint::TYPE_ALL = "ALL";
const QString Waypoint::TYPE_HDG_TO_ALT = "HDG2ALT";
const QString Waypoint::TYPE_HDG_TO_INTERCEPT = "HDG2INTERCEPT";

const QString Waypoint::FLAG_ADEP = "ADEP";
const QString Waypoint::FLAG_SID = "SID";
const QString Waypoint::FLAG_SID_TRANS = "SID_TRANS";
const QString Waypoint::FLAG_TOP_OF_CLIMB = "T/C";
const QString Waypoint::FLAG_END_OF_DESCENT = "E/D";
const QString Waypoint::FLAG_TOP_OF_DESCENT = "T/D";
const QString Waypoint::FLAG_STAR = "STAR";
const QString Waypoint::FLAG_APP_TRANS = "APP_TRANS";
const QString Waypoint::FLAG_APPROACH = "APP";
const QString Waypoint::FLAG_ADES = "ADES";
const QString Waypoint::FLAG_MISSED_APPROACH = "MISSED";
const QString Waypoint::FLAG_DCT = "DCT";
const QString Waypoint::FLAG_DISCONTINUITY = "DISC";

/////////////////////////////////////////////////////////////////////////////

Waypoint::Waypoint() :
    m_is_valid(false), m_type(TYPE_WAYPOINT)
{
}

/////////////////////////////////////////////////////////////////////////////

Waypoint::Waypoint(const QString& id, const QString& name, const double &lat, const double& lon) :
    m_is_valid(true), m_type(TYPE_WAYPOINT), m_id(id.trimmed()), m_name(name.trimmed()),
    m_polar_coordinates(QPointF(lat, lon))
{
}

/////////////////////////////////////////////////////////////////////////////

QString Waypoint::toString() const
{
    return QString("Waypoint: %1, %2, %3, %4").arg(m_type).arg(m_id).arg(m_name).arg(latLonString());
}

/////////////////////////////////////////////////////////////////////////////

QString Waypoint::latString() const
{
    if (m_polar_coordinates.x() < 0) return QString("S") + QString::number(-m_polar_coordinates.x(), 'f', 7);
    else                             return QString("N") + QString::number(m_polar_coordinates.x(), 'f', 7);
}

/////////////////////////////////////////////////////////////////////////////

QString Waypoint::latStringDegMinSec() const
{
    double minutes = 60.0 * (lat() - ((int)lat()));
    int seconds = (int)((minutes - ((int)minutes)) * 100);
    QString lat_string;
    (lat() < 0) ? lat_string += "S" : lat_string += "N";
    lat_string += QString("%1 %2.%3").arg(qAbs((int)lat()), 2, 10, QChar('0')).
            arg(qAbs((int)minutes), 2, 10, QChar('0')).arg(qAbs(seconds),
                                                           2, 10, QChar('0'));
    return lat_string;
};

/////////////////////////////////////////////////////////////////////////////

QString Waypoint::lonString() const
{
    if (m_polar_coordinates.y() < 0) return QString("W") + QString::number(-m_polar_coordinates.y(), 'f', 7);
    else                             return QString("E") + QString::number(m_polar_coordinates.y(), 'f', 7);
};

/////////////////////////////////////////////////////////////////////////////

QString Waypoint::lonStringDegMinSec() const
{
    double minutes = 60.0 * (lon() - ((int)lon()));
    int seconds = (int)((minutes - ((int)minutes)) * 100);
    QString lon_string;
    (lon() < 0) ? lon_string += "W" : lon_string += "E";
    lon_string += QString("%1 %2.%3").arg(qAbs((int)lon()), 3, 10, QChar('0')).
            arg(qAbs((int)minutes), 2, 10, QChar('0')).arg(qAbs(seconds),
                                                           2, 10, QChar('0'));
    return lon_string;
};

/////////////////////////////////////////////////////////////////////////////

bool Waypoint::operator==(const Waypoint& other) const
{
    if (m_id != other.m_id) return false;
    if (qAbs(m_polar_coordinates.x() - other.m_polar_coordinates.x()) > LAT_LON_COMPARE_EPSILON) return false;
    if (qAbs(m_polar_coordinates.y() - other.m_polar_coordinates.y()) > LAT_LON_COMPARE_EPSILON) return false;
    return true;
}

/////////////////////////////////////////////////////////////////////////////

bool Waypoint::operator!=(const Waypoint& other) const
{
    return ! operator==(other);

}

/////////////////////////////////////////////////////////////////////////////

const Waypoint& Waypoint::operator=(const Waypoint& other)
{
    m_is_valid = other.m_is_valid;
    m_id = other.m_id;
    m_name = other.m_name;
    m_parent = other.m_parent;
    m_flag = other.m_flag;

    m_polar_coordinates = other.m_polar_coordinates;
    m_cartesian_coordinates = other.m_cartesian_coordinates;

    m_restrictions = other.m_restrictions;
    m_estimated_data = other.m_estimated_data;
    m_overflown_data = other.m_overflown_data;
    m_holding = other.m_holding;
    return *this;
}

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////

bool Waypoint::isDependendWaypoint() const
{
    return
            asWaypointHdgToAlt() != 0 ||
            asWaypointHdgToIntercept() != 0;
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

void WaypointPtrList::sortByDistance(const Waypoint& reference_wpt)
{
    for (int loop_index=0; loop_index < count() ; ++loop_index)
    {
        for (int compare_index=0; compare_index < count() - 1 - loop_index; ++compare_index)
        {
            if (Navcalc::getDistBetweenWaypoints(reference_wpt, *at(compare_index)) >
                    Navcalc::getDistBetweenWaypoints(reference_wpt, *at(compare_index+1)))
            {
                Waypoint* wpt = takeAt(compare_index);
                insert(compare_index+1, wpt);
            }
        }
    }
}

