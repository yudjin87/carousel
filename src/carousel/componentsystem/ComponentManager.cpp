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

#include "componentsystem/ComponentManager.h"
#include "componentsystem/ComponentDefinition.h"
#include "componentsystem/ComponentDependencies.h"
#include "componentsystem/ComponentCollection.h"
#include "componentsystem/IComponent.h"

#include "logging/LoggerFacade.h"
#include "utils/IServiceLocator.h"

#include <QtCore/QSet>
#include <QtCore/QCoreApplication>

namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("ComponentManager");
}

ComponentManager::ComponentManager(IServiceLocator *serviceLocator, QObject *parent)
    : m_shutDownFunc(&ComponentManager::shutdownCheckedComponent)
    , m_startUpFunc(&ComponentManager::enableAndStartComponent)
    , m_serviceLocator(serviceLocator)
    , m_components(new ComponentDependencies())
    , m_startedComponents(QList<IComponent *>())
    , m_stoppedComponents(QList<IComponent *>())
    , m_orphanComponents(QSet<IComponent *>())
    , m_isCheck(false)
    , m_started(false)
{
    QObject::setParent(parent);
}

ComponentManager::ComponentManager(IServiceLocator *serviceLocator, IComponentDependencies *dependencies, QObject *parent)
    : m_shutDownFunc(&ComponentManager::shutdownCheckedComponent)
    , m_startUpFunc(&ComponentManager::enableAndStartComponent)
    , m_serviceLocator(serviceLocator)
    , m_components(dependencies)
    , m_startedComponents(QList<IComponent *>())
    , m_stoppedComponents(QList<IComponent *>())
    , m_orphanComponents(QSet<IComponent *>())
    , m_isCheck(false)
    , m_started(false)
{
    QObject::setParent(parent);
    Q_ASSERT(m_components != nullptr);
}

ComponentManager::~ComponentManager()
{
    for (IComponent *comp : m_components->components())
        delete comp;

    delete m_components;
    m_components = nullptr;
}

bool ComponentManager::addComponent(IComponent *component)
{
    bool result = addComponentInternal(component);
    if (!result)
        return false;

    Log.d(QString("Component \"%1\" is added. Reset check result.").arg(component->name()));
    resetCheck();
    return result;
}

DependenciesSolvingResult ComponentManager::check()
{
    if (isChecked()) {
        Log.d("Already checked. Skip new check request.");
        return m_checkResult;
    }

    m_isCheck = true;

    DependenciesSolvingResult result = m_components->orderedComponents();
    m_checkResult = result;

    return m_checkResult;
}

const ObservableList<IComponent *> &ComponentManager::components() const
{
    return m_components->components();
}

const IComponentDependencies &ComponentManager::dependencies() const
{
    return *m_components;
}

bool ComponentManager::isChecked() const
{
    return m_isCheck;
}

IServiceLocator *ComponentManager::serviceLocator() const
{
    return m_serviceLocator;
}

QStringList ComponentManager::missingComponents() const
{
    return m_checkResult.missing();
}

QList<IComponent *> ComponentManager::orphanComponents() const
{
    return m_checkResult.orphans();
}

QList<IComponent *> ComponentManager::stoppedComponents() const
{
    return m_stoppedComponents;
}

QList<IComponent *> ComponentManager::startedComponents() const
{
    return m_startedComponents;
}

void ComponentManager::shutdown()
{
    if (!m_started) {
        Log.e("Shutdown is called but startup was not!");
        return;
    }

    Log.i("Prepare for shut down: shut down all components.");
    onAboutToShutDown();
    m_shutDownFunc = &ComponentManager::forceShutdownCheckedComponent;
    shutdownAllComponents();
    m_shutDownFunc = &ComponentManager::shutdownCheckedComponent;
    Log.i("All components have been shut down.");
}

