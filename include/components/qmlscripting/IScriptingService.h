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

#include <QtCore/QObject>

class IScriptConsole;
class IScriptEngineConfigurationDelegate;
class IScriptCollection;

/*!
 * @brief
 *   This interface is an entry point to the JsScripting component.
 * @details
 *   This service provides references to the important parts of the JsScripting component -
 *   IScriptConsole and IScriptCollection. While these objects are used to evaluate scripts,
 *   there is also one more important reference - to the IScriptEngineConfigurationDelegate.
 *   This delegate is invoked every time to configure QJSEngine when new script is evaluated
 *   by IScriptUnit or when new component is started. It is allows new components to extend
 *   JavaScript with custom types, functions or wrappers for their objects.
 *
 *   It is registered in the service locator by the JsScriptingComponent.
 *   You can locate to this service from the service locator:
 *
 * @code
 *   IScriptingService *service = serviceLocator->locate<IScriptingService>();
 *   IScriptConsole *console = service->console();
 * @endcode
 *
 */
class QML_SCRIPTING_API IScriptingService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(IScriptCollection *scripts READ scripts)
    Q_PROPERTY(IScriptConsole *console READ console)
public:
    /*!
     * @details
     * @constructor{IScriptingService}.
     */
    IScriptingService(){}

    /*!
     * @details
     *   Gets the script console.
     */
    virtual IScriptConsole *console() = 0;

    /*!
     * @details
     *   Gets the scripts, that loaded into the application.
     */
    virtual IScriptCollection *scripts() = 0;

    /*!
     * @details
     *   Gets the delegate which is used for QJSEngine configuration.
     */
    virtual IScriptEngineConfigurationDelegate *delegate() = 0;

    /*!
     * @details
     *   Gets the delegate which is used for QJSEngine configuration.
     */
    virtual const IScriptEngineConfigurationDelegate *delegate() const = 0;

    /*!
     * @details
     *   Sets the delegate which is used for QJSEngine configuration.
     *   This delegate is used for configuration console() engine right after component manager
     *   started up and as soons as new components are started.
     */
    virtual void setDelegate(IScriptEngineConfigurationDelegate *delegate) = 0;

private:
    Q_DISABLE_COPY(IScriptingService)
};

