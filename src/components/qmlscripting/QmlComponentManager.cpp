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

#include "components/qmlscripting/QmlComponentManager.h"
#include <carousel/componentsystem/IComponentManager.h>
#include <carousel/utils/IServiceLocator.h>

QmlComponentManager::QmlComponentManager(IComponentManager &componentManager, QObject *parent)
    : QObject(parent)
    , m_componentManager(componentManager)
    , m_orphanComponents()
    , m_stoppedComponents()
    , m_startedComponents()
{
}

QmlComponentManager::QmlComponentManager(IServiceLocator &locator, QObject *parent)
    : QmlComponentManager(*locator.locate<IComponentManager>(), parent)
{
}

QQmlListProperty<IComponent> QmlComponentManager::orphanComponents()
{
    m_orphanComponents = m_componentManager.orphanComponents();
    return QQmlListProperty<IComponent>(this, m_orphanComponents);
}

QQmlListProperty<IComponent> QmlComponentManager::stoppedComponents()
{
    m_stoppedComponents = m_componentManager.stoppedComponents();
    return QQmlListProperty<IComponent>(this, m_stoppedComponents);
}

QQmlListProperty<IComponent> QmlComponentManager::startedComponents()
{
    m_startedComponents = m_componentManager.startedComponents();
    return QQmlListProperty<IComponent>(this, m_startedComponents);
}
