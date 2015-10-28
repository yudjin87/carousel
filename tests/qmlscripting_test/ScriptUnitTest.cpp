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

#include "ScriptUnitTest.h"
#include "fakes/FakeScriptUnit.h"

#include <components/qmlscripting/CarouselScriptEngineConfigurationDelegate.h>
#include <components/qmlscripting/ScriptUnit.h>
#include <components/qmlscripting/ScriptingService.h>

#include <QtCore/QCoreApplication>
#include <QtCore/QEvent>
#include <QtQml/QJSEngine>
#include <QtGui/QTextDocument>
#include <QtTest/QtTest>

ScriptUnitTest::ScriptUnitTest(QObject *parent)
    : QObject(parent)
    , m_testScriptPath(QCoreApplication::applicationDirPath() + "/scripts/TestScript.js")
    , m_unit(nullptr)
{
}

void ScriptUnitTest::shouldReturnAbsoluteFilePath()
{
    ScriptUnit unit("scripts/TestScript.js", nullptr);

#ifdef Q_OS_WIN32
    QCOMPARE(unit.absoluteFilePath().toLower(), m_testScriptPath.toLower());
#else
    QCOMPARE(unit.absoluteFilePath(), m_testScriptPath);
#endif // Q_WS_WIN

}

void ScriptUnitTest::load_shouldLoadScript()
{
    ScriptUnit unit(m_testScriptPath, nullptr);
    QVERIFY(!unit.isLoaded());
    QVERIFY(unit.script()->isEmpty());
    QVERIFY(unit.load());
    QVERIFY(!unit.script()->isEmpty());
    QVERIFY(unit.isLoaded());
}

void ScriptUnitTest::load_shouldNotLoadScriptWithIncorrectFileName()
{
    ScriptUnit unit("/nowhere/TestScript.js", nullptr);
    QVERIFY(!unit.load());
}

void ScriptUnitTest::load_shouldNotChangeDocumentModifiedFlag()
{
    ScriptUnit unit(m_testScriptPath, nullptr);
    QVERIFY(!unit.script()->isModified());
    unit.load();
    QVERIFY(!unit.script()->isModified());
}

void ScriptUnitTest::save_shouldResetDocumentModifiedFlag()
{
    ScriptUnit unit(m_testScriptPath, nullptr);
    unit.load();
    unit.script()->setModified(true);
    QVERIFY(unit.script()->isModified());
    QVERIFY(unit.save());
    QVERIFY(!unit.script()->isModified());
}

void ScriptUnitTest::save_shouldNotResetDocumentModifiedFlagIfSavingFailed()
{
    FakeScriptUnit unit(m_testScriptPath);
    unit.load();
    unit.script()->setModified(true);
    QVERIFY(unit.script()->isModified());
    QVERIFY(!unit.save());
    QVERIFY(unit.script()->isModified());
}

void ScriptUnitTest::saveAs_shouldChangeFileName()
{
    FakeScriptUnit unit(m_testScriptPath); unit.saveToFileResult = true;
    unit.load();
    unit.script()->setModified(true);
    unit.saveAs("/new/file.name");
    QVERIFY(unit.absoluteFilePath() == "/new/file.name");
}

void ScriptUnitTest::saveAs_shouldNotChangeFileNameIfSavingFailed()
{
    FakeScriptUnit unit(m_testScriptPath);
    unit.load();
    unit.script()->setModified(true);
    unit.saveAs("/new/file.name");
#ifdef Q_OS_WIN32
    QCOMPARE(unit.absoluteFilePath().toLower(), m_testScriptPath.toLower());
#else
    QCOMPARE(unit.absoluteFilePath(), m_testScriptPath);
#endif // Q_WS_WIN
}

QJSEngine *ScriptUnitTest::createEngine(IOutputHandler *output, QObject *parent)
{
    QJSEngine *engine = new QJSEngine(parent);
    CarouselScriptEngineConfigurationDelegate configurator(nullptr);
    configurator.configureDefaults(engine, output);

    return engine;
}
