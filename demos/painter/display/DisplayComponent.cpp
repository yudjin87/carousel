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

#include "DisplayComponent.h"

#include <componentsystem/ComponentDefinition.h>
#include <componentsystem/ComponentExport.h>
#include <interactivity/IInteractionService.h>
#include <interactivity/InputInterceptor.h>
#include <utils/IServiceLocator.h>

#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsView>
#include <QtGui/QMainWindow>

//------------------------------------------------------------------------------
static const QByteArray productName("Display");

//------------------------------------------------------------------------------
DisplayComponent::DisplayComponent(QObject *parent)
    : BaseComponent("Display", parent)
{
    addParent("Interactivity");
    setProductName(productName);
    setProvider("Carousel");
}

//------------------------------------------------------------------------------
DisplayComponent::~DisplayComponent()
{
}

//------------------------------------------------------------------------------
void DisplayComponent::onShutdown()
{
    QGraphicsScene *scene = m_serviceLocator->unregisterInstance<QGraphicsScene>();
    QGraphicsView *view = scene->views().first();

    delete scene;
    delete view;

    IInteractionService* interactionService = m_serviceLocator->locate<IInteractionService>();
    interactionService->setInputInterceptor(nullptr);
}

//------------------------------------------------------------------------------
bool DisplayComponent::onStartup(IServiceLocator *serviceLocator)
{
    m_serviceLocator = serviceLocator;
    if (m_serviceLocator == nullptr)
        return false;

    QGraphicsScene *scene = new QGraphicsScene();
    QGraphicsView *view = new QGraphicsView(scene);
    view->scale(50000, 50000);

    QMainWindow *mainWindow = m_serviceLocator->locate<QMainWindow>();
    mainWindow->setCentralWidget(view);

    m_serviceLocator->registerInstance<QGraphicsScene>(scene);

    IInteractionService* interactionService = m_serviceLocator->locate<IInteractionService>();
    interactionService->setInputInterceptor(new InputInterceptor());
    interactionService->inputInterceptor()->setSender(view->viewport());
    interactionService->inputInterceptor()->activate();

    return true;
}

//------------------------------------------------------------------------------
EXPORT_COMPONENT(DisplayComponent)

//------------------------------------------------------------------------------
