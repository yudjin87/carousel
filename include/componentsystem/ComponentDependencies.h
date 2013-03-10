/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * Carousel - Qt-based managed component library.
 *
 * Copyright: 2011-2013 Carousel team
 * Authors:
 *   Eugene Chuguy <eugene.chuguy@gmail.com>
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

#ifndef COMPONENTDEPENDENCIES_H
#define COMPONENTDEPENDENCIES_H

#include "componentsystem/IComponentDependencies.h"

#include <QtCore/QObject>
#include <QtCore/QStringList>

/*!
 * @brief
 *   It is the default implementation of the IComponentDependencies. ComponentManager uses this class
 *   by default.
 * @details
 *   Each component (described in a IComponent and IComponentDescriptionExtension classes, stores the name,
 *   description and availability of the component) that statically registered or dynamically discovered
 *   by providers will be added to the IComponentDependencies through IComponentManager after boot loading
 *   sequence in CarouselBootloader::_configureComponentManager() method.
 *
 *   Also ComponentDependencies uses DependencySolver for components sorting and finding components
 *   dependencies.
 *
 *   Then you can get any dependnecies between the components using specified methods.
 * @note it does not take ownership for added components.
 */
class COMP_API ComponentDependencies : public QObject, public IComponentDependencies
{
    Q_OBJECT
public:
    ComponentDependencies(QObject *parent = nullptr);
    ~ComponentDependencies();

    /*!
     * @details
     *   Adds a new component. Component with same name should not already exists in.
     *
     * @param ip_component
     *   If IComponentDependencies already has component with same name as @a ip_component
     *   - the last one will not be added. The same for the null pointer - it will be ignored.
     *
     *   Returns @a true if component was succesfully added. If it is a null point or already
     *   existed one - returns @a false.
     */
    bool addComponent(IComponent *ip_component);

    /*!
     * @details
     *   Returns a dependencies solving result, that contains a list of distinct components
     *   and a list of components, those dependencies were not found. The component list
     *   will contains all immediate and extended parents for specified child component.
     *
     *   The components are ordered in such way, that parents are firsts and children are lasts.
     *
     * @param ip_forChild
     *   The component to get the dependencies (or parents) for.
     */
    DependenciesSolvingResult completeListWithChild(IComponent *ip_forChild) const;

    /*!
     * @details
     *   Returns a dependencies solving result, that contains a list of distinct components
     *   and a list of components, those dependencies were not found. The component list
     *   will contains all immediate and extended parents for specified children components.
     *
     *   The components are ordered in such way, that parents are firsts and children are lasts.
     *
     * @param i_forChildren
     *   The components to get the dependencies (or parents) for.
     */
    DependenciesSolvingResult completeListWithChildren(const QList<IComponent *> &i_forChildren) const;

    /*!
     * @details
     *   Returns a dependencies solving result, that contains a list of distinct components
     *   and a list of components, those dependencies were not found. The component list
     *   will contains all immediate and extended children for specified parent component.
     *
     *   The components are ordered in such way, that children are firsts and parents are lasts.
     *
     * @param ip_forParent
     *   The component to get the components that depend on it (or its implicit children).
     */
    DependenciesSolvingResult completeListWithParent(IComponent *ip_forParent) const;

    /*!
     * @details
     *   Returns a dependencies solving result, that contains a list of distinct components
     *   and a list of components, those dependencies were not found. The component list
     *   will contains all immediate and extended children for specified parents components.
     *
     *   The components are ordered in such way, that children are firsts and parents are lasts.
     *
     * @param ip_forParents
     *   The components to get the other components that depend on they (or their implicit children).
     */
    DependenciesSolvingResult completeListWithParents(const QList<IComponent *> &ip_forParents) const;

    /*!
     * @details
     *   Finds the component by its name.
     *   Null pointer, if list is empty, or if component with specified name was not added.
     */
    IComponent *componentByName(const QString &i_byName) const;

    /*!
     * @details
     *   Returns a list of added components.
     */
    QList<IComponent *> components() const;

    /*!
     * @details
     *   Returns a dependencies solving result for cpecified child, that contains a list of
     *   distinct components and a list of components, those dependencies were not found.
     *   E.g. if we have components
     * @code
     *   A <- B <- C <- E
     *             D <- E
     * @endcode
     *   then, getParentComponents(E) will return {A, B, C, D} components.
     * @param ip_forChild
     *   The component to get the dependencies (or parents) for.
     *   If @a ip_forChild is null - result with empty collections will be returned.
     */
    DependenciesSolvingResult getParentComponents(const IComponent *ip_forChild) const;

    /*!
     * @details
     *   Returns a dependencies solving result for cpecified parent, that contains a list of
     *   distinct components and a list of components, those dependencies were not found.
     *   E.g. if we have components
     * @code
     *   A <- B <- C <- E
     *             C <- D
     * @endcode
     *   then, getChildComponents(C) will return {E, D} components.
     * @param ip_forParent
     *   The component to get the other components that depend on it (or its implicit children).
     *   If @a ip_forParent is null or component with such name does not exists - result with
     *   empty collections will be returned.
     */
    DependenciesSolvingResult getChildComponents(const IComponent *ip_forParent) const;

    /*!
     * @details
     *   Returns a dependencies solving result for all components, that contains a list of distinct
     *   components and a list of components, those dependencies were not found. The component list
     *   will contains all immediate and extended parents for specified children components.
     *
     *   The components are ordered in such way, that parents are firsts and children are lasts.
     *
     *   It is a shortkey for the
     * @code
     *   completeListWithChildren(components())
     * @endcode
     */
    DependenciesSolvingResult orderedComponents() const;

private:
    static DependenciesSolvingResult solveDependencies(const QList<IComponent *> &i_components);

private:
    QList<IComponent *> m_components;
};


#endif // COMPONENTDEPENDENCIES_H
