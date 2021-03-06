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
#include <carousel/carousel_global.h>
#include <carousel/componentsystem/DependenciesSolvingResult.h>

#include <QtCore/QObject>
#include <QtCore/QList>

class IComponent;
class IComponentDependencies;
class IServiceLocator;

template <typename TItem>
class ObservableList;

/*!
 * @brief
 *   The IComponentManager holds information about the components that can be used by the application.
 * @details
 *   Each component (described in a IComponent and ComponentDefinition classes, stores the name,
 *   description and availability of the component) that was statically registered or dynamically discovered
 *   by providers will be added to the ComponentManager after boot loading sequence in
 *   CarouselBootloader::configureComponentManager() method. Components also can be added and
 *   started during run-time.
 *
 *   Then, after checking and resolving dependencies, all enabled components will be started
 *   with IServiceLocator reference as @a initialziation @a data.
 *   It enables components to get access to shared servces of your application.
 *
 *   Also manager uses IComponentDependencies for components sorting and finding components dependencies.
 *
 * @note it takes ownership for added components, and also takes for the IComponentDependencies.
 */
class CAROUSEL_API IComponentManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QList<IComponent *> orphanComponents READ orphanComponents)
    Q_PROPERTY(QList<IComponent *> stoppedComponents READ stoppedComponents)
    Q_PROPERTY(QList<IComponent *> startedComponents READ startedComponents)
