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

#ifndef ICOMPONENTEXTENSION_H
#define ICOMPONENTEXTENSION_H

#include <carousel/componentsystem/componentsystem_global.h>

class IComponent;

/*!
 * @brief
 *   It is a base class for all extensions that could be exposed by
 *   IComponent::extension() method.
 * @details
 *   This class does not give added value, it is only a top class
 *   for all extensions now.
 */
class COMP_API IComponentExtension
{
public:
    virtual ~IComponentExtension(){}

protected:
    IComponentExtension(){}

private:
    Q_DISABLE_COPY(IComponentExtension)
};

#endif // ICOMPONENTEXTENSION_H