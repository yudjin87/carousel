PROJECT_SOURCES = $$CPP_SOURCE_TREE/components/qmlscripting
PROJECT_HEADERS = $$HPP_SOURCE_TREE/components/qmlscripting

HEADERS += \
    $$PROJECT_HEADERS/CarouselScriptEngineConfigurationDelegate.h \
    $$PROJECT_HEADERS/IOutputHandler.h \
    $$PROJECT_HEADERS/IScriptCollection.h \
    $$PROJECT_HEADERS/IScriptConsole.h \
    $$PROJECT_HEADERS/IScriptEngineConfigurationDelegate.h \
    $$PROJECT_HEADERS/IScriptEngineFactory.h \
    $$PROJECT_HEADERS/IScriptExtension.h \
    $$PROJECT_HEADERS/IScriptingService.h \
    $$PROJECT_HEADERS/IScriptUnit.h \
    $$PROJECT_HEADERS/qmlscripting_global.h \
    $$PROJECT_HEADERS/QmlScriptingComponent.h \
    $$PROJECT_HEADERS/ScriptCollection.h \
    $$PROJECT_HEADERS/ScriptConsole.h \
    $$PROJECT_HEADERS/ScriptingService.h \
    $$PROJECT_HEADERS/ScriptUnit.h \
    $$PROJECT_HEADERS/ServiceLocatorWrapper.h \
    $$PROJECT_HEADERS/SimpleCompleter.h \
    $$PROJECT_HEADERS/ConsoleJsObject.h \

SOURCES += \
    $$PROJECT_SOURCES/CarouselScriptEngineConfigurationDelegate.cpp \
    $$PROJECT_SOURCES/QmlScriptingComponent.cpp \
    $$PROJECT_SOURCES/ScriptCollection.cpp \
    $$PROJECT_SOURCES/ScriptConsole.cpp \
    $$PROJECT_SOURCES/ScriptingService.cpp \
    $$PROJECT_SOURCES/ScriptUnit.cpp \
    $$PROJECT_SOURCES/ServiceLocatorWrapper.cpp \
    $$PROJECT_SOURCES/SimpleCompleter.cpp \
    $$PROJECT_SOURCES/ConsoleJsObject.cpp \

OTHER_FILES += \
    $$PROJECT_SOURCES/org.carousel.QmlScripting.definition \

