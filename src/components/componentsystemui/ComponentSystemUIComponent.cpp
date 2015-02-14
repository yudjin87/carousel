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
#include "ComponentManagementInteractiveExtension.h"

#include <carousel/commands/IUndoStack.h>
#include <carousel/commands/EnableComponentCommand.h>
#include <carousel/commands/InstallComponentsCommand.h>
#include <carousel/componentsystem/ComponentExport.h>
#include <carousel/componentsystem/ComponentDependencies.h>
#include <carousel/componentsystem/IComponentManager.h>
#include <carousel/logging/LoggerFacade.h>
#include <carousel/utils/IServiceLocator.h>

#include <components/interactivity/IDialogService.h>

//------------------------------------------------------------------------------
namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("ComponentSystemUIComponent");
}

//------------------------------------------------------------------------------
static const QByteArray description(
        "");

//------------------------------------------------------------------------------
ComponentSystemUIComponent::ComponentSystemUIComponent(QObject *parent)
    : BaseComponent("org.carousel.ComponentSystemUI", parent)
{
    IInteractiveExtension *interactiveExtension = new ComponentManagementInteractiveExtension(this);
    registerExtension<IInteractiveExtension>(interactiveExtension);

    setShortName("Component System UI");
    setProductName("ComponentSystemUI");
    setDescription(description);
    setProvider("Carousel");
    setVersion(1, 0);
    addParent("org.carousel.Interactivity", 1, 0);
}

//------------------------------------------------------------------------------
ComponentSystemUIComponent::~ComponentSystemUIComponent()
{
    if (started())
        Log.w("Logic error: onShutdown() was not called.");
}

//------------------------------------------------------------------------------
void ComponentSystemUIComponent::onShutdown(IServiceLocator *serviceLocator)
{
    IDialogService *dialogService = serviceLocator->locate<IDialogService>();
    dialogService->unregisterDialogForModel<ComponentDefinitionsModel>();
}

// TODO: use templated "Finder", make common
template<typename TToCreate, typename TReq1, typename TReq2>
class Creator
{
public:
    Creator(IServiceLocator *serviceLocator)
        : m_serviceLocator(serviceLocator)
    {
    }

    void* operator()()
    {
        TReq1* req1 = m_serviceLocator->locate<TReq1>();
        TReq2* req2 = m_serviceLocator->locate<TReq2>();
        TToCreate* result = new TToCreate(req1, req2);
        return result;
    }

private:
    IServiceLocator *m_serviceLocator;
};

//------------------------------------------------------------------------------
bool ComponentSystemUIComponent::onStartup(IServiceLocator *serviceLocator)
{
    IComponentManager *manager = serviceLocator->locate<IComponentManager>();

    // Commands
    Creator<EnableComponentCommand, IUndoStack, IComponentManager> enableCreator{serviceLocator};
    serviceLocator->registerType<EnableComponentCommand>(enableCreator);

    Creator<InstallComponentsCommand, IUndoStack, IComponentManager> installCreator{serviceLocator};
    serviceLocator->registerType<InstallComponentsCommand>(installCreator);

    // Services
    IDialogService *dialogService = serviceLocator->locate<IDialogService>();
    dialogService->registerDialog<ComponentsDialog, ComponentDefinitionsModel>();

    auto componentDefinitionsModelCreator = [manager](){return new ComponentDefinitionsModel(manager->dependencies().components());};
    serviceLocator->registerType<ComponentDefinitionsModel>(componentDefinitionsModelCreator);

    return true;
}

//------------------------------------------------------------------------------
EXPORT_COMPONENT(ComponentSystemUIComponent)

//------------------------------------------------------------------------------

