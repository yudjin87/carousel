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

#ifndef FEATURERENDERER_H
#define FEATURERENDERER_H

#include "display_api.h"

#include <QtCore/QList>

#include <QtGui/QPen>
#include <QtGui/QBrush>

class AbstractGeometry;
class QAbstractGraphicsShapeItem;
class QGraphicsScene;

class DISPLAY_API FeatureRenderer
{
public:
    FeatureRenderer();
    ~FeatureRenderer();

    const QPen &pen() const { return m_pen;}
    const QBrush &brush() const { return m_brush;}

    void setPen(const QPen &pen) {m_pen = pen;}
    void setBrush(const QBrush &brush){m_brush = brush;}

//    QList<QAbstractGraphicsShapeItem *> *drawPoint(const AbstractGeometry *pointGeometry);
//    QList<QAbstractGraphicsShapeItem *> *drawPolygon(const AbstractGeometry *polygonGeometry);
//    QList<QAbstractGraphicsShapeItem *> *drawPolyline(const AbstractGeometry *polylineGeometry);

//    void setScene(QGraphicsScene *scene);

private:
    //QGraphicsScene *mp_scene;
    QPen m_pen;
    QBrush m_brush;
};

#endif // FEATURERENDERER_H

