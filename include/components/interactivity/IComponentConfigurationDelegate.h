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

#include <QtCore/QObject>

class ConfigurationChanges;
class IComponent;
class ICatalogs;


/*!
 * @brief
 *   This interface used by the IInteractionService to configure started
 *   up components.
 * @details
 *   It also manages what exactly have been changed in GUI during
 *   component's configuraion - it is important for the further
 *   deconfiguring and also could be usefull for displaying
 *   which operations have been registered by components.
 */
class INTERACTIVITY_API IComponentConfigurationDelegate : public QObject
{
    Q_OBJECT
public:
    IComponentConfigurationDelegate(){}
    ~IComponentConfigurationDelegate(){}

public slots:
    /*!
     * @details
     *   Tries to get the IInteractiveExtension from @a component and
     *   provides to extension the way to configure application's
     *   user interface.
     *
     *   An @a application will be passed to the extension to obtain application model, for
     *   example, to use it in the Qt View-Model approach.
     */
    virtual void configure(IComponent *component, ICatalogs &catalogs) = 0;

    /*!
     * @details
     *   Removes all component configurations from catalogs. Invokes
     *   after component has been shut down.
     */
    virtual void deconfigure(IComponent *component, ICatalogs &catalogs) = 0;

    /*!
     * @details
     *   Returns GUI changes (component customization) proceded
     *   by the specified component while it was configured.
     * @return @a nullptr, if component has not been configured
     *   by this delegate.
     */
    virtual const ConfigurationChanges *changesByComponent(IComponent *component) const = 0;

private:
    Q_DISABLE_COPY(IComponentConfigurationDelegate)
};

