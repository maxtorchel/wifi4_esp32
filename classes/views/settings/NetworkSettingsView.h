/*
 * NetworkSettingsView.h
 */

#ifndef CLASSES_VIEWS_NETWORKSETTINGSVIEW_H_
#define CLASSES_VIEWS_NETWORKSETTINGSVIEW_H_

#include <WiFi.h>

#include "../../settings/Settings.h"
#include "../../Help.h"

class NetworkSettingsView {
public:
	NetworkSettingsView();

	const static byte REFRESH_COUNT = 1;

	String printPage();
	String printRefresh(byte element);
private:
	Settings& _settings = Settings::Instance();
	Help _help;
};

#endif /* CLASSES_VIEWS_NETWORKSETTINGSVIEW_H_ */
