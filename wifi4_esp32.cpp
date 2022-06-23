#include "wifi4_esp32.h"

#include <FS.h>
#include <SPIFFS.h>

Settings& settings = Settings::Instance();
Board board;
Relay relay;
Buttons buttons;
Triggers triggers;
Sensors sensors;
Scheduler scheduler;
RelayWebServer webServer;
Controller controller(webServer);

void setup()
{
	Wire.begin();
	Serial.begin(115200);
	if(!SPIFFS.begin()) {
		Serial.println(F("Filesystem start filed!"));
		return;
	}
	settings.loadConfig();
	buttons.startButtons();
	sensors.startSensors();
	controller.setupRoutes();
	webServer.start(buttons);
	relay.initRelays();
	board.begin();
}

void loop()
{
	buttons.handleButtons();
	webServer.server.handleClient();
	triggers.handleTriggers();
	scheduler.handleScheduler();
	sensors.handleSensors();
	relay.handleWatchdog();
	board.clock.ntpUpdate();
	board.screen.display();
}
