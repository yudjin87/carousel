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

#include "componentsystem/ComponentProvider.h"
#include "componentsystem/IComponent.h"

ComponentProvider::ComponentProvider(QObject *parent /*= nullptr*/)
    : m_alreadyInit(false)
{
    setParent(parent);
}

ComponentProvider::~ComponentProvider()
{    
}

QList<IComponent *> ComponentProvider::components() const
{
    return m_components;
}

bool ComponentProvider::initialize()
{
    if (m_alreadyInit)
        return true;

    m_alreadyInit = onInitialize();

    return m_alreadyInit;
}

bool ComponentProvider::isInitialized() const
{
    return m_alreadyInit;
}

void ComponentProvider::registerComponent(IComponent *component)
{
    if (component != nullptr)
        m_components.push_back(component);
}

bool ComponentProvider::onInitialize()
{
    //nothing to do by default
    return true;
}

