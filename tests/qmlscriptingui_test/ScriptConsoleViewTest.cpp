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

#include "ScriptConsoleViewTest.h"

#include <components/qmlscripting/ScriptConsole.h>
#include <components/qmlscriptingui/ScriptConsoleView.h>
#include <components/qmlscriptingui/CodeHighlighter.h>
#include <components/qmlscriptingui/ColorTheme.h>

#include <QtQml/QJSEngine>

ScriptConsoleViewTest::ScriptConsoleViewTest(QObject *parent)
    : QObject(parent)
    , m_theme(ColorTheme::getDefault())
    , m_hilighter(new CodeHighlighter(m_theme, this))
    , m_console(new ScriptConsole(new QJSEngine, this))
    , m_view(new ScriptConsoleView(m_console, m_hilighter))
{
}

ScriptConsoleViewTest::~ScriptConsoleViewTest()
{
    delete m_view;
    m_view = nullptr;
}

void ScriptConsoleViewTest::test()
{
    m_view->show();
}

