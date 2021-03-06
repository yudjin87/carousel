#pragma once
#include <carousel/componentsystem/ComponentLoader.h>

class MockComponentLoader : public ComponentLoader
{
    Q_OBJECT
public:
    MockComponentLoader(QObject *parent = nullptr);
    MockComponentLoader(const QString & fileName, QObject *parent = nullptr);
    ~MockComponentLoader();

    IComponent *instance();
    IComponent *getInstance();
    bool load();
    bool deleteInstance();

signals:
    void unloaded();

public:
    int instanceCalled;
    int loadCalled;
    int unloadCalled;
};