DependenciesSolvingResult ComponentManager::shutdownComponent(IComponent *component)
{
    QList<IComponent *> components;
    components.push_back(component);
    return shutdownComponents(components);
}

DependenciesSolvingResult ComponentManager::shutdownAllComponents()
{
    return shutdownComponents(m_components->components().toList());
}

DependenciesSolvingResult ComponentManager::shutdownComponents(const QList<IComponent *> &components)
{
    if (components.empty()) {
        Log.d("Nothing to shutdown - empty collection.");
        return DependenciesSolvingResult();
    }

    Log.d("Reverse components order before shut down.");

    DependenciesSolvingResult solvingResult = m_components->completeListWithParents(components);
    QList<IComponent *> componentsToShutdown = solvingResult.ordered();
    QList<IComponent *> realyShutdownComponents;
    for (IComponent *comp : componentsToShutdown) {
        if (!m_components->components().contains(comp)) {
            Log.i(QString("Can not shutdown unexisting component: \"%1\".").arg(comp->name()));
            continue;
        }

        if (!comp->started()) {
            Log.i(QString("\"%1\" component is already shut down. Skip it.").arg(comp->name()));
            continue;
        }

        realyShutdownComponents.push_back(comp);
        onComponentAboutToShutDown(comp);
        (this->*(m_shutDownFunc))(comp);
        Log.i(QString("\"%1\" component is shut down.").arg(comp->name()));
        onComponentShutDown(comp);
    }

    return DependenciesSolvingResult(realyShutdownComponents);
}

DependenciesSolvingResult ComponentManager::startup()
{
    if (m_started) {
        Log.e("Startup is called second time without shut down!");
        return DependenciesSolvingResult();
    }

    Log.i("Preparing for startup. Start all enabled components that were added to the manager.");
    m_startUpFunc = &ComponentManager::startCheckedComponent;
    DependenciesSolvingResult result = startupAllComponents();
    m_startUpFunc = &ComponentManager::enableAndStartComponent;

    Log.i(QString("Startup finished. %1 started and %2 orphans from %3 components.")
          .arg(result.ordered().size())
          .arg(result.orphans().size())
          .arg(result.ordered().size() + result.orphans().size()));

    m_started = true;

    onStartedUp();
    return result;
}

DependenciesSolvingResult ComponentManager::startupComponent(IComponent *component)
{
    QList<IComponent *> components;
    components.push_back(component);

    return startupComponents(components);
}

DependenciesSolvingResult ComponentManager::startupAllComponents()
{
    return startupComponents(m_components->components().toList());
}

DependenciesSolvingResult ComponentManager::startupComponents(QList<IComponent *> components)
{
    if (components.empty()) {
        Log.d("Nothing to start - empty collection.");
        return DependenciesSolvingResult();
    }

    check();

    // Try to resolve orphan components from the previous starts, because they parents
    // may appear
    components.append(m_orphanComponents.toList());
    DependenciesSolvingResult solvingResult = m_components->completeListWithChildren(components);

    QSet<IComponent *> skippedComponents;
    QList<IComponent *> componentsToStart = solvingResult.ordered();
    QList<IComponent *> reallyStartedComponents;
    Log.i("Components to start:");
    for (IComponent *comp : componentsToStart) {
        Log.i(QString("\"%1\"").arg(comp->name()));
    }

    for (IComponent *comp : componentsToStart) {
        if (comp->started() || skippedComponents.contains(comp))
            continue;

        if (tryToStartComponent(comp)) {
            onComponentStarted(comp);
            reallyStartedComponents.push_back(comp);
        } else {

            Log.i(QString("Can not startup component: \"%1\".").arg(comp->name()));

            QStringList skipedChildren;
            DependenciesSolvingResult children = m_components->completeListWithParent(comp);
            for (IComponent *skippedComp : children.ordered()) {
                skippedComponents.insert(skippedComp);
                if (skippedComp != comp)
                    skipedChildren.append(skippedComp->name()); // don't include name of failed component in the message
            }

            QString info = QString("Can not startup component: \"%1\". Following child component(s) will not started too: %1.").arg(skipedChildren.join(","));
            Log.i(info);
        }
    }

    QList<IComponent *> orphans = solvingResult.orphans();
    if (!orphans.empty()) {
        QStringList orphanComponents;
        for (IComponent *comp : orphans) {
            // HACK. We cannot expose non-const definition from the component, but we should set error message
            const_cast<ComponentDefinition *>(comp->definition())->setError("Can not startup, because parent component(s) are not started.");
            orphanComponents.append(comp->name());
        }

        Log.i(QString("Following components were not started (orphans): %1.").arg(orphanComponents.join(", ")));
        m_orphanComponents += orphans.toSet();
    }

    return DependenciesSolvingResult(reallyStartedComponents);
}

