/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * Carousel - Qt-based managed component library.
 *
 * Copyright: 2011-2016 Carousel team
 * Authors:
 *   Yevhen Chuhui (Eugene Chuguy) <yevhen.chuhui@gmail.com>
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

#pragma once
#include <carousel/carousel_global.h>

#include <QtCore/QString>

/*!
 * @brief
 *   The IComponentLocationConstructorDelegate class is used to constuct
 *   a location to the library for a component.
 * @details
 *   This interface provides functionality for format component location
 *   for the DefinitionConstructor. It may be absolute path for file system
 *   or relative path for the web address and so on.
 */
class CAROUSEL_API IComponentLocationConstructorDelegate
{
public:
    IComponentLocationConstructorDelegate(){}
    virtual ~IComponentLocationConstructorDelegate(){}

    /*!
     * @details
     *   Completes component location bases at the final part of them.
     */
    virtual QString constructLocation(const QString &ending) = 0;
};

