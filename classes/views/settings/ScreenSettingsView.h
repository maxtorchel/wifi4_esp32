/*
 * ScreenSettingsView.h
 */

#ifndef CLASSES_VIEWS_SCREENSETTINGSVIEW_H_
#define CLASSES_VIEWS_SCREENSETTINGSVIEW_H_

#include "../../settings/Settings.h"
#include "../../equipment/Screen.h"
#include "../../equipment/Clock.h"

class ScreenSettingsView {
public:
	ScreenSettingsView();

	String printPage();
private:
	Settings& _settings = Settings::Instance();
	Screen _screen;
	Clock _clock;
};

#endif /* CLASSES_VIEWS_SCREENSETTINGSVIEW_H_ */
