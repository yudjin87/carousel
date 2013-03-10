include(../shared.pri)

QT       += core gui

TARGET = CartoUI

TEMPLATE = lib

DEFINES += CARTO_UI_LIB_IMPORT

DESTDIR = $${PAINTER_WD}/bin/externalSource

win32 {
    LIBS += -L$${CAROUSEL_BIN} -lComponentSystem \
                               -lInteractivity \
                               -lFramework

    LIBS += -L$${DESTDIR} -lDisplay \
                          -lCarto \
                          -lGeometry
}

HEADERS += \
    cartoUI_api.h \
    CartoUIComponent.h \
    CartoUIInteractiveExtension.h \
    FeatureLayerModel.h \
    MapModel.h \
    GraphicsPoinItem.h

SOURCES += \
    CartoUIComponent.cpp \
    CartoUIInteractiveExtension.cpp \
    FeatureLayerModel.cpp \
    MapModel.cpp \
    GraphicsPoinItem.cpp

OTHER_FILES += \
    CartoUI.definition

###############################################################################
# Copy definition to the output directory, right near the library
copyExtraFiles($$OTHER_FILES, $$DESTDIR)
