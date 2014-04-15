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

class PluginManager
{
public:
	QSharedPointer<ctkPluginFramework> getInitializedFramework()
	{
		if (!mFramework)
		{
			QSharedPointer<ctkPluginFramework> framework = mFrameworkFactory.getFramework();

			try
			{
				framework->init();
			}
			catch (const ctkPluginException& exc)
			{
				qCritical() << "Failed to initialize the plug-in framework:" << exc;
				exit(1);
			}
			mFramework = framework;
		}
		return mFramework;
	}

	void installPlugins()
	{
		QStringList pluginDirs;
	#ifdef CMAKE_INTDIR
		pluginDirs << CTK_PLUGIN_DIR CMAKE_INTDIR "/";
	#else
		pluginDirs << CTK_PLUGIN_DIR;
	#endif

//		pluginDirs.clear();
		pluginDirs << "/Users/christiana/dev/working/CTKPluginTutorials/build_Debug/bin/plugins";

		std::cout << "pluginddirs: " << pluginDirs.join(", ").toStdString() << std::endl;

		QStringListIterator dirIt(pluginDirs);
		while (dirIt.hasNext())
		{
			QApplication::addLibraryPath(dirIt.next());
		}

		QStringList libFilter;
		libFilter << "*.dll" << "*.so" << "*.dylib";
		for (int i=0; i<pluginDirs.size(); ++i)
		{
			QDirIterator dirIter(pluginDirs.at(i), libFilter, QDir::Files);
			while(dirIter.hasNext())
			{
				this->installPluginFromFilename(dirIter.next());
			}
		}

		 mFramework->start(); //?????????????????

		 std::cout << "=== plugin install complete ===" << std::endl;
	}

	void installPluginFromFilename(QString filename)
	{
		QString libUrl = QUrl::fromLocalFile(filename).toString();
		std::cout << "liburl: " << libUrl.toStdString() << std::endl;

		try
		{
			QSharedPointer<ctkPlugin> plugin;
	//				std::cout << "installing " << libUrl.toStdString() << std::endl;
			plugin = mFramework->getPluginContext()->installPlugin(libUrl);
	//				std::cout << "installed " << std::endl;
			qDebug() << "symbolicname: " << plugin->getSymbolicName() << ", state: " << plugin->getState();
			plugin->start(ctkPlugin::START_TRANSIENT);
			std::cout << "Installed " << libUrl.toStdString() << std::endl;
			qDebug() << "state: " << plugin->getState();
		}
		catch (const ctkPluginException& e)
		{
			qCritical() << libUrl << ": " << e.what();
		}
		catch(const std::exception& e)
		{
			std::cout << libUrl.toStdString() << ": " << e.what() << std::endl;
		}
		catch(...)
		{
			std::cout << libUrl.toStdString() << ": unknown exc" << std::endl;
		}
	}

	ctkPluginContext* getPluginContext()
	{
		return mFramework->getPluginContext();
	}

	QSharedPointer<ctkPlugin> getPluginFromSymbolicName(QString symbolicName)
	{
		QList<QSharedPointer<ctkPlugin> > plugins;
		plugins = this->getPluginContext()->getPlugins();

		for (int i=0; i<plugins.size(); ++i)
		{
			if (plugins[i]->getSymbolicName()==symbolicName)
				return plugins[i];
		}

		return QSharedPointer<ctkPlugin>();
	}

	void dumpInfoForPlugin(QSharedPointer<ctkPlugin> plugin)
	{
		qDebug() << "=== dump info for plugin " << plugin->getSymbolicName();
		  QList<ctkServiceReference> serviceRefs = plugin->getPluginContext()->getServiceReferences("");
		  QListIterator<ctkServiceReference> it(serviceRefs);
		  while (it.hasNext())
		  {
		    ctkServiceReference ref(it.next());
			this->dumpInfoForService(ref);
		  }
		qDebug() << "=== end dump info for plugin " << plugin->getSymbolicName();
	}

	void dumpInfoForService(ctkServiceReference ref)
	{
		qDebug() << "Service from" << ref.getPlugin()->getSymbolicName() << ":" << ref.getPropertyKeys();
		qDebug() << "\tObject Classes:" << ref.getProperty(ctkPluginConstants::OBJECTCLASS).toStringList();
		qDebug() << "\tService ID:" << ref.getProperty(ctkPluginConstants::SERVICE_ID).toString();

		if (!ref)
			std::cout << "\tinvalid ref" << std::endl;
		QObject* genericService = ref.getPlugin()->getPluginContext()->getService(ref);
		if (genericService)
			std::cout << "\tfound service object " << genericService << std::endl;
	}

	ctkServiceReference getServiceReferenceFromClassName(QSharedPointer<ctkPlugin> plugin, QString name)
	{
		  QList<ctkServiceReference> serviceRefs = plugin->getPluginContext()->getServiceReferences(name);
		  QListIterator<ctkServiceReference> it(serviceRefs);
		  if (it.hasNext())
			  return it.next();
		  return ctkServiceReference();
	}

	template <class T>
	void investigateService(ctkServiceReference ref)
	{
		qDebug() << "Investigating service " << ref.getProperty(ctkPluginConstants::SERVICE_ID).toString();
		this->dumpInfoForService(ref);

		ctkPluginContext* context = ref.getPlugin()->getPluginContext();
	    if (!ref)
	    	std::cout << "invalid ref" << std::endl;
		QObject* genericService = context->getService(ref);
		if (genericService)
	    	std::cout << "found object " << genericService << std::endl;

		T* directService = dynamic_cast<T*>(genericService);
		std::cout << "downcastService: " << directService << std::endl;

		T* specificService = context->getService<T>(ref);
		std::cout << "specificService: " << specificService << std::endl;
	}


private:
	ctkPluginFrameworkFactory mFrameworkFactory;
	QSharedPointer<ctkPluginFramework> mFramework;
};


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
/*
	try
	{
		ctkPluginContext* pluginContext = plugin->getPluginContext();
		std::cout << "obtaining testService..." << std::endl;
//		ctkServiceReference testServiceRef = pluginContext->getServiceReference<TestService>();
		ctkServiceReference testServiceRef = pluginContext->getServiceReference("org.mydomain.serviceeventlistener.TestService");
		if (testServiceRef)
		{
			std::cout << "got ref" << std::endl;
			TestService* testService = pluginContext->getService<TestService>(testServiceRef);
			std::cout << "testService: " << testService << std::endl;
			testService->getCustomString();
		}
		else
		{
			std::cout << "got invalid ref" << std::endl;
		}
	}
	catch(const std::exception& e)
	{
		std::cout  << "got exception: " << e.what() << std::endl;
	}
*/

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
