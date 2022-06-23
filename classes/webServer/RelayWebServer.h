/*
 * RelayWebServer.h
 */

#ifndef CLASSES_RELAYWEBSERVER_H_
#define CLASSES_RELAYWEBSERVER_H_

#include <WebServer.h>

#include "../settings/Settings.h"
#include "../log/Log.h"
#include "../Help.h"
#include "../equipment/Buttons.h"
#include "../views/Views.h"

class RelayWebServer {
public:
	RelayWebServer();

	WebServer server;
	Views views;

	void start(Buttons buttons);
	bool checkLocalMainScripts();

private:
	Settings& _settings = Settings::Instance();
	Log _log;
	Help _help;
};

#endif /* CLASSES_RELAYWEBSERVER_H_ */
