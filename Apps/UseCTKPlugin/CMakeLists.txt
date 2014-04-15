project(UseCTKPluginMain)

#set(SRCS
#  UseCTKPluginMain.cpp
#)

#message(STATUS "CMAke path: " ${CMAKE_MODULE_PATH})
include("${CTK_CMAKE_DIR}/ctkMacroBuildApp.cmake")
#include(ctkMacroBuildApp)

#> Include dirs
set(my_includes
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CTK_INCLUDE_DIRS} # CTK include dirs for enabled libraries
  ${CTKPluginTutorials_BINARY_DIR}/Plugins/org.mydomain.testplugin
  ${CTKPluginTutorials_SOURCE_DIR}/Plugins/org.mydomain.testplugin
#include "org.commontk.plugingenerator.core/ctkPluginGeneratorCoreModel.h"
#  ${CTK_SOURCE_DIR}/Plugins/org.commontk.plugingenerator.core
#  ${CTK_BINARY_DIR}/Plugins/org.commontk.plugingenerator.core
  /Users/christiana/dev/external/CTK/CTK/Plugins/org.commontk.plugingenerator.core
  /Users/christiana/dev/external/CTK/build_Debug/CTK-build/Plugins/org.commontk.plugingenerator.core
)
#>

#set(my_libs
#  CTKPluginFramework
#)

include_directories(${my_includes})

#####


set(KIT_SRCS
  UseCTKPluginMain.cpp
)

# Headers that should run through moc
set(KIT_MOC_SRCS
)

# UI files
set(KIT_UI_FORMS
)

# Resources
set(KIT_resources
)


# Target libraries - See CMake/ctkFunctionGetTargetLibraries.cmake
# The following macro will read the target libraries from the file 'target_libraries.cmake'
ctkFunctionGetTargetLibraries(KIT_target_libraries)
  
set(KIT_target_libraries ${KIT_target_libraries} org_mydomain_testplugin)
message(STATUS "ctkFunctionGetTargetLibraries POST target libs: " ${KIT_target_libraries})

#ctkMacroBuildApp(
#  NAME ${PROJECT_NAME}
#  SRCS ${KIT_SRCS}
#  MOC_SRCS ${KIT_MOC_SRCS}
#  UI_FORMS ${KIT_UI_FORMS}
#  TARGET_LIBRARIES ${KIT_target_libraries}
#  RESOURCES ${KIT_resources}
#  )

add_executable(${PROJECT_NAME} ${KIT_SRCS})
target_link_libraries(${PROJECT_NAME} ${KIT_target_libraries})

