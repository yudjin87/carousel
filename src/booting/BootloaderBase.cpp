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

#include "BootloaderBase.h"

#include <logging/TextLogger.h>
#include <componentsystem/ComponentDependencies.h>
#include <componentsystem/ComponentInitialiser.h>
#include <componentsystem/ComponentManager.h>
#include <componentsystem/ComponentProvider.h>
#include <utils/ServiceLocator.h>

#include <QtGui/QMainWindow>

//------------------------------------------------------------------------------
BootloaderBase::BootloaderBase()
    : mp_componentManager(nullptr)
    , mp_componentProvider(nullptr)
    , mp_logger(nullptr)
    , mp_serviceLocator(nullptr)
    , mp_mainWindow(nullptr)
    , m_alreadyRunned(false)
{
}

//------------------------------------------------------------------------------
BootloaderBase::~BootloaderBase()
{
    delete mp_componentManager;
    mp_componentManager = nullptr;

    delete mp_componentProvider;
    mp_componentProvider = nullptr;

    delete mp_logger;
    mp_logger = nullptr;

    delete mp_serviceLocator;
    mp_serviceLocator = nullptr;

    delete mp_mainWindow;
    mp_mainWindow = nullptr;
}

//------------------------------------------------------------------------------
void BootloaderBase::run()
{
    if (m_alreadyRunned)
        return;

    _run();

    m_alreadyRunned = true;
}

//------------------------------------------------------------------------------
IServiceLocator *BootloaderBase::serviceLocator() const
{
    return mp_serviceLocator;
}

//------------------------------------------------------------------------------
void BootloaderBase::_configureComponentManager()
{
}

//------------------------------------------------------------------------------
void BootloaderBase::_configureComponentProvider()
{
}

//------------------------------------------------------------------------------
IComponentManager *BootloaderBase::_createComponentManager()
{
    return new ComponentManager(new ComponentDependencies(), new ComponentInitialiser(*mp_logger), *mp_logger);
}

//------------------------------------------------------------------------------
IComponentProvider *BootloaderBase::_createComponentProvider()
{
    return new ComponentProvider();
}

//------------------------------------------------------------------------------
ILogger *BootloaderBase::_createLogger()
{
    static QTextStream text(stdout);
    return new TextLogger(text);
}

//------------------------------------------------------------------------------
IServiceLocator *BootloaderBase::_createServiceLocator()
{
    return new ServiceLocator();
}

//------------------------------------------------------------------------------
QMainWindow *BootloaderBase::_createMainWindow()
{
    return new QMainWindow();
}

//------------------------------------------------------------------------------
void BootloaderBase::_initialiseComponentProvider()
{
}

//------------------------------------------------------------------------------
