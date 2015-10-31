include (../../../carousel_props.pri)
include (qmlscriptingui.pri)

QT      += widgets
QT      += core
QT      += qml

TEMPLATE = lib

TARGET = org.carousel.QmlScriptingUI

DEFINES += ORG_CAROUSEL_QMLSCRIPTINGUI_LIBRARY

INCLUDEPATH += $$HPP_SOURCE_TREE/components/qmlscriptingui

LIBS += -L$${DESTDIR} -lCarousel \
                      -lorg.carousel.QmlScripting \
                      -lorg.carousel.Interactivity \

###############################################################################
# Copy definition to the output directory, right near the library
copyExtraFiles($$OTHER_FILES)
