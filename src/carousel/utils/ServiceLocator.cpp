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

#include "utils/ServiceLocator.h"
#include "utils/TypeObjectsMap.h"

#include <QtCore/QStringList>

#include <carousel/logging/LoggerFacade.h>
#include <algorithm>

namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("ServiceLocator");
}

ServiceLocator::ServiceLocator()
    : m_objects(new TypeObjectsMap<void *>())
    , m_creators(new TypeObjectsMap<factoryMethod>())
{
}

ServiceLocator::~ServiceLocator()
{
    delete m_objects;
    m_objects = nullptr;

    delete m_creators;
    m_creators = nullptr;
}

QObject *ServiceLocator::buildObject(const QString &className)
{
    return buildObject(className, "");
}

QObject *ServiceLocator::buildObject(const QString &className, const QString &tag)
{
    bool success = false;
    const factoryMethod &creator = m_creators->getInstance(className, tag, &success);
    if (!success)
    {
        Log.e(QString("Failed to build %1 instance - creator wasn't registered").arg(className));
        return nullptr;
    }

    void *data = creator();
    QObject *object = reinterpret_cast<QObject *>(data);
    return object;
}

QObject *ServiceLocator::locateToObject(const QString &className)
{
    return locateToObject(className, "");
}

QObject *ServiceLocator::locateToObject(const QString &className, const QString &tag)
{
    void *foundInstance = getService(className, tag);
    QObject *service = reinterpret_cast<QObject *>(foundInstance);
    return service;
}

QStringList ServiceLocator::services() const
{
    return services("");
}

QStringList ServiceLocator::services(const QString &tag) const
{
    return m_objects->keys(tag);
}

void ServiceLocator::registerTypeImpl(const QString &className, factoryMethod method, const QString &tag)
{
    if (tag.isEmpty())
        Log.i(QString("Registering factory method for %1").arg(className));
    else
        Log.i(QString("Registering factory method for %1 with tag %2").arg(className).arg(tag));

    m_creators->registerInstance(method, className, tag);
}

void *ServiceLocator::unregisterInstanceImpl(const QString &className, const QString &tag)
{
    void *foundInstance = m_objects->unregisterInstance(className, tag);
    return foundInstance;
}

void *ServiceLocator::buildInstanceImpl(const QString &className, const QString &tag)
{
    bool success = false;
    const factoryMethod &creator = m_creators->getInstance(className, tag, &success);
    if (!success)
    {
        Log.e(QString("Failed to build %1 instance - creator wasn't registered").arg(className));
        return nullptr;
    }

    void *data = creator();
    return data;
}

void *ServiceLocator::getService(const QString &className, const QString &tag)
{
    bool success = false;
    void *tmp = m_objects->getInstance(className, tag, &success);
    if (!success)
    {
        Log.e(QString("Failed to find registered service %1").arg(className));
        return nullptr;
    }

    return tmp;
}

void ServiceLocator::registerInstanceImpl(void *instance, const QString &className, const QString &tag)
{
    if (tag.isEmpty())
        Log.i(QString("Registering %1 instance").arg(className));
    else
        Log.i(QString("Registering %1 instance with tag %2").arg(className).arg(tag));

    m_objects->registerInstance(instance, className, tag);
}