void ComponentManager::onStartedUp()
{
    emit startedUp();
}

void ComponentManager::onAboutToShutDown()
{
    emit aboutToShutDown();
}

void ComponentManager::onComponentStarted(IComponent *component)
{    
    m_stoppedComponents.removeOne(component);
    m_startedComponents.push_back(component);
    emit componentStarted(component);
}

void ComponentManager::onComponentAboutToShutDown(IComponent *component)
{
    emit componentAboutToShutDown(component);
}

void ComponentManager::onComponentShutDown(IComponent *component)
{
    m_startedComponents.removeOne(component);
    m_stoppedComponents.push_back(component);
    emit componentShutDown(component);
}

bool ComponentManager::startCheckedComponent(IComponent *component)
{
    Log.i("Ensure before startup that component is available.");

    if (component->availability() != IComponent::Enabled) {
        Log.i(QString("Can not startup unavailable component: \"%1\".").arg(component->name()));
        return false;
    }

    if (!component->startup(m_serviceLocator))
        return false;

    component->setState(IComponent::Running);
    return true;
}

bool ComponentManager::enableAndStartComponent(IComponent *component)
{
    component->setAvailability(IComponent::Enabled);
    if (!component->startup(m_serviceLocator))
        return false;

    component->setState(IComponent::Running);
    return true;
}

void ComponentManager::shutdownCheckedComponent(IComponent *component)
{
    // We should not shutdown built in component
    if (component->definition()->isBuiltIn())
        return;

    component->setAvailability(IComponent::Disabled);
    component->shutdown(m_serviceLocator);
    component->setState(IComponent::Stopped);
}

void ComponentManager::forceShutdownCheckedComponent(IComponent *component)
{
    component->shutdown(m_serviceLocator);
    component->setState(IComponent::Stopped);
}

bool ComponentManager::tryToStartComponent(IComponent *component)
{
    if (!m_components->components().contains(component)) {
        Log.i(QString("Can not start unexisting component: \"%1\".").arg(component->name()));
        return false;
    }

    Log.i(QString("Starting \"%1\" component").arg(component->name()));

    const QList<IComponent::State> startableStates { IComponent::Initialized, IComponent::Stopped, IComponent::Orphan};
    if (!startableStates.contains(component->state())) {
        Log.i(QString("Could not start component \"%1\" with state %2.").arg(component->name()).arg(component->state()));
        return false;
    }

    if (!(this->*(m_startUpFunc))(component)) {
        Log.i(QString("Component \"%1\" startup was failed.").arg(component->name()));
        return false;
    }

    Log.i(QString("Component \"%1\" is started.").arg(component->name()));
    return true;
}

bool ComponentManager::addComponentInternal(IComponent *component)
{
    if (!m_components->addComponent(component)) {
        Log.i(QString("Cannot add component \"%1\", because it already exist.").arg(component->name()));
        return false;
    }

    m_stoppedComponents.push_back(component);
    return true;
}

void ComponentManager::resetCheck()
{
    m_isCheck = false;
    m_checkResult = DependenciesSolvingResult();
}

