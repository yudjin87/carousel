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

#include "FileComponentProviderTest.h"
#include "fakes/FakeDefinitionParser.h"
#include "fakes/MockFileComponentProvider.h"
#include "Utils.h"

#include <carousel/componentsystem/FileComponentProvider.h>
#include <carousel/componentsystem/IComponent.h>

#include <QtTest/QTest>
#include <QtTest/QSignalSpy>

typedef AutoComponentProvider<FileComponentProvider> AutoFileComponentProvider;

FileComponentProviderTest::FileComponentProviderTest(QObject *parent)
    : QObject(parent)
    , definitionPath(pathToComponentDefinition("TestComponent2"))
{
}

void FileComponentProviderTest::shouldSetupFileName()
{
    AutoFileComponentProvider provider(definitionPath);

    QCOMPARE(provider.path(), definitionPath);
}

void FileComponentProviderTest::shouldNotSetupUnexistingFileName()
{
    AutoFileComponentProvider provider("/path/to/Nowhere.definition");

    QVERIFY(provider.path().isEmpty());
}

void FileComponentProviderTest::initialize_shouldReturnTrue()
{
    MockFileComponentProvider provider(definitionPath);
    MockProxyComponent::initializeReturnValue = true;
    provider.initialize();
    MockProxyComponent::initializeReturnValue = false;

    QCOMPARE(provider.isInitialized(), true);
}

void FileComponentProviderTest::initialize_shouldReturnFalseIfLoadingReturnsNull()
{
    AutoFileComponentProvider provider("/path/to/Nowhere.definition");

    provider.initialize();

    QCOMPARE(provider.isInitialized(), false);
}

void FileComponentProviderTest::initialize_shouldCallLoadComponent()
{
    MockFileComponentProvider provider;

    provider.initialize();

    QCOMPARE(provider.loadCalled, 1);
}

void FileComponentProviderTest::loadComponent_shouldSetInvalidStateIfPathIsEmpty()
{
    AutoFileComponentProvider provider;

    IComponent *result = provider.loadComponent();
    QCOMPARE(result->state(), IComponent::Invalid);
}

void FileComponentProviderTest::loadComponent_shouldSetDiscoveredStateIfParserReturnFalse()
{
    MockFileComponentProvider provider(definitionPath, new FakeDefinitionParser());
    provider.parser->m_readResult = false;

    IComponent *result = provider.loadComponent();
    QCOMPARE(result->state(), IComponent::Discovered);
}

void FileComponentProviderTest::loadComponent_shouldSetDiscoveredStateIfConstructorReturnFalse()
{
    MockFileComponentProvider provider(definitionPath);
	provider.constructor = new MockDefaultConstructor();
    provider.constructor->m_constructResult = new bool(false);

    IComponent *result = provider.loadComponent();
    QCOMPARE(result->state(), IComponent::Discovered);
}

void FileComponentProviderTest::loadComponent_shouldLoadComponent()
{
    MockFileComponentProvider provider(definitionPath);
    MockProxyComponent::initializeReturnValue = true;
    IComponent *result = provider.loadComponent();
    MockProxyComponent::initializeReturnValue = false;

    QCOMPARE(result->state(), IComponent::Initialized);
}

void FileComponentProviderTest::loadComponent_shouldCallReadOnParser()
{
    MockFileComponentProvider provider(definitionPath, new FakeDefinitionParser());
    QSignalSpy spy(provider.parser, SIGNAL(readCalled()));

    provider.loadComponent();

    QCOMPARE(spy.size(), 1);
}

void FileComponentProviderTest::loadComponent_shouldCallConstructOnConstructor()
{
    MockFileComponentProvider provider(definitionPath);
    provider.constructor = new MockDefaultConstructor();
    QSignalSpy spy(provider.constructor, SIGNAL(constructCalled()));

    provider.loadComponent();

    QCOMPARE(spy.size(), 1);
}

void FileComponentProviderTest::loadComponent_shouldPopulateWithComponent()
{
    MockFileComponentProvider provider(definitionPath);
    MockProxyComponent::initializeReturnValue = true;
    provider.loadComponent();
    MockProxyComponent::initializeReturnValue = false;

    QCOMPARE(provider.components().size(), 1);
}

void FileComponentProviderTest::loadComponent_shouldNotPopulateComponentIfItsInitializationFault()
{
    MockFileComponentProvider provider(definitionPath);

    MockProxyComponent::initializeReturnValue = false;
    provider.loadComponent();
    MockProxyComponent::initializeReturnValue = true;

    QCOMPARE(provider.components().size(), 0);
}

void FileComponentProviderTest::loadComponent_shouldSetParsedStateIfConstructorReturnTrueButInitializationFailed()
{
    MockFileComponentProvider provider(definitionPath);

    MockProxyComponent::initializeReturnValue = false;
    IComponent *result = provider.loadComponent();
    MockProxyComponent::initializeReturnValue = true;

    QCOMPARE(result->state(), IComponent::Parsed);
}

