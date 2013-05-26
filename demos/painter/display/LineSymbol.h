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

#ifndef LINESYMBOL_H
#define LINESYMBOL_H

#include "display/SymbolBase.h"

#include <QtGui/QColor>

class DISPLAY_API LineSymbol : public SymbolBase
{
    Q_OBJECT
    /*!
     * @details
     *   Gets or sets the line symbol width.
     */
    Q_PROPERTY(double width READ width WRITE setWidth)

    /*!
     * @details
     *   Gets or sets the line symbol color.
     */
    Q_PROPERTY(QColor color READ color WRITE setColor)
public:
    QColor color() const;
    void setColor(const QColor &color);

    double width() const;
    void setWidth(double width);

protected:
    explicit LineSymbol(QObject *parent = 0);

private:
    double m_width;
    QColor m_color;
};


#endif // LINESYMBOL_H