/*
 * RelayWebServer.cpp
 */

#include <FS.h>
#include <SPIFFS.h>

#include "RelayWebServer.h"

RelayWebServer::RelayWebServer() {}

void RelayWebServer::start(Buttons buttons)
{
	//start WiFi
	if(_settings.config.ap.value==1){
		WiFi.mode(WIFI_AP);
		WiFi.softAPConfig(_settings.config.ip.value, _settings.config.gateway.value, _settings.config.subnet.value);
		if(!WiFi.softAP(_settings.config.ssid.value, _settings.config.wifi_password.value)){
		    Serial.println(F("WiFi AP failed. (Password too short?)"));
		    return;
	    }else{
	    	Serial.println(F("WiFi AP started."));
	    	Serial.println(WiFi.softAPIP()); // Print the IP address
	    	_log.write(F("board.log"), "Server started (ip: "+WiFi.softAPIP().toString()+").");
	    }
	}else{
		WiFi.mode(WIFI_STA);
		if(_settings.config.dhcp.value!=1)
			WiFi.config(_settings.config.ip.value, _settings.config.gateway.value, _settings.config.subnet.value, _settings.config.dns1.value, _settings.config.dns2.value);

		WiFi.disconnect(); //fix issue when status always WL_DISCONNECTED
		WiFi.begin(_settings.config.ssid.value, _settings.config.wifi_password.value);

		while (!WiFi.isConnected()) {
			delay(500);
			Serial.print(F("."));
			buttons.handleButtons();
		}
		Serial.println();
		Serial.println(F("WiFi connected."));
		Serial.println(WiFi.localIP()); // Print the IP address
		_log.write(F("board.log"), "Server started (ip: "+WiFi.localIP().toString()+").");
	}

	// Start the server
	server.begin(_settings.config.port.value);
	Serial.println(F("Server started."));
}

bool RelayWebServer::checkLocalMainScripts()
{
	return SPIFFS.exists(F("/jquery.js"))
			&& SPIFFS.exists(F("/bootstrap.js"))
			&& SPIFFS.exists(F("/bootstrap-editable.js"))
			&& SPIFFS.exists(F("/jquery-mask.js"))
			&& SPIFFS.exists(F("/bootstrap.css"))
			&& SPIFFS.exists(F("/bootstrap-editable.css"));
}
