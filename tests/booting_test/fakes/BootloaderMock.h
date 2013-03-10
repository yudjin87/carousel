#ifndef BOOTLOADERMOCK_H
#define BOOTLOADERMOCK_H

#include <booting/BootloaderBase.h>

class BootloaderMock : public BootloaderBase
{
public:
    BootloaderMock();

public:
    void callCreateLogger();
    void callCreateComponentProvider();
    void callCreateComponentManager();
    void callCreateServiceLocator();
    void callCreateMainWindow();

    ILogger *logger() const;
    IComponentProvider *componentProvider() const;
    IComponentManager *componentManager() const;
    IServiceLocator *serviceLocator() const;
    QMainWindow *mainWindow() const;

    int runAttemptsCount() const;

protected:
    void _run();
    void _configureServiceLocator();

private:
    int m_runAttemptsCount;
};

#endif // BOOTLOADERMOCK_H
