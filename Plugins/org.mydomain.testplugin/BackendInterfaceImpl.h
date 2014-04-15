/*
 * BackendInterfaceImpl.h
 *
 *  Created on: Apr 15, 2014
 *      Author: christiana
 */

#ifndef BACKENDINTERFACEIMPL_H_
#define BACKENDINTERFACEIMPL_H_

#include <QObject>
#include "Backend.h"
#include "org_mydomain_testplugin_Export.h"

class org_mydomain_testplugin_EXPORT BackendInterfaceImpl : public BackendInterface
{
	Q_INTERFACES(BackendInterface)

public:
	BackendInterfaceImpl();
	virtual ~BackendInterfaceImpl();

	virtual QString getBackendString() const;
};



#endif /* BACKENDINTERFACEIMPL_H_ */
