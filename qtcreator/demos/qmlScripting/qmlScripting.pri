DEMO_PROJECT_SOURCES = $$CPP_DEMOS_TREE/qmlScripting

SOURCES += \
    $$DEMO_PROJECT_SOURCES/Bootloader.cpp \
    $$DEMO_PROJECT_SOURCES/DemoApp.cpp \
    $$DEMO_PROJECT_SOURCES/main.cpp\
    $$DEMO_PROJECT_SOURCES/MainWindow.cpp \

HEADERS  += \
    $$DEMO_PROJECT_SOURCES/MainWindow.h \
    $$DEMO_PROJECT_SOURCES/Bootloader.h \
    $$DEMO_PROJECT_SOURCES/DemoApp.h \

FORMS += \
    $$DEMO_PROJECT_SOURCES/MainWindow.ui \


SCRIPTS += \
    $$DEMO_PROJECT_SOURCES/scripts/startup.js \
    $$DEMO_PROJECT_SOURCES/scripts/components.js \
    $$DEMO_PROJECT_SOURCES/scripts/uiManipulations.js \
    $$DEMO_PROJECT_SOURCES/scripts/scripting.js \

OTHER_FILES += \
    $${SCRIPTS} \

