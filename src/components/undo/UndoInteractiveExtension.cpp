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

#include "UndoInteractiveExtension.h"
#include "RedoOperation.h"
#include "UndoOperation.h"

#include <components/interactivity/ICatalogs.h>
#include <components/interactivity/IOperationCatalog.h>
#include <components/interactivity/IMenuCatalog.h>
#include <components/interactivity/IToolBarCatalog.h>
#include <carousel/utils/IServiceLocator.h>

#include <QtWidgets/QMenu>
#include <QtWidgets/QToolBar>

UndoInteractiveExtension::UndoInteractiveExtension(QObject *parent /*= nullptr*/)
    : QObject(parent)
{
}

void UndoInteractiveExtension::configureGui(ICatalogs &inCatalogs, IServiceLocator *serviceLocator)
{
    Q_UNUSED(serviceLocator)

    IOperationCatalog &operationCatalog = inCatalogs.operationCatalog();
    Operation *undo = operationCatalog.add(new UndoOperation());
    Operation *redo = operationCatalog.add(new RedoOperation());

    IToolBarCatalog &toolbarCatalog = inCatalogs.toolBarCatalog();
    QToolBar *toolBar = toolbarCatalog.add("Edit");
    toolBar->addAction(undo);
    toolBar->addAction(redo);


    IMenuCatalog &menuCatalog = inCatalogs.menuCatalog();
    QMenu *menu = menuCatalog.addMenu("Edit");
    menu->addAction(undo);
    menu->addAction(redo);
}



