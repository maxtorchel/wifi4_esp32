/*
 * Views.cpp
 */

#include "Views.h"

Views::Views(){}

String Views::getStart()
{
	StartView view;
	return view.printPage();
}
String Views::getStartRedirect()
{
	StartView view;
	return view.printRedirect();
}

String Views::getIndex()
{
	IndexView view;
	return view.printPage();
}

String Views::getRefresh()
{
	RefreshView view;
	return view.printPage();
}

String Views::getNetworkSettings()
{
	NetworkSettingsView view;
	return view.printPage();
}

String Views::getRelaysSettings()
{
	RelaysSettingsView view;
	return view.printPage();
}

String Views::getSensorsSettings()
{
	SensorsSettingsView view;
	return view.printPage();
}

String Views::getTriggersSettings()
{
	TriggersSettingsView view;
	return view.printPage();
}

String Views::getBoardSettings()
{
	BoardSettingsView view;
	return view.printPage();
}
String Views::getBoardI2cDevices()
{
	BoardSettingsView view;
	return view.printI2cDevices();
}

String Views::getWatchdogSettings()
{
	WatchdogSettingsView view;
	return view.printPage();
}

String Views::getSchedulerSettings()
{
	SchedulerSettingsView view;
	return view.printPage();
}

String Views::getScreenSettings()
{
	ScreenSettingsView view;
	return view.printPage();
}

String Views::getNotFound()
{
	return F("404 Not Found");
}

String Views::getUpdate()
{
	UpdateView view;
	return view.printPage();
}
String Views::getUpdateSuccessRedirect()
{
	UpdateView view;
	return view.printSuccessRedirect();
}
String Views::getUpdateErrorRedirect()
{
	UpdateView view;
	return view.printErrorRedirect();
}
String Views::getUploadRedirect()
{
	UpdateView view;
	return view.printUploadRedirect();
}
