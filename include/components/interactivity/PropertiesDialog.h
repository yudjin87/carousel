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
#include <components/interactivity/interactivity_global.h>
#include <QtWidgets/QDialog>

namespace Ui
{
class PropertiesDialog;
}

class PropertiesWidget;
class IServiceLocator;
class QDialogButtonBox;

// TODO: register in dialog service?
class INTERACTIVITY_API PropertiesDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PropertiesDialog(QWidget *parent = nullptr, Qt::WindowFlags f = 0);
    explicit PropertiesDialog(IServiceLocator *serviceLocator, QWidget *parent = nullptr, Qt::WindowFlags f = 0);
    ~PropertiesDialog();

    void installCentralWidget(PropertiesWidget *propertiesWidget);

public slots:
    void accept() override;
    void reject() override;
    void apply();

private slots:
    void onPropertyChanged();

private:
    bool m_isDirty;
    Ui::PropertiesDialog* m_ui;
    QDialogButtonBox *m_buttonBox;
    IServiceLocator *m_serviceLocator;
    PropertiesWidget *m_propertiesWidget;
};

