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

#ifndef IDIALOGSERVICE_H
#define IDIALOGSERVICE_H

#include "interactivity_global.h"

#include <QtCore/QString>
#include <typeinfo>

class QWidget;
struct IDialogConstructor;

/*!
 * @brief
 *   Defines methods for showing the dialogs.
 * @details
 *   Use IDialogService to show dialogs instead of explicitly creating dialogs
 *   in code to be able to fake dialogs (and returning results), e.g. for unit testing.
 *
 *   It is registered into the application services by the InteractionServiceComponent.
 */
class INTERACTIVITY_API IDialogService
{
public:
    IDialogService(){}
    virtual ~IDialogService(){}

    /*!
     * @details
     *   Registers the @a TDialog type, that expects a @a TDialogModel pointer
     *   in the constructor. This dialog will be shown from the showDialog() method.
     * @param TDialog the type of dialog.
     * @param TDialogModel the type of dialog model.
     * @note the @a TDialog should take ownership of the @a TDialogModel.
     */
    template<typename TDialog, typename TDialogModel>
    void registerDialog();

    /*!
     * @details
     *   Creates new instance of the dialog (if any was registered for
     *   the @a TDialogModel), opens a modal dialog and returns @a true
     *   if user accept it, otherwise @a false. Also returns @a false,
     *   if dialog was not registered for the @a TDialogModel.
     * @param TDialogModel the type of dialog model.
     */
    template<typename TDialogModel>
    bool showDialog(TDialogModel *ip_dlgModel) const;

protected:
    /*!
     * @details
     *   When overriden registers the specified dialog constructor with the
     *   model type name for the creating dialog by demand (by the passed
     *   model type name).
     *
     *   This method is invoked from the template registerDialog() method,
     *   which gets model type name from the template model, and specializes
     *   dialog constructor with specified dialog and model types.
     * @sa showDialog(), registerDialog()
     */
    virtual void registerConstructor(const QString &i_dlgModelType, IDialogConstructor *ip_constructor) = 0;

    /*!
     * @details
     *   When overriden creates a new instance of the registered dialog with
     *   specified model, shows it and returns closing code.
     *   If dialog was not registered for this model type,
     *   returns @a false.
     * @sa showDialog()
     */
    virtual bool showDialogForModel(const QString &i_forDlgModelType, void *ip_dlgModel) const = 0;
};

//------------------------------------------------------------------------------
/*!
 * @brief
 *   Common interface for the dialog factory.
 */
struct IDialogConstructor
{
    virtual ~IDialogConstructor(){}
    /*!
     * @details
     *   Returns new instance of the dialog,
     *   and initializes it with parent window (for the default location)
     *   and ip_dlgModel.
     */
    virtual void *create(void *ip_dlgModel, QWidget *ip_mainWindow) = 0;
};

//------------------------------------------------------------------------------
/*!
 * @brief
 *   Generic class for the dialog factory.
 */
template<typename TDialog, typename TDialogModel>
struct DialogConstructor : public IDialogConstructor
{
    /*!
     * @details
     *   Returns new instance of the dialog,
     *   and initializes it with parent window (for the default location)
     *   and ip_dlgModel.
     */
    void *create(void *ip_dlgModel, QWidget *ip_mainWindow)
    {
        return new TDialog(static_cast<TDialogModel *>(ip_dlgModel), ip_mainWindow);
    }
};

//------------------------------------------------------------------------------
template<typename TDialog, typename TDialogModel>
void IDialogService::registerDialog()
{
    const QString &dlgModelType = typeid(TDialogModel).name();
    registerConstructor(dlgModelType, new DialogConstructor<TDialog, TDialogModel>());
}

//------------------------------------------------------------------------------
template<typename TDialogModel>
bool IDialogService::showDialog(TDialogModel *ip_dlgModel) const
{
    const QString &dlgModelType = typeid(TDialogModel).name();
    return showDialogForModel(dlgModelType, ip_dlgModel);
}

//------------------------------------------------------------------------------
#endif // IDIALOGSERVICE_H
