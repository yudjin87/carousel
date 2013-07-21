/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * Carousel - Qt-based managed component library.
 *
 * Copyright: 2011-2013 Carousel team
 * Authors:
 *   Eugene Chuguy <eugene.chuguy@gmail.com>
 *
 * This program or library is free software; you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 
 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA
 *
 * END_COMMON_COPYRIGHT_HEADER */

#include "SimpleLineSymbol.h"

#include <geometry/Polyline.h>
#include <geometry/Segment.h>
#include <geometry/Ring.h>

#include <QtGui/QPainter>

//------------------------------------------------------------------------------
SimpleLineSymbol::SimpleLineSymbol(QObject *parent)
    : LineSymbol(parent)
    , m_pen()
{
    m_pen.setCosmetic(true);
}

//------------------------------------------------------------------------------
void SimpleLineSymbol::setupPainter(QPainter *painter)
{
    LineSymbol::setupPainter(painter);

    m_pen.setColor(color());

    painter->setPen(m_pen);
}

//------------------------------------------------------------------------------
Qt::PenStyle SimpleLineSymbol::style() const
{
    return m_pen.style();
}

//------------------------------------------------------------------------------
void SimpleLineSymbol::setStyle(Qt::PenStyle style)
{
    m_pen.setStyle(style);
}

//------------------------------------------------------------------------------
void SimpleLineSymbol::drawPolyline(const Polyline &polyline, QPainter &painter)
{
    foreach(const Ring *ring, polyline.rings()) {
        foreach(const Segment *segment, ring->segments()) {
            painter.drawPolyline(segment->curve());
        }
    }
}

//------------------------------------------------------------------------------
