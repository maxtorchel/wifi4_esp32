/*
 * WatchdogSettingsView.h
 *
 *  Created on: 16 мая 2017 г.
 *      Author: maxtor
 */

#ifndef CLASSES_VIEWS_WATCHDOGSETTINGSVIEW_H_
#define CLASSES_VIEWS_WATCHDOGSETTINGSVIEW_H_

#include "../../settings/Settings.h"
#include "../../Help.h"

class WatchdogSettingsView {
public:
	WatchdogSettingsView();

	String printPage();
private:
	Settings& _settings = Settings::Instance();
	Help _help;
};

#endif /* CLASSES_VIEWS_WATCHDOGSETTINGSVIEW_H_ */
