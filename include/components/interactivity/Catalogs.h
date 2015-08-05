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
#include "ICatalogs.h"

class IServiceLocator;
class DockWidgetCatalog;
class MenuCatalog;
class OperationCatalog;
class ToolBarCatalog;

class QMainWindow;

/*!
 * @brief
 *   This class provides methods to get catalogs that contain interactive components.
 * @details
 *   Usually you do not use this class directly, so use IInteractionService::catalogs()
 *   to get a reference to ICatalogs.
 */
class INTERACTIVITY_API Catalogs : public ICatalogs
{
public:
    /*!
     * @details
     * @constructor{Catalogs} with main window.
     *   This main window will be used for ToolBarCatalog creation and
     *   for the MenuCatalog creation. Note, that MenuCatalog requires
     *   that QMenuBar has been added to the specified QMainWindow.
     */
    Catalogs(QMainWindow &shell, IServiceLocator *serviceLocator);
    ~Catalogs();

    /*!
     * @details
     *   Gets the operation catalog.
     */
    IOperationCatalog &operationCatalog() override;

    /*!
     * @details
     *   Gets the immutable operation catalog.
     */
    const IOperationCatalog &operationCatalog() const override;

    /*!
     * @details
     *   Gets the dockable widget catalog.
     */
    IDockWidgetCatalog &dockWidgetCatalog() override;

    /*!
     * @details
     *   Gets the immutable dockable widget catalog.
     */
    const IDockWidgetCatalog &dockWidgetCatalog() const override;

    /*!
     * @details
     *   Gets the menu catalog.
     */
    IMenuCatalog &menuCatalog() override;

    /*!
     * @details
     *   Gets the immutable menu catalog.
     */
    const IMenuCatalog &menuCatalog() const override;

    /*!
     * @details
     *   Gets the toolbar catalog.
     */
    IToolBarCatalog &toolBarCatalog() override;

    /*!
     * @details
     *   Gets the immutable toolbar catalog.
     */
    const IToolBarCatalog &toolBarCatalog() const override;

private:
    OperationCatalog *m_operationCatalog;
    DockWidgetCatalog *m_dockWidgetCatalog;
    MenuCatalog *m_menuCatalog;
    ToolBarCatalog *m_toolBarCatalog;
};

