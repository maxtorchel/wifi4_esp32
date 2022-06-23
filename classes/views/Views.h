/*
 * Views.h
 */

#ifndef CLASSES_VIEWS_VIEWS_H_
#define CLASSES_VIEWS_VIEWS_H_

#include "RefreshView.h"
#include "pages/StartView.h"
#include "pages/IndexView.h"
#include "pages/UpdateView.h"
#include "settings/NetworkSettingsView.h"
#include "settings/RelaysSettingsView.h"
#include "settings/SensorsSettingsView.h"
#include "settings/TriggersSettingsView.h"
#include "settings/BoardSettingsView.h"
#include "settings/WatchdogSettingsView.h"
#include "settings/SchedulerSettingsView.h"
#include "settings/ScreenSettingsView.h"

class Views {
public:
	Views();

	String getStartRedirect();
	String getStart();
	String getIndex();
	String getRefresh();
	String getNetworkSettings();
	String getRelaysSettings();
	String getSensorsSettings();
	String getTriggersSettings();
	String getBoardSettings();
	String getBoardI2cDevices();
	String getWatchdogSettings();
	String getSchedulerSettings();
	String getScreenSettings();
	String getNotFound();
	String getUpdate();
	String getUpdateSuccessRedirect();
	String getUpdateErrorRedirect();
	String getUploadRedirect();
private:
	Settings& _settings = Settings::Instance();
};

#endif /* CLASSES_VIEWS_VIEWS_H_ */
