/*
 * CTKFrameworkWrapper.h
 *
 *  Created on: Apr 15, 2014
 *      Author: christiana
 */

#ifndef CTKFRAMEWORKWRAPPER_H_
#define CTKFRAMEWORKWRAPPER_H_

#include <QApplication>
#include <QDebug>
#include <QDirIterator>


#include <ctkPluginFrameworkLauncher.h>
#include <ctkPluginFrameworkFactory.h>
#include <ctkPluginFramework.h>
#include <ctkPluginException.h>
#include <ctkPluginContext.h>
#include <ctkConfig.h>
#include <iostream>

class PluginManager
{
public:
	QSharedPointer<ctkPluginFramework> getInitializedFramework();
	void installPlugins();
	void installPluginFromFilename(QString filename);

	ctkPluginContext* getPluginContext();
	QSharedPointer<ctkPlugin> getPluginFromSymbolicName(QString symbolicName);
	ctkServiceReference getServiceReferenceFromClassName(QSharedPointer<ctkPlugin> plugin, QString name);

	void dumpInfoForPlugin(QSharedPointer<ctkPlugin> plugin);
	void dumpInfoForService(ctkServiceReference ref);

	template <class T>
	void investigateService(ctkServiceReference ref)
	{
		if (!ref)
		{
			qDebug() << "service not valid";
			return;
		}
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


#endif /* CTKFRAMEWORKWRAPPER_H_ */
