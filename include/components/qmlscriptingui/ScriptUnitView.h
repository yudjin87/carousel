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

#pragma once
#include <components/qmlscriptingui/qmlscriptingui_global.h>

#include <QtWidgets/QWidget>

namespace Ui
{
class ScriptUnitView;
}

class IScriptUnit;
class QSyntaxHighlighter;

class QML_SCRIPTING_UI_API ScriptUnitView : public QWidget
{
    Q_OBJECT
public:
    /*!
     * @details
     *  Takes ownership for highlighter
     */
    ScriptUnitView(IScriptUnit *data, QSyntaxHighlighter *highlighter, QWidget *parent);
    ~ScriptUnitView();

    IScriptUnit *data();

    void clear();
    void printError(const QString &error);
    void printOutput(const QString &output);

public slots:
    void onRun();
    bool onSave();

protected:
    bool eventFilter(QObject *sender, QEvent *event);

private:
    bool onKeyPressed(QKeyEvent *event);
    bool processControlKey(int key);
    void insertIndent();
    void onAborted();

private:
    Ui::ScriptUnitView *m_ui;
    IScriptUnit *m_data;
};

