########################################################################################
# Format name for the external variable, which contains path to the Qt5 directory.
# See user_settings.cmake.template to find all variables.
string(TOUPPER ${CRSL_COMPILER}-x${CRSL_TARGET_PLATFORM_BITS} __COMPILER)
set(__QT_ROOT_DIR ${QT_ROOT_LOCATION_${__COMPILER}})

if("${QT_ROOT_LOCATION_${__COMPILER}}" STREQUAL "")
    message(STATUS "The QT_ROOT_LOCATION_${__COMPILER} variable was not found, use environment variable QTDIR")
    set(__QT_ROOT_DIR $ENV{QTDIR})
else()
    set(ENV{CMAKE_PREFIX_PATH} ${__QT_ROOT_DIR})
    set(ENV{QTDIR} ${__QT_ROOT_DIR})
endif()

message(STATUS "Qt directory: " ${__QT_ROOT_DIR})

########################################################################################
# Map Qt libraries to debug/release configurations
foreach(__LIB_BASENAME ${__LIBRARIES_BASENAME})
  if(DEBUG_VERBOSITY)
    message(STATUS "Finding Qt5${__LIB_BASENAME} ...")
  endif()

  find_package(Qt5${__LIB_BASENAME} REQUIRED)

  # map debug-static and release-static configurations
  set_target_properties(Qt5::${__LIB_BASENAME} PROPERTIES MAP_IMPORTED_CONFIG_RELEASE-STATIC "RELEASE")
  set_target_properties(Qt5::${__LIB_BASENAME} PROPERTIES MAP_IMPORTED_CONFIG_DEBUG-STATIC "DEBUG")

  # get run-time library paths (they will be copied for Windows and for MacOS bundle)
  get_target_property(Qt5_${__LIB_BASENAME}_RUNTIME_DEBUG Qt5::${__LIB_BASENAME} "IMPORTED_LOCATION_DEBUG")
  get_target_property(Qt5_${__LIB_BASENAME}_RUNTIME_RELEASE Qt5::${__LIB_BASENAME} "IMPORTED_LOCATION_RELEASE")

  # Check, if both release and debug versions of Qt are built
  if (${Qt5_${__LIB_BASENAME}_RUNTIME_DEBUG} MATCHES ".*NOTFOUND.*")
    message(FATAL_ERROR "Debug library for the Qt${__LIB_BASENAME} not found")
  endif()
  if (${Qt5_${__LIB_BASENAME}_RUNTIME_RELEASE} MATCHES ".*NOTFOUND.*")
    message(FATAL_ERROR "Release library for the Qt${__LIB_BASENAME} not found")
  endif()

  # get full path
  get_filename_component(Qt5_${__LIB_BASENAME}_RUNTIME_DEBUG ${Qt5_${__LIB_BASENAME}_RUNTIME_DEBUG} REALPATH)
  get_filename_component(Qt5_${__LIB_BASENAME}_RUNTIME_RELEASE ${Qt5_${__LIB_BASENAME}_RUNTIME_RELEASE} REALPATH)

  if (DEBUG_VERBOSITY)
    message(STATUS "Qt${__LIB_BASENAME} debug: " ${Qt5_${__LIB_BASENAME}_RUNTIME_DEBUG})
    message(STATUS "Qt${__LIB_BASENAME} release: " ${Qt5_${__LIB_BASENAME}_RUNTIME_RELEASE})
  endif()

  list(APPEND __Qt5_all_RUNTIMES_DEBUG ${Qt5_${__LIB_BASENAME}_RUNTIME_DEBUG})
  list(APPEND __Qt5_all_RUNTIMES_RELEASE ${Qt5_${__LIB_BASENAME}_RUNTIME_RELEASE})
endforeach()

