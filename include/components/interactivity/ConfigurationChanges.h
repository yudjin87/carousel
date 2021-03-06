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
#include "interactivity_global.h"

#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QObject>

class Operation;
class QAction;
class QDockWidget;
class QMenu;
class QToolBar;
class QWidget;

/*!
 * @brief
 *   This class is describes possible GUI changes during configuration
 *   by custom component.
 * @details
 *   When you extend application by IInteractiveExtension, Carousel
 *   framework offers you to extend user interface also (insert items
 *   to the menus, toolbars, etc). The IComponentConfigurationDelegate
 *   class is responsible for it, and after your customization it stores
 *   so-called configuration changes assosiated with specified component.
 *
 *   Note, that ConfigurationChanges class does not take ownership of the
 *   inserted items.
 */
class INTERACTIVITY_API ConfigurationChanges : public QObject
{
    Q_OBJECT
public:
    typedef QList<Operation *> Operations;
    typedef QList<QDockWidget *> DockWidgets;
    typedef QList<QMenu *> Menus;
    typedef QList<QToolBar *> ToolBars;

public:
    /*!
     * @details
     * @constructor{ConfigurationChanges} with empty changes.
     */
    ConfigurationChanges();
    ~ConfigurationChanges();

    /*!
     * @details
     *   Gets the operations added during component's configuration.
     */
    const Operations &addedOperations() const;

    /*!
     * @details
     *   Gets a dockable widgets added during component's
     *   configuration.
     */
    const DockWidgets &addedDockWidgets() const;

    /*!
     * @details
     *   Gets the menus added to the menu bar
     *   during component's configuration.
     */
    const Menus &addedMenus() const;

    /*!
     * @details
     *   Gets the menus remoevd from the menu bar
     *   during component's configuration.
     */
    const Menus &removedMenus() const;

    /*!
     * @details
     *   Gets the toolbars added during component's configuration.
     */
    const ToolBars &addedToolbars() const;

    /*!
     * @details
     *   Gets the operations added to the specific containers (parents)
     *   during component's configuration.
     */
    const Operations &insertedOperations() const;

public slots:
    /*!
     * @details
     *   Inserts a operation added during component's configuration.
     */
    void insertAddedOperation(Operation *operation);

    /*!
     * @details
     *   Inserts a dockable widget added during component's
     *   configuration.
     */
    void insertAddedDockWidget(QDockWidget *dockWidget);

    /*!
     * @details
     *   Inserts a menu added to the menu bar
     *   during component's configuration.
     */
    void insertAddedMenu(QMenu *menu);

    /*!
     * @details
     *   Inserts a toolbar added during component's configuration.
     */
    void insertAddedToolbar(QToolBar *toolbar);

    /*!
     * @details
     *   Inserts a operation added to the specific container
     *   (parent widget) during component's configuration.
     */
    void insertInsertedOperation(Operation *operation);

    /*!
     * @details
     *   Inserts a menu removed from the menu bar
     *   during component's configuration.
     */
    void insertRemovedMenu(QMenu *menu);

private:
    Operations m_insertedOperations;
    Operations m_addedOperations;
    DockWidgets m_addedDockWidgets;
    Menus m_addedMenus;
    Menus m_removedMenus;
    ToolBars m_addedToolbars;
};

