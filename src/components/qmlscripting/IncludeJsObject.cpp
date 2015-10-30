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

#include "components/qmlscripting/IncludeJsObject.h"
#include <carousel/logging/LoggerFacade.h>

#include <QtCore/QCoreApplication>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtQml/QJSEngine>
#include <QtQml/QJSValue>

namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("IncludeJsObject");
}

IncludeJsObject::IncludeJsObject(QJSEngine &engine, QObject *parent)
    : QObject(parent)
    , m_engine(engine)
{
}

void IncludeJsObject::include(QString jsFilePath)
{
    QDir abs(QCoreApplication::applicationDirPath());
    QFile scriptFile(abs.absoluteFilePath(jsFilePath));
    if (!scriptFile.open(QIODevice::ReadOnly)) {
        Log.w(QString("Could not open included script file: \"%1\"").arg(jsFilePath));
        // TODO: notify client. Some single place with scripting errors is needed
        return;
    }

    QTextStream stream(&scriptFile);
    QString contents = stream.readAll();

    QJSValue result = m_engine.evaluate(contents);
    if (result.isError()) {
        Log.w(QString("An error occured during including script file \"%1\": %2").arg(jsFilePath).arg(result.toString()));
        // TODO: notify client. Some single place with scripting errors is needed
    }
}

