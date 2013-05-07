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

#include "ToolBase.h"

#include "IInteractionService.h"

#include <framework/AbstractApplication.h>
#include <utils/IServiceLocator.h>

#include <assert.h>
//------------------------------------------------------------------------------
ToolBase::ToolBase(QActionGroup *actionGroup)
    : Operation(actionGroup)
    , m_app(nullptr)
    , m_interactionService(nullptr)
{
    setCheckable(true);
}

//------------------------------------------------------------------------------
ToolBase::ToolBase(const QString &i_text, QActionGroup *actionGroup)
    : Operation(i_text, actionGroup)
    , m_app(nullptr)
    , m_interactionService(nullptr)
{
    setCheckable(true);
}

//------------------------------------------------------------------------------
ToolBase::ToolBase(const QIcon &i_icon, const QString &i_text, QActionGroup *actionGroup)
    : Operation(i_icon, i_text, actionGroup)
    , m_app(nullptr)
    , m_interactionService(nullptr)
{
    setCheckable(true);
}

//------------------------------------------------------------------------------
ToolBase::~ToolBase()
{
    m_app = nullptr;
    m_interactionService = nullptr;
}

//------------------------------------------------------------------------------
void ToolBase::execute()
{
    m_interactionService->setActiveTool(this);
}

//------------------------------------------------------------------------------
void ToolBase::stopExecuting()
{
    Operation::stopExecuting();
}

//------------------------------------------------------------------------------
void ToolBase::initialize(QObject *startUpData)
{
    m_app = dynamic_cast<AbstractApplication *>(startUpData);
    assert(m_app != nullptr);

    m_interactionService = m_app->serviceLocator().locate<IInteractionService>();
    assert(m_interactionService != nullptr);
}

//------------------------------------------------------------------------------
bool ToolBase::onContextMenu(QContextMenuEvent * /*event*/)
{
    return false;
}

//------------------------------------------------------------------------------
void ToolBase::onDoubleClick(QMouseEvent * /*event*/)
{
}

//------------------------------------------------------------------------------
void ToolBase::onKeyDown(QKeyEvent * /*event*/)
{
}

//------------------------------------------------------------------------------
void ToolBase::onKeyUp(QKeyEvent * /*event*/)
{
}

//------------------------------------------------------------------------------
void ToolBase::onMouseDown(QMouseEvent * /*event*/)
{
}

//------------------------------------------------------------------------------
void ToolBase::onMouseMove(QMouseEvent * /*event*/)
{
}

//------------------------------------------------------------------------------
void ToolBase::onMouseUp(QMouseEvent * /*event*/)
{
}

//------------------------------------------------------------------------------
