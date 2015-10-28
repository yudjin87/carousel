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

#include "components/qmlscripting/CarouselScriptEngineConfigurationDelegate.h"
#include "components/qmlscripting/IOutputHandler.h"
#include "components/qmlscripting/IScriptExtension.h"
#include "components/qmlscripting/IScriptConsole.h"
#include "components/qmlscripting/IScriptCollection.h"
#include "components/qmlscripting/IScriptUnit.h"
#include "components/qmlscripting/ServiceLocatorWrapper.h"
#include "components/qmlscripting/ConsoleJsObject.h"
#include "components/qmlscripting/QmlComponentManager.h"

#include <carousel/componentsystem/IComponent.h>
#include <carousel/logging/LoggerFacade.h>

#include <QtCore/QCoreApplication>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QEventLoop>
#include <QtCore/QPoint>
#include <QtCore/QTimer>
#include <QtCore/QList>
#include <QtQml/QtQml>
#include <QtQml/QJSEngine>
#include <QtQml/QJSValueIterator>

namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("...ScriptConfigurationDelegate");

static const QList<QString> qobjectProperties = {
    "objectName",
    "destroyed(QObject*)",
    "destroyed()",
    "deleteLater()",
    "objectNameChanged(QString)"
    };

} // namespace

CarouselScriptEngineConfigurationDelegate::CarouselScriptEngineConfigurationDelegate(IServiceLocator *locator, QObject *parent)
    : IScriptEngineConfigurationDelegate()
    , m_locator(locator)
{
    setParent(parent);

    qmlRegisterInterface<IComponent>("IComponent");

    qmlRegisterInterface<IScriptConsole>("IScriptConsole");
    qmlRegisterInterface<IScriptCollection>("IScriptCollection");
    qmlRegisterInterface<IScriptUnit>("IScriptUnit");
}

void CarouselScriptEngineConfigurationDelegate::configureFromComponent(IComponent *component, QJSEngine *engine)
{
    // TODO: move it to the generic delegate (see CarouselComponentConfigurationDelegate)
    if (!component->started()) {
        Log.d(QString("Component \"%1\" does not started. Skip it.").arg(component->name()));
        return;
    }

    IScriptExtension *scriptExtension = component->extension<IScriptExtension>();
    if (scriptExtension == nullptr) {
        Log.d(QString("Component \"%1\" does not have script extension for configuring. Skip it.").arg(component->name()));
        return;
    }

    configureExtension(m_locator, engine, scriptExtension);
}

void CarouselScriptEngineConfigurationDelegate::configureDefaults(QJSEngine *engine, IOutputHandler *output)
{
    configureServiceLocator(engine, m_locator);
    registerConsole(engine, output);
}

void CarouselScriptEngineConfigurationDelegate::configureExtension(IServiceLocator *locator, QJSEngine *engine, IScriptExtension *extension)
{
    extension->configureEngine(locator, engine);
}

void CarouselScriptEngineConfigurationDelegate::configureServiceLocator(QJSEngine *engine, IServiceLocator *locator)
{
    ServiceLocatorWrapper *wrapper = new ServiceLocatorWrapper(locator); // engine takes ownership: JavaScriptOwnership
    const QJSValue jsLocatorWrapper = engine->newQObject(wrapper);
    if (jsLocatorWrapper.isError())
    {
        Log.w(QString("Can't register service locator: %1").arg(jsLocatorWrapper.toString()));
        return;
    }

    engine->globalObject().setProperty("serviceLocator", jsLocatorWrapper);

    QmlComponentManager* manager = new QmlComponentManager(*locator);
    const QJSValue jsManagerWrapper = engine->newQObject(manager);
    if (jsManagerWrapper.isError())
    {
        Log.w(QString("Can't register component manager: %1").arg(jsManagerWrapper.toString()));
        return;
    }

    engine->globalObject().setProperty("componentManager", jsManagerWrapper);
}

void CarouselScriptEngineConfigurationDelegate::registerConsole(QJSEngine *engine, IOutputHandler *output)
{
    ConsoleJsObject* console = new ConsoleJsObject(*output);
    QJSValue jsConsole = engine->newQObject(console);
    if (jsConsole.isError())
    {
        Log.w(QString("Can't register console: %1").arg(jsConsole.toString()));
        return;
    }

    engine->globalObject().setProperty("console", jsConsole);
}

QJSValue CarouselScriptEngineConfigurationDelegate::findValue(QJSEngine *engine, const QString& name)
{
    QJSValueIterator it(engine->globalObject());
    while (it.hasNext()) {
        it.next();
        if (it.name() == name)
            return it.value();
    }

    return QJSValue();
}

