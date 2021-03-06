# This is a settings file that contains a common used variables and
# instructions
#
#========================================================
#   +/carousel                     <= CAROUSEL_WD
#       +/demos
#       +/docs
#       +/include                  <= HPP_SOURCE_TREE
#       +/product                  <= Binaries output (for different configurations and platforms)
#           +/mingw-x64-debug      <= BIN_OUTPUT_PATH
#              +/bin               <= Binaries
#              +/intermediate      <= Intermediate files
#              +/unittest          <= Unittest applications
#           +/mingw-x64-release
#           +/msvc-x32-debug-static
#           +/msvc-x64-release-static
#           +/...
#       +/msvc                     <= Source tree for the MSVC
#       +/qtcreator                <= IDE_SOURCE_TREE
#           +/carousel.pro
#           +/carousel_with_tests.pro
#       +/src                      <= CPP_SOURCE_TREE
#           +/carousel             <= Carousel libraries
#               +/booting          <= PROJECT_SOURCES
#               +/...
#           +/components           <= Carousel components
#               +/interactivity    <= PROJECT_SOURCES
#       +/tests                    <= CPP_TESTS_TREE
#           +/booting_test         <= TEST_PROJECT_SOURCES
#           +/...
#========================================================
#

# Do not create symbol links
CONFIG += plugin

IDE_SOURCE_TREE = $$PWD
CAROUSEL_WD  = $$PWD/..
CPP_SOURCE_TREE = $$CAROUSEL_WD/src
HPP_SOURCE_TREE = $$CAROUSEL_WD/include
CPP_TESTS_TREE = $$CAROUSEL_WD/tests
CPP_DEMOS_TREE = $$CAROUSEL_WD/demos

INCLUDEPATH += $$HPP_SOURCE_TREE

# Format binary output path:
win32-g*:BUILD_CONFIG=mingw
win32-msvc*:BUILD_CONFIG=msvc
macx:BUILD_CONFIG=clang
unix:BUILD_CONFIG=gnu
unix:android:BUILD_CONFIG=android

contains(QT_ARCH, i386) {
    BUILD_CONFIG=$${BUILD_CONFIG}-x32
} else {
    BUILD_CONFIG=$${BUILD_CONFIG}-x64
}

CONFIG(release, debug|release) {
    BUILD_CONFIG=$${BUILD_CONFIG}-release
}
CONFIG(debug, debug|release) {
    BUILD_CONFIG=$${BUILD_CONFIG}-debug
}

static {# everything below takes effect with CONFIG+=static
    DEFINES += STATIC_BUILD
    BUILD_CONFIG=$${BUILD_CONFIG}-static
} else {
    DEFINES -= STATIC_BUILD
}

BIN_OUTPUT_PATH = product/$${BUILD_CONFIG}
DESTDIR         = $${CAROUSEL_WD}/$${BIN_OUTPUT_PATH}/bin

# Store intermedia stuff somewhere else
OBJECTS_DIR     = $${CAROUSEL_WD}/$${BIN_OUTPUT_PATH}/intermediate/obj/$${TARGET}
MOC_DIR         = $${CAROUSEL_WD}/$${BIN_OUTPUT_PATH}/intermediate/moc/$${TARGET}
RCC_DIR         = $${CAROUSEL_WD}/$${BIN_OUTPUT_PATH}/intermediate/rcc/$${TARGET}
UI_DIR          = $${CAROUSEL_WD}/$${BIN_OUTPUT_PATH}/intermediate/ui/$${TARGET}
UI_HEADERS_DIR  = $${CAROUSEL_WD}/$${BIN_OUTPUT_PATH}/intermediate/ui/$${TARGET}
UI_SOURCES_DIR  = $${CAROUSEL_WD}/$${BIN_OUTPUT_PATH}/intermediate/ui/$${TARGET}

#########################################################
# Compiler flags
#########################################################
!win32-msvc* {
    QMAKE_CXXFLAGS += -std=c++11
    QMAKE_CXXFLAGS += -Wall -Wextra -Wuninitialized -Werror -pedantic
}

#########################################################
# MSVC compiler shows this warning, but with virtual inheritance
# that problem is solved, so just disable it.
win32-msvc*:QMAKE_CXXFLAGS += /wd4250

#########################################################
# Copies the given files to the destination directory
defineTest(copyExtraFiles) {
    files = $$1

    for(FILE, files) {
        DDIR = $$DESTDIR

        # Replace slashes in paths with backslashes for Windows
        win32-msvc*:FILE ~= s,/,\\,g
        win32-msvc*:DDIR ~= s,/,\\,g

        QMAKE_POST_LINK += $$QMAKE_COPY $$quote($$FILE) $$quote($$DDIR) $$escape_expand(\\n\\t)
    }

    export(QMAKE_POST_LINK)
}

#########################################################
# Copies the given files to the specified directory
defineTest(copyExtraFilesToDir) {
    files = $$1
    DDIR = $$2

    win32-msvc*:DDIR ~= s,/,\\,g
    win32-msvc*:ABSOLUTE_PATH ~= s,/,\\,g

    # Create directory for copying
    win32-msvc* { # for Windows we also should check whether this directory exists
        QMAKE_POST_LINK += $$QMAKE_CHK_DIR_EXISTS $$quote($$DDIR) $$QMAKE_MKDIR $$quote($$DDIR) $$escape_expand(\\n\\t)
    } else {
        QMAKE_POST_LINK += $$QMAKE_MKDIR $$quote($$DDIR) $$escape_expand(\\n\\t)
    }

    for(FILE, files) {
        # Replace slashes in paths with backslashes for Windows
        win32-msvc*:FILE ~= s,/,\\,g

        QMAKE_POST_LINK += $$QMAKE_COPY $$quote($$FILE) $$quote($$DDIR) $$escape_expand(\\n\\t)
    }

    export(QMAKE_POST_LINK)
}
