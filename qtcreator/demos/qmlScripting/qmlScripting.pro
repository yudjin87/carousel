include(../demos_shared.pri)
include(qmlScripting.pri)

QT       += core widgets qml

TARGET = org.carousel.demos.QmlScripting

TEMPLATE = app

LIBS += -L$${DESTDIR}/../bin -lCarousel \
                             -lorg.carousel.Interactivity \
                             -lorg.carousel.ComponentSystemUI \
                             -lorg.carousel.QmlScripting \
                             -lorg.carousel.QmlScriptingUI \

###############################################################################
# Copy definition to the output directory, right near the library
copyExtraFiles($$OTHER_FILES, $$DESTDIR)
copyExtraFiles($$SCRIPTS, $${DESTDIR}/scripts)
