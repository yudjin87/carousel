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

#include "logging/TextLogger.h"

#include <QtCore/QString>
#include <QtCore/QDate>
#include <QtCore/QThread>

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

static QMutex mutex;

TextLogger::TextLogger(QTextStream &output)
    : TextLogger(output, output, "Root")
{
}

TextLogger::TextLogger(QTextStream &output, QTextStream &errorOutput)
    : TextLogger(output, errorOutput, "Root")
{
}

TextLogger::TextLogger(QTextStream &output, const QString &name)
    : TextLogger(output, output, name)
{
}

TextLogger::TextLogger(QTextStream &output, QTextStream &errorOutput, const QString &name)
    : ILoggerEngine()
    , ILoggerEngineCreator()
    , m_outputStream(output)
    , m_errorStream(errorOutput)
    , m_name(name)
{
}

ILoggerEngine *TextLogger::getLogger(const QString &name)
{
    QMutexLocker locker(&mutex);
    return new TextLogger(m_outputStream, m_errorStream, name);
}

void TextLogger::d(const QString &message)
{
#ifdef QT_DEBUG
    log(m_outputStream, message, "DBG");
#else
    Q_UNUSED(message)
#endif
}

void TextLogger::e(const QString &message)
{
    log(m_errorStream, message, "ERR");
}

void TextLogger::f(const QString &message)
{
    log(m_errorStream, message, "FTL");
}

void TextLogger::i(const QString &message)
{
    log(m_outputStream, message, "INF");
}

void TextLogger::t(const QString &message)
{
    log(m_outputStream, message, "TRC");
}

void TextLogger::w(const QString &message)
{
    log(m_errorStream, message, "WRN");
}

void TextLogger::log(QTextStream& stream, const QString &message, const QString &category)
{
    static const QString messagePattern = "[%1]%2[%3] %4: %5";
    static const QString dateFormat = "dd MMM, hh:mm:ss.zzz";

    QString formatedMessage = messagePattern
            .arg(QDateTime::currentDateTime().toString(dateFormat))
            .arg(QThread::currentThread()->objectName())
            .arg(name())
            .arg(category)
            .arg(message);

    QMutexLocker locker(&mutex);
    stream << formatedMessage << endl;
}

const QString &TextLogger::name() const
{
    return m_name;
}

