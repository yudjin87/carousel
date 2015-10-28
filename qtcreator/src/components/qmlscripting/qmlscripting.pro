include (../../../carousel_props.pri)
include (qmlscripting.pri)

QT      -= widgets
QT      += core qml

TEMPLATE = lib

TARGET = org.carousel.QmlScripting

DEFINES += ORG_CAROUSEL_QML_SCRIPTING_LIBRARY

INCLUDEPATH += $$HPP_SOURCE_TREE/components/qmlscripting

LIBS += -L$${DESTDIR} -lCarousel

###############################################################################
# Copy definition to the output directory, right near the library
copyExtraFiles($$OTHER_FILES)
