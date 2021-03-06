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

#include "componentsystem/ComponentDependencies.h"
#include "componentsystem/DependencySolver.h"
#include "componentsystem/IComponent.h"
#include "componentsystem/ComponentCollection.h"
#include "componentsystem/ComponentDefinition.h"
#include "componentsystem/ParentDefinition.h"

#include "logging/LoggerFacade.h"

namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("ComponentDependencies");
}

ComponentDependencies::ComponentDependencies(QObject *parent)
    : QObject(parent)
    , m_components(new ComponentCollection(this))
{
}

ComponentDependencies::~ComponentDependencies()
{
}

bool ComponentDependencies::addComponent(IComponent *component)
{
    if (component == nullptr) {
        Log.w("Attemp to add null component. Ignoring it.");
        return false;
    }

    if (componentByName(component->name()) != nullptr) {
        Log.w("Attemp to add already existing component. Ignoring it.");
        return false;
    }

    m_components->push_back(component);
    return true;
}

DependenciesSolvingResult ComponentDependencies::completeListWithChild(IComponent *forChild) const
{
    QList<IComponent *> components;
    components.push_back(forChild);

    return completeListWithChildren(components);
}

DependenciesSolvingResult ComponentDependencies::completeListWithChildren(const QList<IComponent *> &forChildren) const
{
    if (forChildren.empty())
        return DependenciesSolvingResult();

    QList<IComponent *> completeList;
    QList<IComponent *> unresolvedList(forChildren);

    while (!unresolvedList.isEmpty()) {
        IComponent *componentInfo = unresolvedList[0];
        if (componentInfo == nullptr) {
            unresolvedList.removeFirst();
            continue;
        }

        QList<IComponent *> result = getParentDefinitions(componentInfo);
        bool isCompatible = true;
        for (IComponent *dependency : result) {
            if (dependency == nullptr)
                continue;

            if (!completeList.contains(dependency) && !unresolvedList.contains(dependency))
                unresolvedList.push_back(dependency);

            if (!componentInfo->isCompatible(dependency)) {
                Log.w("Skip incompatible component.");
                isCompatible = false;
            }

        }

        unresolvedList.removeFirst();

        if (isCompatible)
            completeList.push_back(componentInfo);
    }

    DependenciesSolvingResult result = solveDependencies(completeList);
    return result;
}

DependenciesSolvingResult ComponentDependencies::completeListWithParent(IComponent *forParent) const
{
    QList<IComponent *> components;
    components.push_back(forParent);

    return completeListWithParents(components);
}

DependenciesSolvingResult ComponentDependencies::completeListWithParents(const QList<IComponent *> &forParents) const
{
    if (forParents.empty())
        return DependenciesSolvingResult();

    DependencySolver solver;

    QList<IComponent *> completeList;
    QList<IComponent *> unresolvedList(forParents);

    // TODO: refactoring is needed.
    // Find all children for parents and reverse parent-children dependencies for correct ordering:
    while (!unresolvedList.isEmpty()) {
        IComponent *parent = unresolvedList[0];
        solver.addComponent(parent->name());

        DependenciesSolvingResult result = getChildComponents(parent);
        for (IComponent * child : result.ordered()) {
            if (!completeList.contains(child) && !unresolvedList.contains(child))
                unresolvedList.push_back(child);

            // We look all children for parents, so switch their dependencies:
            solver.addComponent(child->name());
            solver.addDependency(parent->name(), child->name());
        }

        unresolvedList.removeFirst();
        completeList.push_back(parent);
    }

    QStringList ordered;
    QStringList orphans;
    QStringList missing;

    bool hasCyclic = !solver.solve(ordered, orphans, missing);
    if (hasCyclic) {
        Log.d("At least one cyclic dependency has been found in the component manager. Cycles in the component dependencies must be avoided.");
        return DependenciesSolvingResult(ordered, orphans, missing, m_components->toList(), hasCyclic);
    }

    if (!missing.isEmpty()) {
        Log.d(QString("A component declared a dependency on another component which is not declared to be loaded. Missing component(s): %1")
              .arg(missing.join(", ")).toLatin1());
    }

    return DependenciesSolvingResult(ordered, orphans, missing, m_components->toList(), hasCyclic);
}

IComponent *ComponentDependencies::componentByName(const QString &byName) const
{
    if (m_components->empty())
        return nullptr;

    for (IComponent *com : *m_components) {
        if (com->name() == byName)
            return com;
    }

    return nullptr;
}

const ComponentCollection &ComponentDependencies::components() const
{
    return *m_components;
}

DependenciesSolvingResult ComponentDependencies::orderedComponents() const
{
    return completeListWithChildren(m_components->toList());
}

QList<IComponent *> ComponentDependencies::getParentDefinitions(const IComponent *forChild) const
{
    QList<IComponent *> result;
    getParentDefinitions(forChild, result);
    return result;
}

DependenciesSolvingResult ComponentDependencies::getChildComponents(const IComponent *forParent) const
{
    if (forParent == nullptr)
        return DependenciesSolvingResult();

    if (!this->componentByName(forParent->name()))
        return DependenciesSolvingResult();

    QList<IComponent *> components_to_return;

    for (IComponent *com : *m_components) {
        const ComponentDefinition *definition = com->definition();
        const ParentDefinitions &parents = definition->parents();
        if (parents.contains(forParent->name()))
            components_to_return.push_back(com);

    }

    return DependenciesSolvingResult(components_to_return);
}

DependenciesSolvingResult ComponentDependencies::solveDependencies(const QList<IComponent *> &components)
{
    QStringList ordered;
    QStringList orphans;
    QStringList missing;
    DependencySolver solver;

    for (IComponent *com : components) {
        solver.addComponent(com->name());

        const ComponentDefinition *definition = com->definition();
        const ParentDefinitions &parents = definition->parents();
        for(const ParentDefinition *dependency : parents) {
            if (!definition->isCompatible(parents)) {
                Log.w("Skip incompatible component.");
                //solver.removeComponent(com->name());
                //break;
            }
            solver.addDependency(com->name(), dependency->name());
        }
    }

    bool hasCyclic = !solver.solve(ordered, orphans, missing);
    if (hasCyclic) {
        Log.w("At least one cyclic dependency has been found in the component manager. Cycles in the component dependencies must be avoided.");
        return DependenciesSolvingResult(ordered, orphans, missing, components, hasCyclic);
    }

    if (!missing.isEmpty()) {
        Log.w(QString("A component declared a dependency on another component which is not declared to be loaded. Missing component(s): %1")
              .arg(missing.join(", ")).toLatin1());
    }

    return DependenciesSolvingResult(ordered, orphans, missing, components, hasCyclic);
}

void ComponentDependencies::getParentDefinitions(const IComponent *forChild, QList<IComponent *> &found) const
{
    if (forChild == nullptr)
        return;

    const ComponentDefinition *definition = forChild->definition();
    if (definition == nullptr)
        return;

    const ParentDefinitions &parents = definition->parents();

    for (const ParentDefinition *def : parents) {
        IComponent *parent = componentByName(def->name());
        if (parent == nullptr)
            continue;

        // Skip cyclic dependencies
        if (found.contains(parent))
            continue;

        found.push_back(parent);
        getParentDefinitions(parent, found);
    }
}

