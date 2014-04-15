/*=============================================================================

  Library: CTK

  Copyright (c) DKFZ

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

=============================================================================*/


#include "TestPluginActivator_p.h"
#include <QtPlugin>
#include <iostream>
#include "TestServiceImpl.h"

TestPluginActivator* TestPluginActivator::instance = 0;

TestPluginActivator::TestPluginActivator()
  : context(0)
{
//	int* val = 0;
//	*val = 0;
	std::cout << "Created TestPluginActivator" << std::endl;
}

TestPluginActivator::~TestPluginActivator()
{
  
}

void TestPluginActivator::start(ctkPluginContext* context)
{
	std::cout << "Started TestPluginActivator" << std::endl;
  instance = this;
  this->context = context;

  mTestService = new TestServiceImpl();
  std::cout << "create TestServiceImpl object " << mTestService << std::endl;
//  context->registerService<TestService>(mTestService);
//  context->registerService("TestService", mTestService);
  context->registerService(QStringList("TestService"), mTestService);

}

void TestPluginActivator::stop(ctkPluginContext* context)
{
	delete mTestService;
	std::cout << "Stopped TestPluginActivator" << std::endl;
  Q_UNUSED(context)
}

TestPluginActivator* TestPluginActivator::getInstance()
{
  return instance;
}

ctkPluginContext* TestPluginActivator::getPluginContext() const
{
  return context;
}

//Q_EXPORT_PLUGIN2(org_mydomain_testplugin, TestPluginActivator)
Q_EXPORT_PLUGIN2(TestPluginActivator_irrelevant_string, TestPluginActivator)


