include (../../carousel.pri)
include (undo.pri)

QT      += gui
QT      += core
TEMPLATE = lib

TARGET = Undo

DEFINES += UNDO_LIBRARY

INCLUDEPATH += $$HPP_SOURCE_TREE/undo

LIBS += -L$${DESTDIR} -lComponentSystem \
                      -lFramework \
                      -lInteractivity \

###############################################################################
# Copy definition to the output directory, right near the library
copyExtraFiles($$OTHER_FILES)

RESOURCES += \
