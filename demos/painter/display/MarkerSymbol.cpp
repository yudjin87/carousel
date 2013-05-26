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

#include "MarkerSymbol.h"

#include <stdlib.h>

//------------------------------------------------------------------------------
MarkerSymbol::MarkerSymbol(QObject *parent)
    : SymbolBase(parent)
    , m_angle(0)
    , m_size(10)
    , m_color(QColor(rand() % 255, rand() % 255, rand() % 255))
{
}

//------------------------------------------------------------------------------
double MarkerSymbol::angle() const
{
    return m_angle;
}

//------------------------------------------------------------------------------
void MarkerSymbol::setAngle(double angle)
{
    m_angle = angle;
}

//------------------------------------------------------------------------------
double MarkerSymbol::size() const
{
    return m_size;
}

//------------------------------------------------------------------------------
void MarkerSymbol::setSize(double size)
{
    m_size = size;
}

//------------------------------------------------------------------------------
QColor MarkerSymbol::color() const
{
    return m_color;
}

//------------------------------------------------------------------------------
void MarkerSymbol::setColor(const QColor &color)
{
    m_color = color;
}

//------------------------------------------------------------------------------