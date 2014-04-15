/*
 * BackendImplActivator.cpp
 *
 *  Created on: Apr 15, 2014
 *      Author: christiana
 */

#include "BackendImplActivator.h"

#include <QtPlugin>
#include <iostream>
#include "BackendInterfaceImpl2.h"

BackendImplActivator* BackendImplActivator::instance = 0;

BackendImplActivator::BackendImplActivator()
  : context(0)
{
//	int* val = 0;
//	*val = 0;
	std::cout << "Created BackendImplActivator" << std::endl;
}

BackendImplActivator::~BackendImplActivator()
{

}

void BackendImplActivator::start(ctkPluginContext* context)
{
	std::cout << "Started BackendImplActivator" << std::endl;
  instance = this;
  this->context = context;
/*
  mTestService = new TestServiceImpl();
  std::cout << "create TestServiceImpl object " << mTestService << std::endl;
//  context->registerService<TestService>(mTestService);
//  context->registerService("TestService", mTestService);
  context->registerService(QStringList("TestService"), mTestService);
*/
  mBackendInterface = new BackendInterfaceImpl2();
  std::cout << "create BackendInterfaceImpl2 object " << mBackendInterface << std::endl;
  context->registerService(QStringList("BackendInterface"), mBackendInterface);

}

void BackendImplActivator::stop(ctkPluginContext* context)
{
//	delete mTestService;
	std::cout << "Stopped BackendImplActivator" << std::endl;
  Q_UNUSED(context)
}

BackendImplActivator* BackendImplActivator::getInstance()
{
  return instance;
}

ctkPluginContext* BackendImplActivator::getPluginContext() const
{
  return context;
}

//Q_EXPORT_PLUGIN2(org_mydomain_testplugin, BackendImplActivator)
Q_EXPORT_PLUGIN2(BackendImplActivator_irrelevant_string, BackendImplActivator)


