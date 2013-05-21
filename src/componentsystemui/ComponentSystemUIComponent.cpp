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

#include "ComponentSystemUIComponent.h"
#include "ComponentDefinitionsModel.h"
#include "ComponentsDialog.h"

#include "EnableComponentCommand.h"
#include "InstallComponentsCommand.h"

#include <componentsystem/ComponentExport.h>
#include <componentsystem/ComponentDependencies.h>
#include <componentsystem/IComponentManager.h>
#include <interactivity/IDialogService.h>
#include <framework/AbstractApplication.h>
#include <logging/LoggerFacade.h>
#include <utils/IServiceLocator.h>

//------------------------------------------------------------------------------
namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("ComponentSystemUIComponent");
}

//------------------------------------------------------------------------------
// TODO: will be removed when c++11 is supported (with lambdas)
static void *createComponentDefinitionsModel(IComponentManager *manager)
{
    return new ComponentDefinitionsModel(manager->dependencies().components());
}

static void *createEnableComponentCommand(IComponentManager *manager)
{
    return new EnableComponentCommand(manager);
}

static void *createInstallComponentsCommand(IComponentManager *manager)
{
    return new InstallComponentsCommand(manager);
}

//------------------------------------------------------------------------------
static const QByteArray description(
        "");

//------------------------------------------------------------------------------
ComponentSystemUIComponent::ComponentSystemUIComponent(QObject *parent)
    : BaseComponent("ComponentSystemUI", parent)
{
    setProductName("ComponentSystemUI");
    setDescription(description);
    setProvider("Carousel");
    addParent("Interactivity");
}

//------------------------------------------------------------------------------
ComponentSystemUIComponent::~ComponentSystemUIComponent()
{
    if (started())
        Log.w("Logic error: onShutdown() was not called.");
}

//------------------------------------------------------------------------------
void ComponentSystemUIComponent::onShutdown()
{
    // TODO:
    // Unregister dialogs!
}

//------------------------------------------------------------------------------
bool ComponentSystemUIComponent::onStartup(QObject *initData)
{
    if (initData == nullptr)
        return false;

    AbstractApplication *app = dynamic_cast<AbstractApplication *>(initData);
    if (app == nullptr)
        return false;

    IServiceLocator &locator = app->serviceLocator();
    IComponentManager *manager = locator.locate<IComponentManager>();

    // Commands
    auto enableCreator = std::bind(&createEnableComponentCommand, manager);
    locator.registerType<EnableComponentCommand>(enableCreator);

    auto installCreator = std::bind(&createInstallComponentsCommand, manager);
    locator.registerType<InstallComponentsCommand>(installCreator);

    // Services
    IDialogService *dialogService = locator.locate<IDialogService>();
    dialogService->registerDialog<ComponentsDialog, ComponentDefinitionsModel>();

    auto componentDefinitionsModelCreator = std::bind(&createComponentDefinitionsModel, manager);
    locator.registerType<ComponentDefinitionsModel>(componentDefinitionsModelCreator);

    return true;
}

//------------------------------------------------------------------------------
EXPORT_COMPONENT(ComponentSystemUIComponent)

//------------------------------------------------------------------------------

