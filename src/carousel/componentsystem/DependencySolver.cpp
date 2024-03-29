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

#include "componentsystem/DependencySolver.h"
#include "logging/LoggerFacade.h"
#include "utils/ListDictionary.h"

#include <algorithm>
#include <iterator>

namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("DependencySolver");
}

DependencySolver::DependencySolver()
    : m_dependencyMatrix(new ListDictionary<QString, QString>())
{
}

DependencySolver::~DependencySolver()
{
    delete m_dependencyMatrix;
    m_dependencyMatrix = nullptr;
}

void DependencySolver::addComponent(const QString &name)
{
    if (name.isEmpty()) {
        Log.w("The provided component name must not be null or empty.");
        return;
    }

    addToDependencyMatrix(name);
    addToKnownComponents(name);
}

void DependencySolver::addDependency(const QString &childComponent, const QString &parentComponent)
{
    if (childComponent.isEmpty()) {
        Log.w("The provided child component component name must not be null or empty.");
        return;
    }

    if (parentComponent.isEmpty()) {
        Log.w("The provided parent component name must not be null or empty.");
        return;
    }

    if (!m_knownComponents.contains(childComponent)) {
        Log.w(QString("Cannot add dependency for unknown component \"%1\". Add it first.").arg(childComponent));
        return;
    }

    addToDependencyMatrix(parentComponent);
    m_dependencyMatrix->add(parentComponent, childComponent);
}

int DependencySolver::componentsCount() const
{
    return m_knownComponents.size();
}

void DependencySolver::removeComponent(const QString &component)
{
    if (m_dependencyMatrix->contains(component))
        m_dependencyMatrix->remove(component);

    if (m_knownComponents.contains(component, Qt::CaseInsensitive))
        m_knownComponents.removeOne(component);
}

int Compare(const QString &a, const QString &b)
{
    return QString::compare(a, b);
}

bool DependencySolver::solve(QStringList &ordered, QStringList &orphans, QStringList &missing) const
{
    QStringList orderedList;
    while (orderedList.size() < m_dependencyMatrix->size()) {
        QStringList leaves = findLeaves(orderedList);
        if ((leaves.size() == 0) && (orderedList.size() < m_dependencyMatrix->size()))
            return false; // Cyclic dependencies are found

        orderedList.append(leaves);
    }

    // Clean ordered list
    for (QString unknownComponent : orderedList) {
        if (m_knownComponents.contains(unknownComponent))
            continue;

        // Remove missing from sorted
        missing.append(unknownComponent);
        orderedList.removeOne(unknownComponent);

        // Remove orphans from sorted
        removeMissingComponents(unknownComponent, orderedList, orphans);
    }

    std::reverse(orderedList.begin(), orderedList.end());
    ordered = orderedList;

    return true;
}

void DependencySolver::removeMissingComponents(const QString &unknownComponent, QStringList &orderedList, QStringList &orphans) const
{
    const QStringList &children = *m_dependencyMatrix->value(unknownComponent);
    for (QString orphan : children) {
        orderedList.removeOne(orphan);
        orphans.append(orphan);
        removeMissingComponents(orphan, orderedList, orphans);
    }
}

void DependencySolver::addToDependencyMatrix(const QString &component)
{
    if (!m_dependencyMatrix->contains(component))
        m_dependencyMatrix->add(component);
}

void DependencySolver::addToKnownComponents(const QString &component)
{
    if (!m_knownComponents.contains(component, Qt::CaseInsensitive))
        m_knownComponents.push_back(component);
}

QStringList DependencySolver::findLeaves(const QStringList &skip) const
{
    QStringList result;

    for (QString parentComponent : m_dependencyMatrix->keys()) {
        if (skip.contains(parentComponent))
            continue;

        int count = 0;
        const QStringList &children = *m_dependencyMatrix->value(parentComponent);
        for (QString child : children) {
            if (skip.contains(child))
                continue;

            ++count;
        }
        if (count == 0)
            result.append(parentComponent);
    }

    return result;
}

