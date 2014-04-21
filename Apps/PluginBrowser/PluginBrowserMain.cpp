#include <QApplication>
#include <QDebug>

#include <ctkPluginFrameworkLauncher.h>
#include <ctkPluginFrameworkFactory.h>
#include <ctkPluginFramework.h>
#include <ctkPluginException.h>
#include <ctkPluginContext.h>
#include <ctkConfig.h>
#include <iostream>

#include <service/event/ctkEventAdmin.h>

#include <QDirIterator>
#include "TestService.h"
#include "ctkPluginGeneratorCodeModel.h"

#include "PluginFrameworkManager.h"
#include "Backend.h"
#include "ctkPluginBrowser.h"


int main(int argc, char** argv)
{
	QApplication app(argc, argv);

	app.setOrganizationName("CustusX");
	app.setOrganizationDomain("custusx.org");
	app.setApplicationName("PluginBrowser2");

	PluginFrameworkManagerPtr manager = PluginFrameworkManager::create();

	manager->addSearchPath(CTK_PLUGIN_DIR);
	manager->addSearchPath(qApp->applicationDirPath()+"/plugins");

	qDebug() << " * Pluginddirs: " << manager->getSearchPaths().join(", ");
	qDebug() << "All available plugins: \n  " << manager->getPluginSymbolicNames().join("\n  ");

	manager->start();

//	QStringList names = manager->getPluginSymbolicNames();
//	for (int i=0; i<names.size(); ++i)
//	{
//		QString name = names[i];
//		manager->install(name);
//		if (!manager->getInstalledPluginFromSymbolicName(name))
//			continue;
//		manager->start(name, ctkPlugin::START_TRANSIENT);
//		qDebug() << " * Started plugin " << name;
//	}

	ctkPluginBrowser browser(manager);
	browser.show();

#ifdef __APPLE__ // needed on mac for bringing to front: does the opposite on linux
	browser.activateWindow();
#endif
	browser.raise();


	return app.exec();
}
