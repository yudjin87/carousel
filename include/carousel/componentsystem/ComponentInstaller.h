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
#include <carousel/componentsystem/IComponentInstaller.h>

#include <QtCore/QList>

class IComponentDependencies;

/*!
 * @brief
 * @details
 */
class CAROUSEL_API ComponentInstaller : public IComponentInstaller
{
public:
    ComponentInstaller(const QString &destinationDirectory = ComponentInstaller::defaultInstallDir());
    ~ComponentInstaller();

    bool installComponentInSeparateDir() const override;
    void setInstallComponentInSeparateDir(bool separate) override;

    const QString &installDirectory() const override;
    void setInstallDirectory(const QString &destinationDirectory) override;

    void addExistedComponent(IComponent *component) override;

    QList<IComponent *> existedComponents() const override;

    DependenciesSolvingResult tryToInstall(const QStringList &componentNames) override;

    QStringList install() override;

    static QString defaultInstallDir();

protected:
    /*!
     * @details
     *   When overridden in derived classes discovers the components from the file system
     *   or web. The installed components must be from the discovered set.
     *
     *   The ComponentInstaller takes ownership for discovered components.
     */
    virtual QList<IComponent *> discoverComponents() = 0;

    /*!
     * @details
     *   When overridden in derived classes loads components if it is needed (e.g. from web)
     *   and returns collection of the component proxies, loaded from the ready to copy files.
     *
     *   The ComponentInstaller takes ownership for loaded components.
     */
    virtual QList<IComponent *> loadComponents(const QList<IComponent *> &componentsToInstall) = 0;

    /*!
     * @details
     *   Creates a default ComponentDependencies to solve component dependencies and install
     *   missing ones if it is needed.
     *
     *   The ComponentInstaller takes ownership for it.
     */
    virtual IComponentDependencies* createDependencies();

private:
    QString createComponentDirectory(const QString &componentName);
    void deleteComponents();

private:
    QString m_destinationDirectory;
    bool m_separateDirForComponent;
    QList<IComponent *> m_existedComponents;
    QList<IComponent *> m_componentsToInstall;
};

