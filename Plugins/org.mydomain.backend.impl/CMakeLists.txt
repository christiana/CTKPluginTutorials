project(org_mydomain_backend_impl)

set(PLUGIN_export_directive "${PROJECT_NAME}_EXPORT")

include_directories(${CTKPluginTutorials_SOURCE_DIR}/Libs/Backend)

set(PLUGIN_SRCS
  BackendImplActivator.cpp
  BackendInterfaceImpl2.cpp
)

# Files which should be processed by Qts moc
set(PLUGIN_MOC_SRCS
  BackendImplActivator.h
  BackendInterfaceImpl2.h
)

# Qt Designer files which should be processed by Qts uic
set(PLUGIN_UI_FORMS
)

# QRC Files which should be compiled into the plugin
set(PLUGIN_resources
)

#message(STATUS "ctkFunctionGetTargetLibraries PRE target libs pre: " ${PLUGIN_target_libraries})
#Compute the plugin dependencies
ctkFunctionGetTargetLibraries(PLUGIN_target_libraries)
set(PLUGIN_target_libraries ${PLUGIN_target_libraries} CTKPluginTutorialLibBackend)
message(STATUS "Target libs for [${PROJECT_NAME}]: " ${PLUGIN_target_libraries})


ctkMacroBuildPlugin(
  NAME ${PROJECT_NAME}
  EXPORT_DIRECTIVE ${PLUGIN_export_directive}
  SRCS ${PLUGIN_SRCS}
  MOC_SRCS ${PLUGIN_MOC_SRCS}
  UI_FORMS ${PLUGIN_UI_FORMS}
  RESOURCES ${PLUGIN_resources}
  TARGET_LIBRARIES ${PLUGIN_target_libraries}
)
