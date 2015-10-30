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

#include "components/qmlscripting/ExploreJsObject.h"
#include "components/qmlscripting/IOutputHandler.h"
#include <carousel/logging/LoggerFacade.h>

#include <QtCore/QList>
#include <QtQml/QJSEngine>
#include <QtQml/QJSValue>
#include <QtQml/QJSValueIterator>

namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("ExploreJsObject");

static const QList<QString> qobjectProperties = {
    "objectName",
    "objectNameChanged"
    };

}

ExploreJsObject::ExploreJsObject(IOutputHandler &outputHandler, QJSEngine &engine, QObject *parent)
    : QObject(parent)
    , m_engine(engine)
    , m_outputHandler(outputHandler)
{
}

void ExploreJsObject::explore()
{
    QJSValueIterator it(m_engine.globalObject());
    while (it.hasNext())
    {
        it.next();
        QJSValue val = it.value();
        if (val.isCallable())
        {
            m_outputHandler.print(it.name() + "()");
            continue;
        }

        if (val.isObject() && !it.name().startsWith("__"))
        {
            m_outputHandler.print(it.name() + " (instance)");
            continue;
        }

        m_outputHandler.print(it.name());
    }
}

void ExploreJsObject::explore(const QJSValue &instance)
{
    if (instance.isUndefined())
    {
        explore(); // show globals
        return;
    }

    QJSValueIterator membersIt(instance);
    while (membersIt.hasNext())
    {
        membersIt.next();
        const QString name = membersIt.name();
        if (!qobjectProperties.contains(name))
            m_outputHandler.print(membersIt.name());
    }
}

