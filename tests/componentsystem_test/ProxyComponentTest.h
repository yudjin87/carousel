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

#ifndef PROXYCOMPONENTTEST_H
#define PROXYCOMPONENTTEST_H

#include <QtCore/QObject>

class ProxyComponentTest : public QObject
{
    Q_OBJECT
public:
    explicit ProxyComponentTest(QObject *parent = 0);
    
private slots:
    void shouldReturnSpecifiedNameUntilComponentLoaded();

    void initializeCallShouldSetupComponentName();
    void initializeCallShouldSetupLoaderFileName();
    void initializeCallShouldSetupLoaderFileNameAsComponentNameIfLocationIsAbsent();
    void initializeCallShouldSetupAbsoluteFileNameToLoader();
    void initializeCallShouldSetupComponentDefinition();
    void initializeCallShouldInvokeLoadAvailability();
    void initializeCallShouldReturnTrue();
    void initializeCallShouldReturnFalseIfLibraryFileDoesNotExist();

    void extensionShouldReturnRealComponentExtension();
    void extensionShouldReturnNullUntilRealComponentIsCreated();

    void startupShouldLoadComponent();
    void startupShouldReturnFalseIfInitialzeWasNotCalled();
    void startupShouldReturnFalseIfLoadFailed();
    void startupShouldCallStartupOnTheLoadedComponent();
    void startupShouldReturnResultOfTheLoadedComponentStartup();

    void shutdownShouldUnloadComponent();
    void shutdownShouldShutdownLoadedComponent();

private:
    const QString definitionLocation;
};

#endif // PROXYCOMPONENTTEST_H
