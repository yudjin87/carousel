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

