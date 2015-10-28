include (../test_shared.pri)
include (qmlscriptingui_test.pri)

QT      += widgets
QT      += qml

TARGET = qmlscriptingui_test

LIBS += -L$${DESTDIR}/../bin -lCarousel \
                             -lorg.carousel.Interactivity \
                             -lorg.carousel.QmlScripting \
                             -lorg.carousel.QmlScriptingUI \

###############################################################################
# Copy script files to the script directory
copyExtraFilesToDir($$OTHER_FILES, $$DESTDIR/scripts)

win32:QMAKE_POST_LINK += windeployqt $$shell_quote($$DESTDIR/$$TARGET.exe)
