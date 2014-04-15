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

#include "CTKFrameworkWrapper.h"

int main(int argc, char** argv)
{
	QCoreApplication app(argc, argv);

	app.setOrganizationName("CustusX");
	app.setOrganizationDomain("custusx.org");
	app.setApplicationName("UseCTK_CA_Test");

	PluginManager pluginManager;
	pluginManager.getInitializedFramework();
	pluginManager.installPlugins();

	QSharedPointer<ctkPlugin> plugin = pluginManager.getPluginFromSymbolicName("org.mydomain.testplugin");
	pluginManager.dumpInfoForPlugin(plugin);

	qDebug() << "=================";
	qDebug() << "=================";
	qDebug() << "=================";

	ctkServiceReference ref2 = pluginManager.getServiceReferenceFromClassName(plugin, "ctkPluginGeneratorCodeModel");
	pluginManager.investigateService<ctkPluginGeneratorCodeModel>(ref2);
	qDebug() << "=================";

	ctkServiceReference ref = pluginManager.getServiceReferenceFromClassName(plugin, "TestService");
	pluginManager.investigateService<TestService>(ref);
	qDebug() << "=================";

	ctkPluginContext* context = ref.getPlugin()->getPluginContext();
	TestService* testService = context->getService<TestService>(ref);
	std::cout << "TestService: " << testService << std::endl;
	if (testService)
		qDebug() << testService->getCustomString();
	qDebug() << "=================";

	TestStandalone sl;
	sl.printStuff();

	//	return app.exec();
}

//> Main method
/*int main(int argc, char** argv)
{
  QCoreApplication app(argc, argv);

  app.setOrganizationName("MyOrganization");
  app.setOrganizationDomain("mydomain.org");
  app.setApplicationName("UseCTKPluginMain");

  ctkPluginFrameworkLauncher::start("org.mydomain.serviceeventlistener");
  ctkPluginFrameworkLauncher::start("org.commontk.eventadmin");
  ctkPluginFrameworkLauncher::start("org.mydomain.blarg");
  std::cout << "started" << std::endl;

  ctkPluginContext* pluginContext = ctkPluginFrameworkLauncher::getPluginContext();
  ctkServiceReference eventAdminRef = pluginContext->getServiceReference<ctkEventAdmin>();
  ctkEventAdmin* eventAdmin = pluginContext->getService<ctkEventAdmin>(eventAdminRef);

  eventAdmin->sendEvent(ctkEvent("mydomain/tutorial/CustomEvent"));

  QString path = "/Users/christiana/dev/working/CTKPluginTutorials";
  QStringList names = ctkPluginFrameworkLauncher::getPluginSymbolicNames(path);
  std::cout << names.join("\n").toStdString() << std::endl;

//  ctkServiceReference serviceEventListenerActivatorRef = pluginContext->getServiceReference<ServiceEventListenerActivator>();
//  ServiceEventListenerActivator* selA = pluginContext->getService<ServiceEventListenerActivator>(serviceEventListenerActivatorRef);

  return 0;
}*/
//>
