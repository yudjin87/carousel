TEMPLATE = subdirs
CONFIG  += ordered

SUBDIRS += \
    interactivity \
    undo \
    componentsystemui \
    qmlscripting \
    qmlscriptingui \
#    jsscripting \          deprecated, since QtScript module is deprecated at Qt 5.5
#    jsscriptingui \        deprecated, since QtScript module is deprecated at Qt 5.5
    persistence \
    persistenceui \

