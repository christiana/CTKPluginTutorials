/*
 * BackendInterfaceImpl2.h
 *
 *  Created on: Apr 15, 2014
 *      Author: christiana
 */

#ifndef BACKENDINTERFACEIMPL2_H_
#define BACKENDINTERFACEIMPL2_H_

#include <QObject>
#include "Backend.h"
#include "org_mydomain_backend_impl_Export.h"

class org_mydomain_backend_impl_EXPORT BackendInterfaceImpl2 : public BackendInterface
{
	Q_INTERFACES(BackendInterface)

public:
	BackendInterfaceImpl2();
	virtual ~BackendInterfaceImpl2();

	virtual QString getBackendString() const;
};

#endif /* BACKENDINTERFACEIMPL2_H_ */
