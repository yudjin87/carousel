###############################################################################
# This is a top-level solution folder that groups
# concrete projects together
project(tests CXX)

###############################################################################
# Test executables should have absolute linking paths to the 3d party libraries,
# particulary, for Qt
set(CMAKE_SKIP_BUILD_RPATH FALSE)

###############################################################################
# Add concrete projects to the group
add_subdirectory(booting_test)
add_subdirectory(componentsystem_test)
add_subdirectory(componentsystem_test_libs)
add_subdirectory(interactivity_test)
add_subdirectory(logging_test)
add_subdirectory(utils_test)
#add_subdirectory(jsscripting_test)     deprecated, since QtScript module is deprecated at Qt 5.5
add_subdirectory(qmlscripting_test)
add_subdirectory(persistence_test)

# Manual tests
add_subdirectory(componentsystemui_test)
#add_subdirectory(jsscriptingui_test)   deprecated, since QtScript module is deprecated at Qt 5.5
add_subdirectory(qmlscriptingui_test)

###############################################################################
# Specify dependencies for correct build order
add_dependencies(booting_test              Carousel)
add_dependencies(componentsystem_test      Carousel)
add_dependencies(logging_test              Carousel)
add_dependencies(utils_test                Carousel)
add_dependencies(interactivity_test        org.carousel.Interactivity)
add_dependencies(componentsystemUI_test    org.carousel.ComponentSystemUI)
#add_dependencies(jsscripting_test          org.carousel.JsScripting)       deprecated, since QtScript module is deprecated at Qt 5.5
#add_dependencies(jsscriptingUI_test        org.carousel.JsScriptingUI)     deprecated, since QtScript module is deprecated at Qt 5.5
add_dependencies(qmlscripting_test          org.carousel.QmlScripting)
add_dependencies(qmlscriptingUI_test        org.carousel.QmlScriptingUI)
add_dependencies(persistence_test          org.carousel.Persistence)

###############################################################################
# Organize projects into folders/filters (for MSVC, xCode)
set_property(TARGET booting_test PROPERTY FOLDER "tests")
set_property(TARGET componentsystem_test PROPERTY FOLDER "tests")
set_property(TARGET interactivity_test PROPERTY FOLDER "tests")
set_property(TARGET logging_test PROPERTY FOLDER "tests")
set_property(TARGET utils_test PROPERTY FOLDER "tests")
set_property(TARGET componentsystemUI_test PROPERTY FOLDER "tests")
#set_property(TARGET jsscripting_test PROPERTY FOLDER "tests")              deprecated, since QtScript module is deprecated at Qt 5.5
#set_property(TARGET jsscriptingUI_test PROPERTY FOLDER "tests")            deprecated, since QtScript module is deprecated at Qt 5.5
set_property(TARGET qmlscripting_test PROPERTY FOLDER "tests")
set_property(TARGET qmlscriptingUI_test PROPERTY FOLDER "tests")
set_property(TARGET persistence_test PROPERTY FOLDER "tests")
