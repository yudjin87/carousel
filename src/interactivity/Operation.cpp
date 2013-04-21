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

#include "Operation.h"

//------------------------------------------------------------------------------
Operation::Operation(QActionGroup *ip_actionGroup /*= nullptr*/)
    : QAction(ip_actionGroup)
    , m_category("")
    , m_name("")
{
    _connectToSignals();
}

//------------------------------------------------------------------------------
Operation::Operation(const QString &i_text, QActionGroup *ip_actionGroup /*= nullptr*/)
    : QAction(i_text, ip_actionGroup)
    , m_category("")
    , m_name("")
{
    _connectToSignals();
}

//------------------------------------------------------------------------------
Operation::Operation(const QIcon &i_icon, const QString &i_text, QActionGroup *ip_actionGroup /*= nullptr*/)
    : QAction(i_icon, i_text, ip_actionGroup)
    , m_category("")
    , m_name("")
{
    _connectToSignals();
}

//------------------------------------------------------------------------------
Operation::~Operation()
{
}

//------------------------------------------------------------------------------
QString Operation::category() const
{
    return m_category;
}

//------------------------------------------------------------------------------
void Operation::stopExecuting()
{
    emit executingStopped();
}

//------------------------------------------------------------------------------
void Operation::initialize(QObject * /*ip_startUpData*/)
{
    //Does nothing by default.
}

//------------------------------------------------------------------------------
QString Operation::name() const
{
    return m_name;
}

//------------------------------------------------------------------------------
void Operation::setCategory(const QString &i_category)
{
    m_category = i_category;
}

//------------------------------------------------------------------------------
void Operation::setName(const QString &i_name)
{
    m_name = i_name;
}

//------------------------------------------------------------------------------
void Operation::_onTriggered(bool /*i_checked*/)
{
    if (isCheckable())
        return;

    execute();
}

//------------------------------------------------------------------------------
void Operation::_onToggled(bool i_checked)
{
    if (i_checked)
        execute();
    else
        stopExecuting();
}

//------------------------------------------------------------------------------
void Operation::_connectToSignals()
{
    connect(this, SIGNAL(triggered(bool)),
            this, SLOT(_onTriggered(bool)));

    connect(this, SIGNAL(toggled(bool)),
            this, SLOT(_onToggled(bool)));
}

//------------------------------------------------------------------------------