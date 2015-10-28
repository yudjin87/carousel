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

#include "ScriptEngineTest.h"

#include <components/qmlscripting/ServiceLocatorWrapper.h>
#include <carousel/utils/ServiceLocator.h>

#include <QtQml/QJSEngine>
#include <QtTest/QtTest>

ScriptEngineTest::ScriptEngineTest(QObject *parent)
    : QObject(parent)
{
    setObjectName("ScriptEngineTestName");
}

ScriptEngineTest::~ScriptEngineTest()
{
}

void ScriptEngineTest::tryServiceLocatorWrapper()
{
    ServiceLocator locator; locator.registerInstance<ScriptEngineTest>(this);
    ServiceLocatorWrapper *wrapper = new ServiceLocatorWrapper(&locator);

    QJSEngine engine;
    QJSValue value = engine.newQObject(wrapper); // QJSEngine takes ownership for the wrapper
    QVERIFY(!value.isNull());

    engine.globalObject().setProperty("serviceLocator", value);

    QJSValue result = engine.evaluate(simpleScript);
    QVERIFY(!result.isError());

    QString nameFromScript = engine.globalObject().property("name").toString();
    QCOMPARE(nameFromScript, this->objectName());
}

const QByteArray ScriptEngineTest::simpleScript(
        "var obj = serviceLocator.locate(\"ScriptEngineTest\");"
        "var name = obj.objectName");

