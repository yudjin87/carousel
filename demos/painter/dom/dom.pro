include(../shared.pri)

QT       -= gui

TEMPLATE = lib

TARGET = Dom

DEFINES += DOM_LIB_IMPORT

DESTDIR = $${PAINTER_WD}/bin/externalSource

win32 {
    LIBS += -L$${CAROUSEL_BIN} -lComponentSystem \
                               -lFramework

    LIBS += -L$${DESTDIR} -lCarto
}

# Sources:
HEADERS += \
    dom_api.h \
    PainterDocumentController.h \
    DomComponent.h \
    PainterDocument.h \
    PainterDocumentController.h \
    IPainterDocumentController.h \
    IPainterDocument.h \
    IShape.h

SOURCES += \
    PainterDocumentController.cpp \
    DomComponent.cpp \
    PainterDocument.cpp

OTHER_FILES += Dom.definition

###############################################################################
# Copy definition to the output directory, right near the library
copyExtraFiles($$OTHER_FILES, $$DESTDIR)
