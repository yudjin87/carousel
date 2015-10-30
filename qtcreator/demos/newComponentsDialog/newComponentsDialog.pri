DEMO_PROJECT_SOURCES = $$CPP_DEMOS_TREE/newComponentsDialog

HEADERS += \
    $$DEMO_PROJECT_SOURCES/newComponentsDialog_api.h \
    $$DEMO_PROJECT_SOURCES/NewComponentsDialogComponent.h \
    $$DEMO_PROJECT_SOURCES/NewDialog.h \

SOURCES += \
    $$DEMO_PROJECT_SOURCES/NewComponentsDialogComponent.cpp \
    $$DEMO_PROJECT_SOURCES/NewDialog.cpp \

OTHER_FILES += \
    $$DEMO_PROJECT_SOURCES/org.carousel.demos.NewComponentsDialog.definition \


