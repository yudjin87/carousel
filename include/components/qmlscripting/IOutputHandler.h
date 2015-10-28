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
#include <components/qmlscripting/qmlscripting_global.h>

/*!
 * @brief
 *   This handler is used for the JavaScript's print() function.
 * @details
 *   During configuration QJSEngine with default types and functions, an
 *   IScriptEngineConfigurationDelegate configures the JavaScript's print() function
 *   in such way, that each time when print() is invoked from the script, IOutputHandler::print()
 *   will be invoked.
 *
 * @sa IScriptEngineConfigurationDelegate
 */
class QML_SCRIPTING_API IOutputHandler
{
public:
    /*!
     * @details
     * @constructor{IOutputHandler}.
     */
    IOutputHandler(){}
    virtual ~IOutputHandler(){}

    /*!
     * @details
     *   It is invoked each time when print() is invoked from the script.
     *   A @a message is a parameter, that was passed to the JavaScript's print()
     *   function.
     */
    virtual void print(const QString &message) = 0;

    // virtual void alert(const QString &message) = 0;
    // virtual void prompt(const QString &message) = 0;
    // virtual void confirm(const QString &message) = 0;

private:
    Q_DISABLE_COPY(IOutputHandler)
};

