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

#include "componentsystem/BaseComponent.h"
#include "componentsystem/ComponentDefinition.h"
#include "componentsystem/ParentDefinition.h"

#include "logging/LoggerFacade.h"
#include "utils/TypeObjectsMap.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QSettings>

namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("BaseComponent");
}

static int IComponentMetatypeId = qRegisterMetaType<IComponent*>("IComponent*");
static int IComponentListMetatypeId = qRegisterMetaType<QList<IComponent*>>("QList<IComponent*>");
static int IComponentAvailabilityId = qRegisterMetaType<IComponent::Availability>("IComponent::Availability");
static int IComponentStateId = qRegisterMetaType<IComponent::State>("IComponent::State");

QStringList toStringList(const QList<IComponent *> &components)
{
    QStringList names;
    for (IComponent *comp : components)
        names.push_back(comp->name());

    return names;
}

BaseComponent::BaseComponent(const QString &name, QObject *parent)
    : m_definition(new ComponentDefinition(name, true))
    , m_availability(IComponent::Enabled)
    , m_state(IComponent::Initialized)
    , m_typeObjectsMap(new TypeObjectsMap<void *>())
{
    setParent(parent);
    setObjectName(m_definition->componentName());
    loadAvailability();
    m_definition->setComponent(this);
}

BaseComponent::BaseComponent(ComponentDefinition *definition, QObject *parent)
    : m_definition(definition)
    , m_availability(IComponent::Enabled)
    , m_state(IComponent::Initialized)
    , m_typeObjectsMap(new TypeObjectsMap<void *>())
{
    setParent(parent);
    setObjectName(m_definition->componentName());
    loadAvailability();
    m_definition->setComponent(this);
}

void *BaseComponent::getExtension(const QString &byTypeId) const
{
    bool success = false;
    void* tmp = m_typeObjectsMap->getInstance(byTypeId, &success);
    if (success)
        return tmp;

    return nullptr;
}

bool BaseComponent::isCompatible(const IComponent *withOther) const
{
    // TODO: log incompatibles
    return m_definition->isCompatible(withOther) && withOther->definition()->isCompatible(this);
}

BaseComponent::~BaseComponent()
{
    saveAvailability();

    delete m_typeObjectsMap;
    m_typeObjectsMap = nullptr;

    delete m_definition;
    m_definition = nullptr;
}

IComponent::Availability BaseComponent::availability() const
{
    return m_availability;
}

IComponent::State BaseComponent::state() const
{
    return m_state;
}

const ComponentDefinition *BaseComponent::definition() const
{
    return m_definition;
}

const QString &BaseComponent::name() const
{
    return m_definition->componentName();
}

bool BaseComponent::started() const
{
    return state() == IComponent::Running;
}

void BaseComponent::shutdown(IServiceLocator *serviceLocator)
{
    if (!started()) {
        Log.w(QString("Component \"%1\" is being shut down, but it was not started up.").arg(name()));
        return;
    }

    onShutdown(serviceLocator);
}

bool BaseComponent::startup(IServiceLocator *serviceLocator)
{
    if (started()) {
        Log.w(QString("Component \"%1\" is being started up, but it was not shut down.").arg(name()));
        return true;
    }

    m_definition->setArguments(QCoreApplication::arguments());
    return onStartup(serviceLocator);
}

void BaseComponent::onShutdown(IServiceLocator *serviceLocator)
{
    Q_UNUSED(serviceLocator)
    // nothing to do in the base implementation
}

bool BaseComponent::onStartup(IServiceLocator *)
{
    // nothing to do in the base implementation
    return true;
}

void BaseComponent::addParent(const QString &parentName, int major_version, int minor_version, int build_version, int revision_version)
{
    // TODO: replace major_version to the majorVersion, etc
    m_definition->addParent(new ParentDefinition(parentName, major_version, minor_version, build_version, revision_version));
}

void BaseComponent::loadAvailability()
{
    QSettings settings;
    QVariant value = settings.value(QString("components_availability/%1").arg(name()));
    if (value.isValid())
        setAvailability(static_cast<Availability>(value.toInt()));
}

void BaseComponent::saveAvailability()
{
    QSettings settings;
    settings.setValue(QString("components_availability/%1").arg(name()), static_cast<int>(availability()));
    settings.sync();
}

void BaseComponent::setAvailability(IComponent::Availability newMode)
{
    if (m_availability == newMode)
        return;

    m_availability = newMode;
    onAvailabilityChanged(newMode);
}

void BaseComponent::setState(IComponent::State newState)
{
    m_state = newState;
}

void BaseComponent::setDescription(const QString &description)
{
    m_definition->setDescription(description);
}

void BaseComponent::setError(const QString &error)
{
    m_definition->setError(error);
}

void BaseComponent::setShortName(const QString &name)
{
    m_definition->setShortComponentName(name);
}

void BaseComponent::setProductName(const QString &productName)
{
    m_definition->setProductName(productName);
}

void BaseComponent::setProvider(const QString &provider)
{
    m_definition->setProvider(provider);
}

void BaseComponent::setVersion(int major_version, int minor_version, int build_version, int revision_version)
{
    m_definition->setVersion(major_version, minor_version, build_version, revision_version);
}

void BaseComponent::onAvailabilityChanged(Availability newMode)
{
    emit availabilityChanged(newMode);
}

void BaseComponent::registerExtensionInstance(void *instance, const QString &forTypeId)
{
    m_typeObjectsMap->registerInstance(instance, forTypeId);
}

