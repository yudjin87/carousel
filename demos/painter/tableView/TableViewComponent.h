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

#ifndef TABLEVIEWCOMPONENT_H
#define TABLEVIEWCOMPONENT_H

#include "tableView_api.h"

#include <componentsystem/BaseComponent.h>

class TableViewComponent : public BaseComponent
{
    Q_OBJECT
public:
    TableViewComponent(QObject *parent = nullptr);
    ~TableViewComponent();

protected:
    bool _onStartup(QObject *ip_initData);
};

extern "C"
{
TABLEVIEW_API void *createInstance();
TABLEVIEW_API void disposeInstance(void *ip_componentObject);
}

#endif // TABLEVIEWCOMPONENT_H
