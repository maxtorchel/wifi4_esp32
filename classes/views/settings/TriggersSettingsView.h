/*
 * TriggersSettingsView.h
 */

#ifndef CLASSES_VIEWS_TRIGGERSSETTINGSVIEW_H_
#define CLASSES_VIEWS_TRIGGERSSETTINGSVIEW_H_

#include "../../settings/Settings.h"

class TriggersSettingsView {
public:
	TriggersSettingsView();

	String printPage();
private:
	Settings& _settings = Settings::Instance();
};

#endif /* CLASSES_VIEWS_TRIGGERSSETTINGSVIEW_H_ */
