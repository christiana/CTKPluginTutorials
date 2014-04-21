set(APPS
  UseCTKPlugin
  PluginBrowser
)

foreach(app ${APPS})
  option(BUILD_APP_${app} "Build the ${app} application" ON)
  add_subdirectory(${app})
endforeach()
