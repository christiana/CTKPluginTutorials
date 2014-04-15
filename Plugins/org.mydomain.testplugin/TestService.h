/*
 * TestService.h
 *
 *  Created on: Apr 7, 2014
 *      Author: christiana
 */

#ifndef TESTSERVICE_H_
#define TESTSERVICE_H_

#include <QObject>
#include "org_mydomain_testplugin_Export.h"

class org_mydomain_testplugin_EXPORT TestService : public QObject
{
	  Q_OBJECT
public:
	virtual ~TestService();

	virtual QString getCustomString() const = 0;
};
//Q_DECLARE_INTERFACE(CATestService, "org.mydomain.serviceeventlistener.CATestService")
Q_DECLARE_INTERFACE(TestService, "TestService")

class TestStandalone
{
public:
	void printStuff();
	void printFromBackend();
};

#endif /* TESTSERVICE_H_ */
