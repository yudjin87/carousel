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

#include "components/qmlscripting/ScriptConsole.h"

#include <carousel/logging/LoggerFacade.h>

#include <QtQml/QJSEngine>

namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("ScriptConsole");
}

ScriptConsole::ScriptConsole(QJSEngine *engine, QObject *parent)
    : m_engine(engine)
    , m_history(QStringList())
    , m_historyCommand(m_history.begin())
    , m_historyCapacity(100) // TODO: read from application references
{
    setParent(parent);
    engine->setParent(this);
}

QJSEngine *ScriptConsole::engine()
{
    return m_engine;
}

bool ScriptConsole::execCommand(const QString &command)
{
    emit aboutToExecute(command);
    addCommandToHistory(command);

    QJSValue result = m_engine->evaluate(command);
    if (!result.isError())
        return true;

    QString scriptError = QString("Script error:\n\"%1\"").arg(result.toString());
    Log.w(scriptError);

    emit error(result.toString());

    return false;
}

int ScriptConsole::historyCapacity() const
{
    return m_historyCapacity;
}

void ScriptConsole::setHistoryCapacity(int capacity)
{
    m_historyCapacity = capacity;
}

QString ScriptConsole::prevCommand()
{
    if (m_history.isEmpty())
        return "";

    if (m_historyCommand == m_history.constBegin())
        return m_history.first();

    return *--m_historyCommand;
}

QString ScriptConsole::nextCommand()
{
    if (m_history.isEmpty())
        return "";

    if (m_historyCommand == m_history.constEnd()) {
        return "";
    }

    if (++m_historyCommand == m_history.constEnd()) {
        --m_historyCommand;
        return "";
    }

    return *m_historyCommand;
}

const QStringList &ScriptConsole::commandHistory() const
{
    return m_history;
}

void ScriptConsole::print(const QString &message)
{
    emit printed(message);
}

void ScriptConsole::addCommandToHistory(const QString &command)
{
    if (command.trimmed().isEmpty()) {
        m_historyCommand = m_history.constEnd(); // reset anyway
        return;
    }

    if (m_history.size() >= m_historyCapacity)
        m_history.removeFirst();

    m_history.push_back(command);
    m_historyCommand = m_history.constEnd();
}

