###############################################################################
# This module finds Qt5 stuff depending on the platform, because Qt5 has different
# structure for different platforms. E.g., it is possible to build both debug
# and release build of Qt5 on MacOS and Windows, but not on Linux. On Linux you
# should build debug and release in the separate directories, because Qt5 CMake files
# for release and for debug will be different on Linux, e.g. on Windows there are two
# configurations (Qt5CoreConfig.cmake):
#     _populate_imported_target_properties(DEBUG "Qt5Cored.dll" "Qt5Cored.lib" )
#     _populate_imported_target_properties(RELEASE "Qt5Core.dll" "Qt5Core.lib" )
# but on Linux only one:
#     _populate_Core_target_properties(DEBUG "libQt5Core.so.5.0.2")
# or
#     _populate_Core_target_properties(RELEASE "libQt5Core.so.5.0.2")

########################################################################################
# List of Qt5 modules carousel is dependent on
set(__LIBRARIES_BASENAME
    Core
    Gui
    Script
    Test
    Widgets
    Xml)

########################################################################################
# Include import-script depending on build platform
if(MSVC)
  message(STATUS "Import Qt5 for the MSVC compiler...")
  include(cmake/import_qt5_msvc.cmake)
elseif(MINGW)
  message(STATUS "Import Qt5 for the MinGW compiler...")
  include(cmake/import_qt5_mingw.cmake)
elseif(XCODE_VERSION)
  message(STATUS "Import Qt5 for the Xcode (Clang compiler)...")
  include(cmake/import_qt5_clang.cmake)
elseif(${CMAKE_CXX_COMPILER_ID} MATCHES "Clang")
  message(STATUS "Import Qt5 for the Clang compiler...")
  include(cmake/import_qt5_clang.cmake)
elseif(${CMAKE_GENERATOR} MATCHES "Unix Makefiles")
  message(STATUS "Import Qt5 for the GNU compiler...")
  include(cmake/import_qt5_gnu.cmake)
endif()

message(STATUS "Qt5: Found.")
