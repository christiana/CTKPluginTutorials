/*
 * CTKFrameworkWrapper.cpp
 *
 *  Created on: Apr 15, 2014
 *      Author: christiana
 */

#include "CTKFrameworkWrapper.h"

PluginManager::PluginManager()
{
	mManager = PluginFrameworkManager::create();
	mManager->addSearchPath(CTK_PLUGIN_DIR);
	mManager->addSearchPath(qApp->applicationDirPath()+"/plugins");

	qDebug() << " * Pluginddirs: " << mManager->getSearchPaths().join(", ");

	qDebug() << "All available plugins: \n  " << mManager->getPluginSymbolicNames().join("\n  ");
}

void PluginManager::installPlugin(QString name)
{
	mManager->install(name);

	if (!mManager->getInstalledPluginFromSymbolicName(name))
		return;

	mManager->start(name, ctkPlugin::START_TRANSIENT);

	qDebug() << " * Started plugin " << name;
}

void PluginManager::installPlugins()
{
	QStringList names = mManager->getPluginSymbolicNames();

	for (int i=0; i<names.size(); ++i)
	{
		this->installPlugin(names[i]);
	}
	 std::cout << "=== plugin install+start complete ===" << std::endl;
}


ctkPluginContext* PluginManager::getPluginContext()
{
	return mManager->getPluginContext();
}

QSharedPointer<ctkPlugin> PluginManager::getPluginFromSymbolicName(QString name)
{
	return mManager->getInstalledPluginFromSymbolicName(name);
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

