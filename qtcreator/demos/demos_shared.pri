include (../carousel_props.pri)

TEMPLATE = app

DESTDIR = $${CAROUSEL_WD}/$${BIN_OUTPUT_PATH}/demos

INCLUDEPATH += $$HPP_SOURCE_TREE/carousel \
               $$HPP_SOURCE_TREE/components