public:
    IComponentManager(){}
    virtual ~IComponentManager(){}

    /*!
     * @details
     *   Adds a new component. Component with same name should not already exists in
     *   the manager.
     *
     *   A newly is appended to the stoppedComponents() list and to the dependencies().
     *   This method sets isChecked() to false.
     * @param component
     *   If manager already has component with same name as @a component - the last one will
     *   not be added to the manager. The same for the null pointer - it will be ignored.
     *
     *   Returns @a true if component was succesfully added. If it is a null point or already
     *   existed one - returns @a false. Note, that IComponentManager does not take ownership
     *   for component, which was not successfully added.
     *
     * @sa IComponentDependencies::addComponent()
     */
    virtual bool addComponent(IComponent *component) = 0;

    /*!
     * @details
     *   Uses DependencySolver for checking of added components according to their dependencies.
     *
     *   Returns a dependencies solving result, that contains a list of distinct components
     *   and a list of components, those dependencies were not found.
     *
     *   It caches resulting value for prefomance, but addComponent() is resets it.
     *
     * @sa isChecked()
     */
    virtual DependenciesSolvingResult check() = 0;

    /*!
     * @details
     *   Returns a list of all added components.
     *   It is a shortcut to the IComponentDependencies::components().
     *
     * @sa IComponentDependencies::dependencies().
     */
    virtual const ObservableList<IComponent *> &components() const = 0;

    /*!
     * @details
     *   Returns a component dependencies.
     */
    virtual const IComponentDependencies &dependencies() const = 0;

    /*!
     * @details
     *   Uses DependencySolver for checking of added components according to their dependencies.
     *
     *   Returns a dependencies solving result, that contains a list of distinct components
     *   and a list of components, those dependencies were not found.
     *
     * @sa check()
     */
    virtual bool isChecked() const = 0;

    /*!
     * @details
     *   Gets an initialization data that will be passed to the started components.
     * @sa startupComponent()
     */
    virtual IServiceLocator *serviceLocator() const = 0;

    /*!
     * @details
     *   Returns a list of missing parent names those children were added
     *   to the manager.
     *
     *   This list is populated after check() or startup/shutdown components
     *   and resets after the addComponent() call.
     *
     * @sa orphanComponents()
     */
    virtual QStringList missingComponents() const = 0;

    /*!
     * @details
     *   Returns a list of components those parents were not added
     *   to the manager while components were started.
     *
     *   This list is populated after check() or startup/shutdown components
     *   and resets after the addComponent() call.
     *
     * @sa missingComponents()
     */
    virtual QList<IComponent *> orphanComponents() const = 0;

    /*!
     * @details
     *   Returns a list of already stopped or non-started yet components.
     */
    virtual QList<IComponent *> stoppedComponents() const = 0;

    /*!
     * @details
     *   Returns a list of started components.
     */
    virtual QList<IComponent *> startedComponents() const = 0;

    /*!
     * @details
     *   Shuts down all the components. Call this method when your application is going to
     *   quit.
     * @sa startup()
     */
    virtual void shutdown() = 0;

    /*!
     * @details
     *   Shuts down the specified component and all its implicit children,
     *   obtained by IComponentDependencies::completeListWithParent() in such order, that
     *   children will be shut down first.
     *
     *   Shut component is moved from the startedComponents() to
     *   the stoppedComponents() list.
     *
     *   Ignores null pointer or unexisting component.
     *
     *   Returns a DependenciesSolvingResult with components that
     *   were realy shut down. Components that already were shut down
     *   will not appear to the result list.
     */
    virtual DependenciesSolvingResult shutdownComponent(IComponent *component) = 0;

    /*!
     * @details
     *   This method is added for convinient. It is a shortkey to the
     *   shutdownComponents(components()).
     *
     *   Returns a DependenciesSolvingResult with components that
     *   were realy shut down. Components that already were shut down
     *   will not appear to the result list.
     *
     * @sa shutdownComponents()
     *
     */
    virtual DependenciesSolvingResult shutdownAllComponents() = 0;

    /*!
     * @details
     *   Shuts down specified components in such order, that
     *   children will be shut down before their parents.
     *
     *   Shut components are moved from the startedComponents() to
     *   the stoppedComponents() list.
     *
     *   Returns a DependenciesSolvingResult with components that
     *   were realy shut down. Components that already were shut down
     *   will not appear to the result list.
     */
    virtual DependenciesSolvingResult shutdownComponents(const QList<IComponent *> &components) = 0;

    /*!
     * @details
     *   Begins working and starts components which were added on the
     *   start of application. Starts only enabled components.
     *
     *   Components with disabled parent components will not be
     *   started.
     *
     *   Initialization data will be passed to the started components (if any).
     *
     * @sa shutdown()
     */
    virtual DependenciesSolvingResult startup() = 0;

    /*!
     * @details
     *   Implicitly calls check() and starts (if resolving) up the specified components and
     *   all its parents, obtained by IComponentDependencies::completeListWithChild() in
     *   such order, that parents will be started first. All started components became
     *   enabled.
     *
     *   Components will not start if parent component could not start.
     *
     *   Initialization data will be passed to the started components (if any).
     *   Returns a dependencies solving result, that contains a list of distinct components
     *   and a list of components, those dependencies were not found.
     *
     *   All started components will be moved from the stoppedComponents() to the
     *   startedComponents() list.
     *
     *   Returns a DependenciesSolvingResult with components that
     *   were realy started. Components that already were started
     *   will not appear to the result list.
     *
     * @note component should be added to the manager before starting.
     * @sa addComponent(), check()
     */
    virtual DependenciesSolvingResult startupComponent(IComponent *component) = 0;

    /*!
     * @details
     *   This method is added for convinient. It is a shortkey to the
     *   startupComponents(components()).
     *
     *   Initialization data will be passed to the started components (if any).
     *
     *   Returns a DependenciesSolvingResult with components that
     *   were realy started. Components that already were started
     *   will not appear to the result list.
     *
     * @sa addComponent(), check(), startupComponents()
     */
    virtual DependenciesSolvingResult startupAllComponents() = 0;

    /*!
     * @details
     *   Implicitly calls check() and starts (if resolving) up the specified components and
     *   all its parents, obtained by IComponentDependencies::completeListWithChild() in
     *   such order, that parents will be started first. All started components became
     *   enabled.
     *
     *   Components will not start if parent component could not start.
     *
     *   Initialization data will be passed to the started components (if any).
     *   Returns a dependencies solving result, that contains a list of distinct components
     *   and a list of components, those dependencies were not found.
     *
     *   Components, those parents were not added to manager, will be appended to the
     *   orphanComponents() list and names of their missing parents will be appended to
     *   the missingComponents() list. All started components will be moved from the
     *   stoppedComponents() to the startedComponents() list.
     *
     *   Returns a DependenciesSolvingResult with components that
     *   were realy started. Components that already were started
     *   will not appear to the result list.
     *
     * @note components should be added to the manager before starting.
     * @sa addComponent(), check(), startupAllComponents()
     */
    virtual DependenciesSolvingResult startupComponents(QList<IComponent *> components) = 0;

signals:
    /*!
     * @details
     *   This signal is emmited before @a manager will be shut down.
     */
    void aboutToShutDown();

    /*!
     * @details
     *   This signal is emmited after @a manager startup() call.
     */
    void startedUp();

    /*!
     * @details
     *   This signal is emmited before @a component will be shut down by the
     *   IComponentManager.
     */
    void componentAboutToShutDown(IComponent *component);

    /*!
     * @details
     *   This signal is emmited when @a component is shut down by the
     *   IComponentManager.
     */
    void componentShutDown(IComponent *component);

    /*!
     * @details
     *   This signal is emmited when @a component is started up by the
     *   IComponentManager.
     */
    void componentStarted(IComponent *component);
};

