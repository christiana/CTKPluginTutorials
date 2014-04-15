project(UseCTKPluginMain)

include(${CTK_PLUGIN_USE_FILE})

#message(STATUS "org_commontk_plugingenerator_core_INCLUDE_DIRS: " ${org_commontk_plugingenerator_core_INCLUDE_DIRS})

#> Include dirs
set(my_includes
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CTK_INCLUDE_DIRS} # CTK include dirs for enabled libraries
  ${CTKPluginTutorials_BINARY_DIR}/Plugins/org.mydomain.testplugin
  ${CTKPluginTutorials_SOURCE_DIR}/Plugins/org.mydomain.testplugin
  ${org_commontk_plugingenerator_core_INCLUDE_DIRS}
  ${CTKPluginTutorials_SOURCE_DIR}/Libs/Backend
)
#>

include_directories(${my_includes})


set(KIT_SRCS
  UseCTKPluginMain.cpp
  CTKFrameworkWrapper.cpp
  CTKFrameworkWrapper.h
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
message(STATUS "Target libs for [${PROJECT_NAME}]: " ${KIT_target_libraries})

add_executable(${PROJECT_NAME} ${KIT_SRCS})
target_link_libraries(${PROJECT_NAME} ${KIT_target_libraries})

