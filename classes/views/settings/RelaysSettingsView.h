/*
 * RelaysSettingsView.h
 */

#ifndef CLASSES_VIEWS_RELAYSSETTINGSVIEW_H_
#define CLASSES_VIEWS_RELAYSSETTINGSVIEW_H_

#include "../../settings/Settings.h"

class RelaysSettingsView {
public:
	RelaysSettingsView();

	String printPage();
private:
	Settings& _settings = Settings::Instance();
};

#endif /* CLASSES_VIEWS_RELAYSSETTINGSVIEW_H_ */
