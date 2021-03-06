#pragma once
#include <QtCore/QObject>

class CompositeComponentProviderTest : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void canAddProvider();
    void shouldInitialiseAllProviders();
    void shouldJoinComponentsFromAllProviders();
    void shouldMergeComponentsBothFromProvidersAndFromComponentsList();
};

