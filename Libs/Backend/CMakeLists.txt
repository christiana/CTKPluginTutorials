project(CTKPluginTutorialLibBackend)

#> Include dirs
set(my_includes
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CTK_INCLUDE_DIRS} # CTK include dirs for enabled libraries
)
#>

include_directories(${my_includes})

#####


set(KIT_SRCS
  Backend.cpp
  PluginFrameworkManager.cpp
  PluginFrameworkManager.h
)

# Headers that should run through moc
set(KIT_MOC_SRCS
  Backend.h
)

# UI files
set(KIT_UI_FORMS
)

# Resources
set(KIT_resources
)

QT4_WRAP_CPP( KIT_SRCS ${KIT_MOC_SRCS} )

# Target libraries - See CMake/ctkFunctionGetTargetLibraries.cmake
# The following macro will read the target libraries from the file 'target_libraries.cmake'
ctkFunctionGetTargetLibraries(KIT_target_libraries)
  
#set(KIT_target_libraries ${KIT_target_libraries} org_mydomain_testplugin)
message(STATUS "Target libs for [${PROJECT_NAME}]: " ${KIT_target_libraries})

add_library(${PROJECT_NAME} ${KIT_SRCS})
target_link_libraries(${PROJECT_NAME} ${KIT_target_libraries})

