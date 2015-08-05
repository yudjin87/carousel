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
#include "Operation.h"
#include "ITool.h"

class IInteractionService;

/*!
 * @brief
 *   The ToolBase class overrides all ITool methods
 *   with empty implementation for further convenience of inheritance.
 * @details
 *   You can derive your tools for the components from this
 *   class, if you don't want to override all members. The ToolBase class
 *   also set QAction::checkable() property to the @a true.
 */
class INTERACTIVITY_API ToolBase : public Operation, public ITool
{
public:
    /*!
     * @details
     * @constructor{ToolBase} with action group, if any.
     *   If the action group not null, this tool
     *   will be automatically inserted into the group.
     */
    ToolBase(QActionGroup *actionGroup = nullptr);

    /*!
     * @details
     *   Constructs a tool with action group, if any.
     *   If the action group not null, this tool
     *   will be automatically inserted into the group.
     *
     *   The ToolBase uses a stripped version of @a text (e.g. "&Menu Option..." becomes
     *   "Menu Option") as descriptive text for tool buttons. You can override
     *   this by setting a specific description with setText(). The same text will be
     *   used for tooltips unless you specify a different text using setToolTip().
     */
    ToolBase(const QString &text, QActionGroup *actionGroup = nullptr);

    /*!
     * @details
     *   Constructs a tool with action group, if any.
     *   If the action group not null, this tool
     *   will be automatically inserted into the group.
     *
     *   The ToolBase uses a stripped version of @a text (e.g. "&Menu Option..." becomes
     *   "Menu Option") as descriptive text for tool buttons. You can override
     *   this by setting a specific description with setText(). The same text will be
     *   used for tooltips unless you specify a different text using setToolTip().
     */
    ToolBase(const QIcon &icon, const QString &text, QActionGroup *actionGroup = nullptr);
    ~ToolBase();

    /*!
     * @details
     *   Called when this tool is activated by user (button/menu is clicked,
     *   or shortkey pressed).
     *
     *   The ToolBase sets itself to the IInteractionService as the active tool
     *   when this method is invoked.
     *
     *   Write the code that performs the action when the tool is clicked in this method.
     * @note Do not forget to call parent method ToolBase::execute();
     */
    void execute() override;

    /*!
     * @details
     *   Occurs when user switch off this operation explicitly or implicitly (by selecting
     *   other tool).
     *
     *   Does nothing by default, just calls parent one.
     */
    void stopExecuting() override;

    /*!
     * @details
     *   Called by carousel interactivity system to gives the operation a hook into
     *   the application.
     *   When subclassing ToolBase, use the initialize() method to get a hook to the
     *   application.
     */
    void initialize(IServiceLocator *serviceLocator) override;

    /*!
     * @details
     *   Context menu event occured at the given in @a event location.
     *
     *   When impting Ito create a custom tool, write code to display a
     *   custom context menu the right mouse button is pressed when this tool
     *   is the active too   *
     *   If your tool displays a custom context menu, it should let the application
     *   know that it handled the onContextMenu event by returning true. If you
     *   don't do this, the standard context menu will be displayed.
     */
    bool onContextMenu(QContextMenuEvent *event) override;

    /*!
     * @details
     *   Occurs when a mouse button is double clicked when this tool is active.
     */
    bool onDoubleClick(QMouseEvent *event) override;

    /*!
     * @details
     *   Occurs when a key on the keyboard is pressed when this tool is active.
     */
    bool onKeyDown(QKeyEvent *event) override;

    /*!
     * @details
     *   Occurs when a key on the keyboard is released when this tool is active.
     */
    bool onKeyUp(QKeyEvent *event) override;

    /*!
     * @details
     *   Occurs when a mouse button is pressed when this tool is active.
     */
    bool onMouseDown(QMouseEvent *event) override;

    /*!
     * @details
     *   Occurs when the mouse is moved when this tool is active.
     */
    bool onMouseMove(QMouseEvent *event) override;

    /*!
     * @details
     *   Occurs when a mouse button is released when this tool is active.
     */
    bool onMouseUp(QMouseEvent *event) override;

private:
    IServiceLocator *m_serviceLocator;
    IInteractionService *m_interactionService;
};

