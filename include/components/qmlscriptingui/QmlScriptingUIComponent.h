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
#include <components/qmlscriptingui/qmlscriptingui_global.h>

#include <carousel/componentsystem/BaseComponent.h>

/*!
 * @brief
 *   This class represents a component, that adds UI to the QmlScripting component.
 * @details
 *   The QmlScriptingUIComponent populates GUI with script console dockable widget
 *   and with simple script editor, which allows to create, save, load and run
 *   new scripts.
 *
 *   Registered dialogs:
 * @li ScriptCollectionDialog;
 *   Registered types:
 * @li ScriptCollectionModel;
 *
 * @sa QmlScriptingComponent
 */
class QML_SCRIPTING_UI_API QmlScriptingUIComponent : public BaseComponent
{
    Q_OBJECT
public:
    /*!
     * @details
     * @constructor{QmlScriptingUIComponent}.
     */
    QmlScriptingUIComponent(QObject *parent = nullptr);
    ~QmlScriptingUIComponent();

protected:
    /*!
     * @details
     *   Shuts down the component.
     */
    void onShutdown(IServiceLocator *serviceLocator) override;

    /*!
     * @details
     *   Registers ScriptCollectionDialog and ScriptCollectionModel in the @a serviceLocator.
     */
    bool onStartup(IServiceLocator *serviceLocator) override;
};

