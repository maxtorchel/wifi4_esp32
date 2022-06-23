/*
 * SensorsSettingsView.h
 */

#ifndef CLASSES_VIEWS_SENSORSSETTINGSVIEW_H_
#define CLASSES_VIEWS_SENSORSSETTINGSVIEW_H_

#include "../../equipment/Board.h"
#include "../../settings/Settings.h"

class SensorsSettingsView {
public:
	SensorsSettingsView();

	String printPage();
private:
	Settings& _settings = Settings::Instance();
	Board _board;
};

#endif /* CLASSES_VIEWS_SENSORSSETTINGSVIEW_H_ */
