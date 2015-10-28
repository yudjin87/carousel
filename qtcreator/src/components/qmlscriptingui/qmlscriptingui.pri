PROJECT_SOURCES = $$CPP_SOURCE_TREE/components/qmlscriptingui
PROJECT_HEADERS = $$HPP_SOURCE_TREE/components/qmlscriptingui

HEADERS += \
    $$PROJECT_HEADERS/CodeHighlighter.h \
    $$PROJECT_HEADERS/ColorTheme.h \
    $$PROJECT_HEADERS/LexemeAppearance.h \
    $$PROJECT_HEADERS/qmlscriptingui_global.h \
    $$PROJECT_HEADERS/QmlScriptingUIComponent.h \
    $$PROJECT_HEADERS/QmlScriptingUIInteractiveExtension.h \
    $$PROJECT_HEADERS/ScriptCollectionDialog.h \
    $$PROJECT_HEADERS/ScriptCollectionModel.h \
    $$PROJECT_HEADERS/ScriptConsoleView.h \
    $$PROJECT_HEADERS/ScriptUnitView.h \
    $$PROJECT_HEADERS/ShowScriptsOperation.h \

SOURCES += \
    $$PROJECT_SOURCES/CodeHighlighter.cpp \
    $$PROJECT_SOURCES/ColorTheme.cpp \
    $$PROJECT_SOURCES/LexemeAppearance.cpp \
    $$PROJECT_SOURCES/QmlScriptingUIComponent.cpp \
    $$PROJECT_SOURCES/QmlScriptingUIInteractiveExtension.cpp \
    $$PROJECT_SOURCES/ScriptCollectionDialog.cpp \
    $$PROJECT_SOURCES/ScriptCollectionModel.cpp \
    $$PROJECT_SOURCES/ScriptConsoleView.cpp \
    $$PROJECT_SOURCES/ScriptUnitView.cpp \
    $$PROJECT_SOURCES/ShowScriptsOperation.cpp \

OTHER_FILES += \
    $$PROJECT_SOURCES/org.carousel.QmlScriptingUI.definition \

FORMS += \
    $$PROJECT_SOURCES/ScriptCollectionDialog.ui \
    $$PROJECT_SOURCES/ScriptConsoleView.ui \
    $$PROJECT_SOURCES/ScriptUnitView.ui \

RESOURCES += \
    $$PROJECT_SOURCES/qmlscriptingui.qrc \

