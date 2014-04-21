/*
 * PluginFrameworkManager.h
 *
 *  Created on: Apr 15, 2014
 *      Author: christiana
 */

#ifndef PLUGINFRAMEWORKMANAGER_H_
#define PLUGINFRAMEWORKMANAGER_H_

#include <QString>
#include <QObject>

#include "ctkPlugin.h"
#include "ctkPluginFramework_global.h"

typedef QSharedPointer<ctkPlugin> ctkPluginPtr;
typedef std::pair<QString,ctkPluginPtr> PluginData;

class ctkPluginFramework;
class ctkPluginFrameworkFactory;
typedef QSharedPointer<class PluginFrameworkManager> PluginFrameworkManagerPtr;

/** Manages a ctkPluginFramework instance.
 *
 * This is a customized version of the ctk singleton ctkPluginFrameworkLauncher.
 *
 */
class PluginFrameworkManager : public QObject
{
	Q_OBJECT
public:
	static PluginFrameworkManagerPtr create() { return PluginFrameworkManagerPtr(new PluginFrameworkManager()); }

	PluginFrameworkManager();
	~PluginFrameworkManager();

	void install(const QString& symbolicName);
	void uninstall(const QString& symbolicName);
	bool start(const QString& symbolicName, ctkPlugin::StartOptions options = ctkPlugin::START_ACTIVATION_POLICY);
	bool stop(const QString& symbolicName, ctkPlugin::StopOptions options = 0);
	bool start();
	bool stop();

	ctkPluginContext* getPluginContext();
	QSharedPointer<ctkPluginFramework> getPluginFramework();

	void addSearchPath(const QString& searchPath);
	void setSearchPaths(const QStringList& searchPath);
	QStringList getSearchPaths() const;
	QStringList getPluginSymbolicNames();
	QSharedPointer<ctkPlugin> getInstalledPluginFromSymbolicName(QString symbolicName);

signals:
	void pluginPoolChanged();

private:
	QString getPluginPath(const QString& symbolicName);
	QStringList getPluginSymbolicNames(const QString& searchPath);

	QScopedPointer<ctkPluginFrameworkFactory> mFrameworkFactory;
	QSharedPointer<ctkPluginFramework> mFramework;

	void initializeFramework();
	void startFramework();

	bool frameworkInitialized() const;
	bool frameworkStarted() const;

  QStringList mPluginSearchPaths;
  QStringList mPluginLibFilter;
};

#endif /* PLUGINFRAMEWORKMANAGER_H_ */
