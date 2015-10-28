TEMPLATE = subdirs
CONFIG  += ordered

SUBDIRS += \
    booting_test \
    componentsystem_test \
    componentsystem_test_libs \
    componentsystemui_test \
    interactivity_test \
    logging_test \
    utils_test \
#    jsscripting_test \      deprecated, since QtScript module is deprecated at Qt 5.5
#    jsscriptingui_test \    deprecated, since QtScript module is deprecated at Qt 5.5
    qmlscripting_test \
    qmlscriptingui_test \
    persistence_test \

