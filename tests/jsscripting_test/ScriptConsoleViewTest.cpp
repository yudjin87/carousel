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

#include "ScriptConsoleViewTest.h"

#include <components/jsscripting/ScriptConsole.h>
#include <components/jsscripting/ScriptConsoleView.h>
#include <components/jsscripting/CodeHighlighter.h>
#include <components/jsscripting/ColorTheme.h>

//------------------------------------------------------------------------------
ScriptConsoleViewTest::ScriptConsoleViewTest(QObject *parent)
    : QObject(parent)
    , m_engine()
    , m_theme(ColorTheme::createDefault(this))
    , m_hilighter(new CodeHighlighter(m_theme, this))
    , m_console(new ScriptConsole(&m_engine, this))
    , m_view(new ScriptConsoleView(m_console, m_hilighter))
{
}

//------------------------------------------------------------------------------
ScriptConsoleViewTest::~ScriptConsoleViewTest()
{
    delete m_view;
    m_view = nullptr;
}

//------------------------------------------------------------------------------
void ScriptConsoleViewTest::test()
{
    m_view->show();    
}

//------------------------------------------------------------------------------
