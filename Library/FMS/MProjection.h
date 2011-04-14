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

#ifndef MProjection_h
#define MProjection_h

#include "waypoint.h"
#include "navcalc.h"

class Projection {
public:
    Projection() : m_xy_scale_factor(1.0) {}
    virtual ~Projection() {}

    //! Sets the center and the scale of the projection, where the center
    //! lat/lon will result in (0/0) x/y coordinates, and the lat/lon points
    //! at range 20nm will have a (max.) distance of "drawing_dist_at_max_range"
    //! from the (0/0) x/y coordinate.
    virtual void setScaleAndCenter(const Waypoint& center_wpt,
                                   unsigned int range_nm,
                                   unsigned int drawing_dist_at_max_range);

    //! Converts the given lat/lon values to x/y.
    //! (QPointF: x = lat , y=lon)
    bool convertLatLonToXY(const QPointF& latlon_point, QPointF& xy_point) const;

    //! Converts the given x/y to lat/lon values.
    //! (QPointF: x = lat , y=lon)
    bool convertXYToLatLon(const QPointF& xy_point, QPointF& latlon_point) const;

protected:

    QPointF m_center_xy;
    double m_xy_scale_factor;

    //! lat/lon center of the projection
    Waypoint m_center_latlon;

    //! the range of the projection
    unsigned int m_range_nm;
    unsigned int m_drawing_dist_at_max_range;
};

#endif //MProjection_h
