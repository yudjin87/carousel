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

#include "CarouselScriptEngineConfigurationDelegateTest.h"
#include "fakes/MockOutputHandler.h"
#include "fakes/MockScriptExtensionComponent.h"

#include <carousel/utils/ServiceLocator.h>
#include <components/qmlscripting/CarouselScriptEngineConfigurationDelegate.h>

#include <QtQml/QJSEngine>
#include <QtTest/QtTest>

CarouselScriptEngineConfigurationDelegateTest::CarouselScriptEngineConfigurationDelegateTest(QObject *parent)
    : QObject(parent)
    , m_testScriptPath("./scripts/TestScript.js")
{
}

void CarouselScriptEngineConfigurationDelegateTest::configureComponent_shouldConfigureComponentIfItHasScriptExtension()
{
    ServiceLocator locator; QJSEngine engine;
    CarouselScriptEngineConfigurationDelegate delegate(&locator);
    MockScriptExtensionComponent component;
    component.startup(nullptr); component.setState(IComponent::Running);

    delegate.configureFromComponent(&component, &engine);

    QVERIFY(component.m_extension->m_configureCalled);
}

void CarouselScriptEngineConfigurationDelegateTest::configureComponent_shouldNotCallConfigureIfComponentWasNotStarted()
{
    ServiceLocator locator; QJSEngine engine;
    CarouselScriptEngineConfigurationDelegate delegate(&locator);
    MockScriptExtensionComponent component;

    delegate.configureFromComponent(&component, &engine);

    QVERIFY(!component.m_extension->m_configureCalled);
}

void CarouselScriptEngineConfigurationDelegateTest::configureComponent_shouldNotThrowIfComponentHasNoScriptExtension()
{
    ServiceLocator locator; QJSEngine engine;
    CarouselScriptEngineConfigurationDelegate delegate(&locator);
    MockNoScriptExtensionComponent component;
    component.startup(nullptr); component.setState(IComponent::Running);

    delegate.configureFromComponent(&component, &engine);

    QVERIFY(true);
}

void CarouselScriptEngineConfigurationDelegateTest::configureDefaults_shouldAddServiceLocatorObjectToEngine()
{
    ServiceLocator locator; QJSEngine engine;
    CarouselScriptEngineConfigurationDelegate delegate(&locator);

    MockOutputHandler output;
    delegate.configureDefaults(&engine, &output);

    QVERIFY(!engine.globalObject().property("serviceLocator").isNull());
}
