#include "BootloaderMock.h"

BootloaderMock::BootloaderMock()
    : m_runAttemptsCount(0)
{
}

void BootloaderMock::callCreateLogger()
{
    m_logger = createLoggerEngine();
}

void BootloaderMock::callCreateComponentProvider()
{
    m_componentProvider = createComponentProvider();
}

void BootloaderMock::callCreateComponentManager()
{
    m_componentManager = createComponentManager();
}

void BootloaderMock::callCreateServiceLocator()
{
    m_serviceLocator = createServiceLocator();
}

ILoggerEngineCreator *BootloaderMock::logger() const
{
    return m_logger;
}

IComponentProvider *BootloaderMock::componentProvider() const
{
    return m_componentProvider;
}

IComponentManager *BootloaderMock::componentManager() const
{
    return m_componentManager;
}

IServiceLocator *BootloaderMock::serviceLocator() const
{
    return m_serviceLocator;
}

int BootloaderMock::runAttemptsCount() const
{
    return m_runAttemptsCount;
}

void BootloaderMock::safeRun()
{
    ++m_runAttemptsCount;
}

void BootloaderMock::configureServiceLocator()
{
}

