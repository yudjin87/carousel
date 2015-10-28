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

#include "ScriptingServiceTest.h"
#include "fakes/FakeConfigurationDelegate.h"
#include "fakes/MockComponentManager.h"
#include "fakes/MockScriptExtensionComponent.h"

#include <components/qmlscripting/CarouselScriptEngineConfigurationDelegate.h>
#include <components/qmlscripting/ServiceLocatorWrapper.h>
#include <components/qmlscripting/ScriptingService.h>
#include <components/qmlscripting/IScriptConsole.h>
#include <components/interactivity/Catalogs.h>
#include <carousel/utils/ServiceLocator.h>

#include <QtQml/QJSEngine>
#include <QtTest/QtTest>

ScriptingServiceTest::ScriptingServiceTest(QObject *parent)
    : QObject(parent)
{
    setObjectName("ScriptingServiceTest");
}

void ScriptingServiceTest::setDelegate_shouldSetupNull()
{
    ServiceLocator locator; MockComponentManager cm(&locator);
    ScriptingService service(&locator, &cm);
    QJSEngine *engine = service.createEngine(nullptr, this);

    QJSValue defaultLocator = engine->globalObject().property("serviceLocator");
    QVERIFY(!defaultLocator.isNull());

    service.setDelegate(nullptr);
    engine = service.createEngine(nullptr, this);
    // QJSValue nullLocator = engine->globalObject().property("serviceLocator");
    // QVERIFY(nullLocator.isNull());
    // TODO: should be uncomment when is implemented
}

void ScriptingServiceTest::setDelegate_shouldResetConsoleEngine()
{
    ServiceLocator locator; MockComponentManager cm(&locator);
    ScriptingService service(&locator, &cm);
    QJSEngine *engine = service.console()->engine();

    QJSValue defaultLocator = engine->globalObject().property("serviceLocator");
    QVERIFY(!defaultLocator.isNull());
    QVERIFY(!defaultLocator.isUndefined());
    QVERIFY(defaultLocator.isQObject());

    QVERIFY(defaultLocator.toQObject() != nullptr);

    FakeConfigurationDelegate *delegate = new FakeConfigurationDelegate();
    service.setDelegate(delegate);

    QObject *newWrapper = engine->globalObject().property("serviceLocator").toQObject();
    QVERIFY(newWrapper != nullptr);
    QVERIFY(newWrapper->objectName() == "NewWrapper");
}

void ScriptingServiceTest::shouldCallConfigureForConsoleEngineWhenComponentStarted()
{
    ServiceLocator locator; MockComponentManager manager(&locator);
    ScriptingService service(&locator, &manager);
    FakeConfigurationDelegate *delegate = new FakeConfigurationDelegate();
    service.setDelegate(delegate);
    manager.callOnStartUp();

    MockScriptExtensionComponent comp;
    manager.callOnComponentStarted(&comp);

    QVERIFY(delegate->configureFromComponentCalled);
}

