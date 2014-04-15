/*
 * TestService.h
 *
 *  Created on: Apr 7, 2014
 *      Author: christiana
 */

#ifndef BACKEND_H_
#define BACKEND_H_

#include <QObject>


class Backend
{
public:
	void foo();
};


class BackendInterface : public QObject
{
	  Q_OBJECT
public:
	virtual ~BackendInterface();

	virtual QString getBackendString() const = 0;
};
Q_DECLARE_INTERFACE(BackendInterface, "BackendInterface")


#endif /* BACKEND_H_ */
