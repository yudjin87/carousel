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
#include "interactivity_global.h"

#include <carousel/componentsystem/IComponentExtension.h>

class ICatalogs;
class IServiceLocator;

/*!
 * @brief
 *   The IInteractiveExtension interface declares contract for the component,
 *   that wants to extend user interaction elements.
 * @details
 *   This abstract class provides contract to register ICatalog items (operations,
 *   menus, toolbars, etc) specific to the component in application.
 *
 *   Although you can access IInteractionService during application startup,
 *   it is recomended to implement this interface to register menus and tools
 *   specific to your component. Components that register this interface in the
 *   IComponent::extension() will be asked for the GUI configuration right
 *   after component started.
 * @sa IComponent::extension().
 */
class INTERACTIVITY_API IInteractiveExtension : public IComponentExtension
{
public:
    IInteractiveExtension(){}

    /*!
     * @details
     *   Place your code here to register component-specific operations,
     *   dockable widgets and others in the specified catalogs.
     *
     *   You can use @a serviceLocator to obtain application model, for
     *   example, to use it in the Qt View-Model approach.
     */
    virtual void configureGui(ICatalogs &inCatalogs, IServiceLocator *serviceLocator) = 0;

private:
    Q_DISABLE_COPY(IInteractiveExtension)
};

