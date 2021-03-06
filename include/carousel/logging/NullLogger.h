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
#include <carousel/logging/ILoggerEngine.h>
#include <carousel/logging/ILoggerEngineCreator.h>

/*!
 * @brief
 *   The NullLogger class is a stub for the carousel logging engine.
 * @details
 *   You might return this object in the overridden function BootloaderBase::createLogger()
 *   if you don't need any logging and/or you lack resources.
 */
class CAROUSEL_API NullLogger : public ILoggerEngine, public ILoggerEngineCreator
{
public:
    /*!
     * @details
     * @constructor{LoggerFacade} using "NullLogger" logger name.
     */
    NullLogger();

    /*!
     * @details
     *   Creates and returns a new instance of the NullLogger. The @a name
     *   parameter is ignored.
     */
    ILoggerEngine *getLogger(const QString &name) override;

    /*!
     * @details
     *   Sends a @a debug log message to the output stream.
     *   Debug logs are stripped at runtime in release configuration.
     */
    void d(const QString &message) override;

    /*!
     * @details
     *   Sends an @a error log message to the output stream.
     */
    void e(const QString &message) override;

    /*!
     * @details
     *   Sends a @a fatal log message to the output stream.
     */
    void f(const QString &message) override;

    /*!
     * @details
     *   Sends an @a info log message to the output stream.
     */
    void i(const QString &message) override;

    /*!
     * @details
     *   Sends a @a trace log message to the output stream.
     */
    void t(const QString &message) override;

    /*!
     * @details
     *   Sends a @a warning log message to the output stream.
     */
    void w(const QString &message) override;
};

