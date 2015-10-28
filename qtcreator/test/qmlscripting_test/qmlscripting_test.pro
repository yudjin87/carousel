include (../test_shared.pri)
include (qmlscripting_test.pri)

QT      -= widgets
QT      += qml

TARGET = qmlscripting_test

LIBS += -L$${DESTDIR}/../bin -lCarousel \
                             -lorg.carousel.QmlScripting \

###############################################################################
# Copy script files to the script directory
copyExtraFilesToDir($$OTHER_FILES, $$DESTDIR/scripts)

win32:QMAKE_POST_LINK += windeployqt $$shell_quote($$DESTDIR/$$TARGET.exe)
