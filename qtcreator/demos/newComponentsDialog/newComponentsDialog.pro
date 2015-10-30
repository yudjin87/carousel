include(../demos_shared.pri)
include(newComponentsDialog.pri)

QT       += core widgets

TARGET = org.carousel.demos.NewComponentsDialog

TEMPLATE = lib

DEFINES += NEWCOMPONENTSDIALOG_LIB_IMPORT

LIBS += -L$${DESTDIR}/../bin -lCarousel \
                             -lorg.carousel.Interactivity \
                             -lorg.carousel.ComponentSystemUI \

###############################################################################
# Copy definition to the output directory, right near the library
copyExtraFiles($$OTHER_FILES, $$DESTDIR)
