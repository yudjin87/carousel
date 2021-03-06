###############################################################################
# interactivity project
set(CRSL_PROJECT_NAME "org.carousel.Interactivity")
set(CRSL_TARGET_TYPE "components")

include(cmake/target_utils)

######################################################################
# Sources
set(__SOURCES
    ${CRSL_TARGET_SOURCES}/BaseInputReceiver.cpp 
    ${CRSL_TARGET_SOURCES}/CarouselComponentConfigurationDelegate.cpp 
    ${CRSL_TARGET_SOURCES}/CarouselInteractionService.cpp 
    ${CRSL_TARGET_SOURCES}/Catalogs.cpp 
    ${CRSL_TARGET_SOURCES}/ConfigurationChanges.cpp 
    ${CRSL_TARGET_SOURCES}/DialogService.cpp 
    ${CRSL_TARGET_SOURCES}/DockWidgetCatalog.cpp 
    ${CRSL_TARGET_SOURCES}/InputDispatcher.cpp 
    ${CRSL_TARGET_SOURCES}/InteractionServiceComponent.cpp 
    ${CRSL_TARGET_SOURCES}/MenuCatalog.cpp 
    ${CRSL_TARGET_SOURCES}/Operation.cpp 
    ${CRSL_TARGET_SOURCES}/OperationCatalog.cpp 
    ${CRSL_TARGET_SOURCES}/PropertiesDialog.cpp 
    ${CRSL_TARGET_SOURCES}/PropertiesWidget.cpp 
    ${CRSL_TARGET_SOURCES}/ToggleActionWrapper.cpp 
    ${CRSL_TARGET_SOURCES}/ToogleDialogOperation.cpp 
    ${CRSL_TARGET_SOURCES}/ToolBarCatalog.cpp 
    ${CRSL_TARGET_SOURCES}/ToolBase.cpp 
)

######################################################################
# Headers
set(__HEADERS
    ${CRSL_TARGET_HEADERS}/BaseInputReceiver.h 
    ${CRSL_TARGET_HEADERS}/CarouselComponentConfigurationDelegate.h 
    ${CRSL_TARGET_HEADERS}/CarouselInteractionService.h 
    ${CRSL_TARGET_HEADERS}/Catalogs.h 
    ${CRSL_TARGET_HEADERS}/ConfigurationChanges.h 
    ${CRSL_TARGET_HEADERS}/DialogService.h 
    ${CRSL_TARGET_HEADERS}/DockWidgetCatalog.h 
    ${CRSL_TARGET_HEADERS}/ICatalogs.h 
    ${CRSL_TARGET_HEADERS}/IComponentConfigurationDelegate.h 
    ${CRSL_TARGET_HEADERS}/IDialogService.h 
    ${CRSL_TARGET_HEADERS}/IDockWidgetCatalog.h 
    ${CRSL_TARGET_HEADERS}/IInputDispatcher.h 
    ${CRSL_TARGET_HEADERS}/IInputReceiver.h 
    ${CRSL_TARGET_HEADERS}/IInteractionService.h 
    ${CRSL_TARGET_HEADERS}/IInteractiveExtension.h 
    ${CRSL_TARGET_HEADERS}/IMenuCatalog.h 
    ${CRSL_TARGET_HEADERS}/InputDispatcher.h 
    ${CRSL_TARGET_HEADERS}/InteractionServiceComponent.h 
    ${CRSL_TARGET_HEADERS}/interactivity_global.h 
    ${CRSL_TARGET_HEADERS}/IOperation.h 
    ${CRSL_TARGET_HEADERS}/IOperationCatalog.h 
    ${CRSL_TARGET_HEADERS}/ITool.h 
    ${CRSL_TARGET_HEADERS}/IToolBarCatalog.h 
    ${CRSL_TARGET_HEADERS}/MenuCatalog.h 
    ${CRSL_TARGET_HEADERS}/Operation.h 
    ${CRSL_TARGET_HEADERS}/OperationCatalog.h 
    ${CRSL_TARGET_HEADERS}/PropertiesDialog.h 
    ${CRSL_TARGET_HEADERS}/PropertiesWidget.h 
    ${CRSL_TARGET_HEADERS}/ToggleActionWrapper.h 
    ${CRSL_TARGET_HEADERS}/ToogleDialogOperation.h 
    ${CRSL_TARGET_HEADERS}/ToolBarCatalog.h 
    ${CRSL_TARGET_HEADERS}/ToolBase.h 
)

######################################################################
# Forms
set(__FORMS
    ${CRSL_TARGET_SOURCES}/PropertiesDialog.ui 
)

######################################################################
# Definitions
set(__OTHER_FILES
    ${CRSL_TARGET_SOURCES}/org.carousel.Interactivity.definition 
)

######################################################################
# Qt generated files
qt5_wrap_cpp(__HEADERS_MOC ${__HEADERS})
qt5_wrap_ui(__UI_HEADERS ${__FORMS})

# As moc files are generated in the binary dir, tell CMake
# to always look for includes there:
include_directories(${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_INCLUDE_CURRENT_DIR ON)

######################################################################
# Group sources into IDE's filters
source_group("src" FILES ${__SOURCES} ${__HEADERS} ${__OTHER_FILES})
source_group("moc" FILES ${__HEADERS_MOC})
source_group("forms" FILES ${__UI_HEADERS} ${__FORMS})

######################################################################
# Create target 'CRSL_PROJECT_NAME' from specified source files
add_library(${CRSL_PROJECT_NAME} ${CRSL_LIB_TYPE} ${__SOURCES} ${__HEADERS} ${__HEADERS_MOC} ${__FORMS} ${__UI_HEADERS} ${__OTHER_FILES})

######################################################################
# Setup output path
crsl_setup_output_path(bin)

######################################################################
# Add targets to a list of libraries to linking
target_link_libraries(${CRSL_PROJECT_NAME} Carousel)

###############################################################################
# Qt dependencies
qt5_use_modules(${CRSL_PROJECT_NAME} Core Widgets Gui)

###############################################################################
# Copy definition to the output directory, right near the library
crsl_copy_extra_files(${CRSL_PROJECT_NAME} "${__OTHER_FILES}" $<TARGET_FILE_DIR:${CRSL_PROJECT_NAME}>)
