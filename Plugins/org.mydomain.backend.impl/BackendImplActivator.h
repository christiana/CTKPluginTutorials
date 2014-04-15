/*
 * BackendImplActivator.h
 *
 *  Created on: Apr 15, 2014
 *      Author: christiana
 */

#ifndef BACKENDIMPLACTIVATOR_H_
#define BACKENDIMPLACTIVATOR_H_

#include <ctkPluginActivator.h>

class BackendInterface;

class BackendImplActivator :
  public QObject, public ctkPluginActivator
{
  Q_OBJECT
  Q_INTERFACES(ctkPluginActivator)

public:

  BackendImplActivator();
  ~BackendImplActivator();

  void start(ctkPluginContext* context);
  void stop(ctkPluginContext* context);

  static BackendImplActivator* getInstance();

  ctkPluginContext* getPluginContext() const;


private:

  static BackendImplActivator* instance;
  ctkPluginContext* context;

//  TestService* mTestService;
  BackendInterface* mBackendInterface;

}; // TestPluginActivator

#endif /* BACKENDIMPLACTIVATOR_H_ */
