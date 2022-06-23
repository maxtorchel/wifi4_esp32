/*
 * Controller.h
 */

#ifndef CLASSES_CONTROLLER_H_
#define CLASSES_CONTROLLER_H_

#include <ArduinoJson.h>

#include "../equipment/Board.h"
#include "../log/Log.h"
#include "RelayWebServer.h"

class Controller {
public:
	Controller(RelayWebServer& webServer);

	void setupRoutes();
	void doJob();
private:
	Settings& _settings = Settings::Instance();
	RelayWebServer& _webServer;
	Board _board;
	Log _log;

	void handleStartConfig();
	void handleLogin();
	void handleUpdateFirmware();
	void handleUpdateSettings();
	void handleFileUpload(String name);
	String getContentType(String name);
};

#endif /* CLASSES_CONTROLLER_H_ */
