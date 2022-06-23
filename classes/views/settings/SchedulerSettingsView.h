/*
 * SchedulerSettingsView.h
 */

#ifndef CLASSES_VIEWS_SCHEDULERSETTINGSVIEW_H_
#define CLASSES_VIEWS_SCHEDULERSETTINGSVIEW_H_

#include "../../settings/Settings.h"
#include "../../equipment/Clock.h"

class SchedulerSettingsView {
public:
	SchedulerSettingsView();

	String printPage();
private:
	Settings& _settings = Settings::Instance();
	Clock _clock;
};

#endif /* CLASSES_VIEWS_SCHEDULERSETTINGSVIEW_H_ */
