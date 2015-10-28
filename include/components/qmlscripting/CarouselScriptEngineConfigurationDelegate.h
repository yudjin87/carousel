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
#include <components/qmlscripting/IScriptEngineConfigurationDelegate.h>

class IOutputHandler;
class IServiceLocator;
class IScriptExtension;
class QJSValue;
class QScriptContext;

/*!
 * @brief
 *   It is a default implementation of the IScriptEngineConfigurationDelegate interface.
 * @details
 *   Each time when new QJSEngine is created to evaluate some JavaScript,
 *   this the configureFromComponent() method is invoked by the ScriptingService
 *   for each component to get it a chance to register custom types, new functions
 *   and other objects. Also it is called when new component is started at runtime.
 *
 * @sa IScriptExtension
 */
class QML_SCRIPTING_API CarouselScriptEngineConfigurationDelegate : public IScriptEngineConfigurationDelegate
{
    Q_OBJECT
public:
    /*!
     * @details
     * @constructor{CarouselScriptEngineConfigurationDelegate} using specified @a locator for wrapping it for
     *   script.
     */
    CarouselScriptEngineConfigurationDelegate(IServiceLocator *locator, QObject *parent = nullptr);

public slots:
    /*!
     * @details
     *   Configures specified @a engine using IScriptExtension extension from the @a component.
     *   Does nothing, if component does not provide IScriptExtension.
     */
    void configureFromComponent(IComponent *component, QJSEngine *engine) override;

    /*!
     * @details
     *   Configures specified @a engine with default types and functions like explore(), include() and
     *   prototype for the QPoint.
     *
     *   An @a output is a handler for the print() function. Each time when print() is invoked
     *   from the script, IOutputHandler::print() will be invoked.
     */
    void configureDefaults(QJSEngine *engine, IOutputHandler *output = nullptr) override;

protected:
    virtual void configureExtension(IServiceLocator *locator, QJSEngine *engine, IScriptExtension *extension);
    virtual void configureServiceLocator(QJSEngine *engine, IServiceLocator *locator);

private:
    Q_DISABLE_COPY(CarouselScriptEngineConfigurationDelegate)
    static QJSValue findValue(QJSEngine *engine, const QString &name);

private:
    IServiceLocator *m_locator;
};

