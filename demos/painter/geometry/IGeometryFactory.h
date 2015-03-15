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

#ifndef IGEOMETRYFACTORY_H
#define IGEOMETRYFACTORY_H

#include "geometry_api.h"
#include "GeometryType.h"

#include <QtCore/QObject>

#include <memory>

class AbstractGeometry;

class GEOMETRY_API IGeometryFactory : public QObject
{
    Q_OBJECT
public:
    IGeometryFactory(){}
    virtual ~IGeometryFactory(){}

public slots:
    virtual Geometry::Type geometryTypeFromShapeType(int shapeType) const = 0;
    virtual AbstractGeometry *createGeometry(int bytesCount, const char *geometryBlob) const = 0;
};

typedef std::unique_ptr<IGeometryFactory> IGeometryFactoryUPtr;

#endif // IGEOMETRYFACTORY_H
