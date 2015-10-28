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
#include <carousel/componentsystem/IComponentExtension.h>
#include <components/qmlscripting/qmlscripting_global.h>

class IServiceLocator;
class QJSEngine;

/*!
 * @brief
 *   This interface used by the IScriptEngineConfigurationDelegate to configure QJSEngine
 *   by the component extension.
 * @details
 *   If some component wants to extend script with new funcitons or types, or register wrappers
 *   for some non-QObject classes, it should be a child of the QmlScriptingComponent. This mean a
 *   dependency of component parent name:  @a "org.carousel.QmlScripting". Then to get chance for
 *   registration, this component should also provide IScriptExtension extension. The overridden
 *   IScriptExtension::configureEngine method will be invoked every time, when QJSEngine
 *   configuration is needed. So, in your extension you can register what ever you want in the
 *   QJSEngine.
 *
 * @sa IComponent::extension(), IScriptEngineConfigurationDelegate
 */
class QML_SCRIPTING_API IScriptExtension : public IComponentExtension
{
public:
    /*!
     * @details
     * @constructor{IScriptExtension}.
     */
    IScriptExtension(){}

    /*!
     * @details
     *   This method will be invoked every time when a new instance of the QJSEngine
     *   is needed to be configured by other components. Usually each execution of the
     *   IScriptUnit is required a new engine.
     *
     *   Implement this method to extend an @a engine with additional functions, classes or
     *   wrappers for your types.
     *
     *   You can use @a locator to obtain some services and register them in the @a engine.
     */
    virtual void configureEngine(IServiceLocator *locator, QJSEngine *engine) = 0;

private:
    Q_DISABLE_COPY(IScriptExtension)
};
