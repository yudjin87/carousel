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
#include <QtQml/QQmlEngine>

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
    ServiceLocator locator;
    QJSEngine *engine = new QJSEngine(this);
    CarouselScriptEngineConfigurationDelegate delegate(&locator);

    MockOutputHandler output;
    delegate.configureDefaults(engine, &output);

    QJSValue defaultLocator = engine->globalObject().property("serviceLocator");
    QVERIFY(!defaultLocator.isNull());
    QVERIFY(!defaultLocator.isUndefined());
    QVERIFY(defaultLocator.isQObject());

    QVERIFY(defaultLocator.toQObject() != nullptr);
}

void CarouselScriptEngineConfigurationDelegateTest::configureDefaults_shouldAddIncludeFunctionToEngine()
{
    ServiceLocator locator; QJSEngine engine;
    CarouselScriptEngineConfigurationDelegate delegate(&locator);

    MockOutputHandler output;
    delegate.configureDefaults(&engine, &output);
    QJSValue result = engine.evaluate(QString("include(\"%1\");").arg(m_testScriptPath));
    QVERIFY(!result.isError());

    QJSValue includedScriptValue = engine.globalObject().property("a");
    QVERIFY(!includedScriptValue.isUndefined());

    int value = includedScriptValue.toInt();

    QCOMPARE(value, 111);
}

void CarouselScriptEngineConfigurationDelegateTest::explore_shouldPrintAllGlobals()
{
    ServiceLocator locator; QJSEngine engine;
    CarouselScriptEngineConfigurationDelegate delegate(&locator);

    MockOutputHandler output;
    delegate.configureDefaults(&engine, &output);
    engine.evaluate("explore()");

    QVERIFY(!output.messages.empty());
    QVERIFY(output.messages.contains("Math (instance)"));
    QVERIFY(output.messages.contains("explore()"));
    QVERIFY(output.messages.contains("NaN"));
    QVERIFY(!output.messages.contains("__explore__ (instance)"));
    QVERIFY(!output.messages.contains("__explore__"));
}

void CarouselScriptEngineConfigurationDelegateTest::explore_shouldPrintVariableMembers()
{
    ServiceLocator locator; QJSEngine engine;
    CarouselScriptEngineConfigurationDelegate delegate(&locator);

    MockOutputHandler output;
    delegate.configureDefaults(&engine, &output);
    engine.evaluate("explore(serviceLocator)");

    QCOMPARE(output.messages.size(), 4);
    QVERIFY(!output.messages.contains("objectName"));
    QVERIFY(!output.messages.contains("destroyed"));
    QVERIFY(!output.messages.contains("objectNameChanged"));

    QVERIFY(output.messages.contains("locate"));
    QVERIFY(output.messages.contains("build"));
    QVERIFY(output.messages.contains("build"));
    QVERIFY(output.messages.contains("services"));
}

