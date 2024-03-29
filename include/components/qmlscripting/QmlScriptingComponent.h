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

#include <carousel/componentsystem/BaseComponent.h>

class ServiceLocatorWrapper;

/*!
 * @brief
 *   This class represents a component, that adds JavaScript facilities using QtQml module.
 * @details
 *   The QmlScriptingComponent provides objects that allow custom application
 *   to expose its API to the JavaScript.
 *
 *   All objsects, registered in the IServiceLocator are available from the script. Also one more object
 *   is available in the JS global context - it is the serviceLocator:
 * @code
 *   var cm = serviceLocator.locate("IComponentManager");
 *   var startedComponents = cm.startedComponents;
 *   var componentsCount = startedComponents.length;
 * @endcode
 *
 *   To see all available objsects from the serviceLocator you can use serviceLocator.services()
 *   method;
 *
 *   To see all properties and methods in the object you can use explore() function:
 * @code
 *   explore(serviceLocator);
 *   explore(cm);
 * @endcode
 *
 *   explore() also can be used without arguments to print out global objects, types
 *   and functions.
 *
 *   Since all objsects, registered in the IServiceLocator are available from the script,
 *   it is possible to get references for deeper models of the component. Main flow for this
 *   the next: you get a service from the script. As soon as the service is derived from the
 *   QObject, ypu can use its properties amd methods. Usually, carousel services expose some
 *   part of the its model through the properties or slots. So, you can get some model (which is
 *   derived from the QObject too) reference via these properties, and so on.
 *
 *   If some component wants to extend script with new funcitons or types, or register wrappers
 *   for some non-QObject classes, it should be a child of the QmlScriptingComponent. This mean a
 *   dependency of component parent name:  @a "org.carousel.QmlScripting". Then to get chance for
 *   registration, this component should also provide IScriptExtension extension. The overridden
 *   IScriptExtension::configureEngine method will be invoked every time, when QScriptEngine
 *   configuration is needed. So, in your extension you can register what ever you want in the
 *   QScriptEngine.
 *
 *   Registered services:
 * @li IScriptingService (entry point);
 *
 * @sa QmlScriptingUIComponent, IScriptEngineConfigurationDelegate, IScriptExtension, IScriptingService
 */
class QML_SCRIPTING_API QmlScriptingComponent : public BaseComponent
{
    Q_OBJECT
public:
    /*!
     * @details
     * @constructor{QmlScriptingComponent}.
     */
    QmlScriptingComponent(QObject *parent = nullptr);
    ~QmlScriptingComponent();

protected:
    /*!
     * @details
     *   Shuts down the component.
     */
    void onShutdown(IServiceLocator *serviceLocator) override;

    /*!
     * @details
     *   Registers IScriptingService in the @a serviceLocator.
     */
    bool onStartup(IServiceLocator *serviceLocator) override;

private:
    QString getStartedScriptFromAgrs() const;
};

