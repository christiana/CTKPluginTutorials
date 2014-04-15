/*
 * TestServiceImpl.h
 *
 *  Created on: Apr 13, 2014
 *      Author: christiana
 */

#ifndef TESTSERVICEIMPL_H_
#define TESTSERVICEIMPL_H_


#include <QObject>
#include "TestService.h"
#include "org_mydomain_testplugin_Export.h"

class org_mydomain_testplugin_EXPORT TestServiceImpl : public TestService
{
	Q_INTERFACES(TestService)

public:
	TestServiceImpl();
	virtual ~TestServiceImpl();

	virtual QString getCustomString() const;
};


#endif /* TestServiceIMPL_H_ */
