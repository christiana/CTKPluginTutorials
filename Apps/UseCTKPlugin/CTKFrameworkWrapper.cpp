/*
 * CTKFrameworkWrapper.cpp
 *
 *  Created on: Apr 15, 2014
 *      Author: christiana
 */

#include "CTKFrameworkWrapper.h"


QSharedPointer<ctkPluginFramework> PluginManager::getInitializedFramework()
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

void PluginManager::installPlugins()
{
	QStringList pluginDirs;
#ifdef CMAKE_INTDIR
	pluginDirs << CTK_PLUGIN_DIR CMAKE_INTDIR "/";
#else
	pluginDirs << CTK_PLUGIN_DIR;
#endif

		pluginDirs.clear();
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

void PluginManager::installPluginFromFilename(QString filename)
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

ctkPluginContext* PluginManager::getPluginContext()
{
	return mFramework->getPluginContext();
}

QSharedPointer<ctkPlugin> PluginManager::getPluginFromSymbolicName(QString symbolicName)
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

void PluginManager::dumpInfoForPlugin(QSharedPointer<ctkPlugin> plugin)
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

void PluginManager::dumpInfoForService(ctkServiceReference ref)
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

ctkServiceReference PluginManager::getServiceReferenceFromClassName(QSharedPointer<ctkPlugin> plugin, QString name)
{
	  QList<ctkServiceReference> serviceRefs = plugin->getPluginContext()->getServiceReferences(name);
	  QListIterator<ctkServiceReference> it(serviceRefs);
	  if (it.hasNext())
		  return it.next();
	  return ctkServiceReference();
}

