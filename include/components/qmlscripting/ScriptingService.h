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
#include <components/qmlscripting/IScriptEngineFactory.h>
#include <components/qmlscripting/IScriptingService.h>

#include <QtCore/QSet>

class IComponent;
class IComponentManager;
class IServiceLocator;
class ScriptConsole;

/*!
 * @brief
 *   It is default implementation of the IScriptingService and IScriptEngineFactory interfaces.
 * @details
 *   This service provides references to the important parts of the QmlScripting component -
 *   IScriptConsole and IScriptCollection. While these objects are used to evaluate scripts,
 *   there is also one more important reference - to the IScriptEngineConfigurationDelegate.
 *   This delegate is invoked every time to configure QJSEngine when new script is evaluated
 *   by IScriptUnit or when new component is started. It is allows new components to extend
 *   JavaScript with custom types, functions or wrappers for their objects.
 *
 *   It is registered in the service locator by the QmlScriptingComponent.
 *   You can locate to this service from the service locator:
 * @code
 *   IScriptingService *service = serviceLocator->locate<IScriptingService>();
 *   IScriptConsole *console = service->console();
 * @endcode
 *
 *   Also it implements the IScriptEngineFactory to create configured QJSEngine for the
 *   ScriptUnit.
 */
class QML_SCRIPTING_API ScriptingService : public IScriptingService, public IScriptEngineFactory
{
    Q_OBJECT
public:
    /*!
     * @details
     * @constructor{ScriptingService}.
     *   Does not takes ownership for locator;
     */
    explicit ScriptingService(IServiceLocator *locator, IComponentManager *manager, QObject *parent = nullptr);

    /*!
     * @details
     * @constructor{ScriptingService}.
     *   A @a startScript script will be laoded and started right after IComponentManager::startedUp signal.
     *   Does not takes ownership for locator;
     */
    ScriptingService(IServiceLocator *locator, IComponentManager *manager, const QString &startScript, QObject *parent = nullptr);

    ~ScriptingService();

    /*!
     * @details
     *   Gets the script console.
     */
    IScriptConsole *console() override;

    /*!
     * @details
     *   Gets the scripts, that loaded into the application.
     */
    IScriptCollection *scripts() override;

    /*!
     * @details
     *   Gets the delegate which is used for QJSEngine configuration.
     */
    IScriptEngineConfigurationDelegate *delegate() override;

    /*!
     * @details
     *   Gets the delegate which is used for QJSEngine configuration.
     */
    const IScriptEngineConfigurationDelegate *delegate() const override;

    /*!
     * @details
     *   Sets the delegate which is used for QJSEngine configuration.
     *   This delegate is used for configuration console() engine right after component manager
     *   started up and as soons as new components are started.
     */
    void setDelegate(IScriptEngineConfigurationDelegate *delegate) override;

    /*!
     * @details
     *   Creates a new instance of the QJSEngine class and populated with new functions
     *   or types from other components.
     *
     *   Also, during configuration, an @a output is set in such way, that all
     *   output, obtained during execution by the QJSEngine will be redirected
     *   to this handler.
     *
     *   A @a parent could be used as a parent for created engine.
     *
     *   Note, that it does not takes ownership for created engine;
     */
    QJSEngine *createEngine(IOutputHandler *output = nullptr, QObject *parent = nullptr) override;

protected slots:
    /*!
     * @details
     *   After component manager started up, service configures console engine using
     *   all started components and also subscribes to the IComponentManager::componentStarted
     *   signal for configuration engine using newly started components.
     */
    void onComponentManagerStartedUp();

    /*!
     * @details
     *   Configures console engine using a just started @a component.
     */
    void onComponentStartedUp(IComponent *component);

private:
    Q_DISABLE_COPY(ScriptingService)

    void setUpEngine(QJSEngine* engine, IOutputHandler *output);

private slots:
    void runStartScript();

private:
    IComponentManager *m_componentManager;
    IScriptEngineConfigurationDelegate *m_scriptExtensionConfigurationDelegate;
    ScriptConsole *m_console;
    IScriptCollection *m_scripts;
    QString m_startScript;
};

