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

#include "CartoUIComponent.h"
#include "CartoUIInteractiveExtension.h"
#include "MapModel.h"

#include <componentsystem/ComponentDefinition.h>
#include <componentsystem/ComponentExport.h>
#include <dom/IPainterDocument.h>
#include <dom/IPainterDocumentController.h>
#include <framework/AbstractApplication.h>
#include <utils/IServiceLocator.h>

#include <QtGui/QGraphicsScene>

//------------------------------------------------------------------------------
CartoUIComponent::CartoUIComponent(QObject *parent /*= nullptr*/)
    : BaseComponent("ShapesView", parent)
{
    IInteractiveExtension *interactiveExtension = new CartoUIInteractiveExtension(this);
    registerExtension<IInteractiveExtension>(interactiveExtension);

    addParent("Dom");
    addParent("Geodatabase");
    addParent("Display");
    addParent("Carto");
}

//------------------------------------------------------------------------------
CartoUIComponent::~CartoUIComponent()
{
}

//------------------------------------------------------------------------------
bool CartoUIComponent::_onStartup(QObject *ip_initData)
{
    AbstractApplication *app = qobject_cast<AbstractApplication *>(ip_initData);
    if (app == nullptr)
        return false;

    IPainterDocumentController* docController = app->serviceLocator().locate<IPainterDocumentController>();
    IPainterDocument *doc = docController->document();

    QGraphicsScene *scene = app->serviceLocator().locate<QGraphicsScene>();
    MapModel *map = new MapModel(&doc->map(), scene, this);
    Q_UNUSED(map);
    return true;
}

//------------------------------------------------------------------------------
void CartoUIComponent::_onShutdown()
{
}

//------------------------------------------------------------------------------
EXPORT_COMPONENT(CartoUIComponent)

//------------------------------------------------------------------------------

