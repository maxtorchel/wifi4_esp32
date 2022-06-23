/*
 * Controller.cpp
 */

#include <FS.h>
#include <SPIFFS.h>
#include <Update.h>

#include "Controller.h"

Controller::Controller(RelayWebServer& webServer) : _webServer(webServer) {}

void Controller::doJob()
{
	//Relay
	if(_webServer.server.hasArg("switch") && _webServer.server.hasArg("relay"))
		_board.relay.switchRelay(_webServer.server.arg("relay").toInt(),_webServer.server.arg("switch").toInt());
	else if(_webServer.server.hasArg("relay_enabled") && _webServer.server.hasArg("relay"))
		_settings.setRelayEnabled(_webServer.server.arg("relay").toInt(),_webServer.server.arg("relay_enabled").toInt(), true);
	else if(_webServer.server.hasArg("relay_pin") && _webServer.server.hasArg("relay"))
		_settings.setRelayPin(_webServer.server.arg("relay").toInt(),_webServer.server.arg("relay_pin").toInt(), true);
	else if(_webServer.server.hasArg("relay_name") && _webServer.server.hasArg("relay"))
		_settings.setRelayName(_webServer.server.arg("relay").toInt(),_webServer.server.arg("relay_name"), true);
	else if(_webServer.server.hasArg("relay_inverse") && _webServer.server.hasArg("relay"))
		_settings.setRelayInverse(_webServer.server.arg("relay").toInt(), _webServer.server.arg("relay_inverse").toInt(), true);
	else if(_webServer.server.hasArg("relay_remember") && _webServer.server.hasArg("relay"))
		_settings.setRelayRememberState(_webServer.server.arg("relay").toInt(), _webServer.server.arg("relay_remember").toInt(), true);
	else if(_webServer.server.hasArg("relay_watchdog") && _webServer.server.hasArg("relay"))
		_settings.setRelayWatchdog(_webServer.server.arg("relay").toInt(), _webServer.server.arg("relay_watchdog").toInt(), true);
	else if(_webServer.server.hasArg("relay_host") && _webServer.server.hasArg("relay"))
		_settings.setRelayHost(_webServer.server.arg("relay").toInt(), _webServer.server.arg("relay_host"), true);
	else if(_webServer.server.hasArg("watchdog_host"))
		_settings.setWatchdogHost(_webServer.server.arg("watchdog_host"), true);
	else if(_webServer.server.hasArg("watchdog_interval"))
		_settings.setWatchdogInterval(_webServer.server.arg("watchdog_interval").toInt(), true);
	else if(_webServer.server.hasArg("watchdog_try_count"))
		_settings.setWatchdogTryCount(_webServer.server.arg("watchdog_try_count").toInt(), true);
	//Sensor
	else if(_webServer.server.hasArg("sensor_enabled") && _webServer.server.hasArg("sensor"))
		_settings.setSensorEnabled(_webServer.server.arg("sensor").toInt(),_webServer.server.arg("sensor_enabled").toInt(), true);
	else if(_webServer.server.hasArg("sensor_type") && _webServer.server.hasArg("sensor"))
		_settings.setSensorType(_webServer.server.arg("sensor").toInt(), _webServer.server.arg("sensor_type").toInt(), true);
	else if(_webServer.server.hasArg("sensor_pin") && _webServer.server.hasArg("sensor"))
		_settings.setSensorPin(_webServer.server.arg("sensor").toInt(),_webServer.server.arg("sensor_pin").toInt(), true);
	else if(_webServer.server.hasArg("sensor_name") && _webServer.server.hasArg("sensor"))
		_settings.setSensorName(_webServer.server.arg("sensor").toInt(), _webServer.server.arg("sensor_name"), true);
	else if(_webServer.server.hasArg("sensor_group") && _webServer.server.hasArg("sensor"))
		_settings.setSensorGroup(_webServer.server.arg("sensor").toInt(), _webServer.server.arg("sensor_group"), true);
	else if(_webServer.server.hasArg("sensor_log_interval") && _webServer.server.hasArg("sensor"))
		_settings.setSensorLogInterval(_webServer.server.arg("sensor").toInt(), _webServer.server.arg("sensor_log_interval").toInt(), true);
	else if(_webServer.server.hasArg("sensor_host") && _webServer.server.hasArg("sensor"))
		_settings.setSensorHost(_webServer.server.arg("sensor").toInt(), _webServer.server.arg("sensor_host"), true);
	//Trigger
	else if(_webServer.server.hasArg("trigger_enabled") && _webServer.server.hasArg("trigger"))
		_settings.setTriggerEnabled(_webServer.server.arg("trigger").toInt(),_webServer.server.arg("trigger_enabled").toInt(), true);
	else if(_webServer.server.hasArg("trigger_name") && _webServer.server.hasArg("trigger"))
		_settings.setTriggerName(_webServer.server.arg("trigger").toInt(), _webServer.server.arg("trigger_name"), true);
	else if(_webServer.server.hasArg("trigger_sensor") && _webServer.server.hasArg("trigger"))
		_settings.setTriggerSensor(_webServer.server.arg("trigger").toInt(), _webServer.server.arg("trigger_sensor").toInt(), true);
	else if(_webServer.server.hasArg("trigger_target") && _webServer.server.hasArg("trigger")){
		DynamicJsonBuffer jsonBuffer;
		JsonObject& root = jsonBuffer.parseObject(_webServer.server.arg("trigger_target"));
		_settings.setTriggerTarget(_webServer.server.arg("trigger").toInt(), root["type"].as<unsigned int>(), root["number"].as<unsigned int>(), true);
	}else if(_webServer.server.hasArg("trigger_on_value") && _webServer.server.hasArg("trigger"))
		_settings.setTriggerOnValue(_webServer.server.arg("trigger").toInt(), _webServer.server.arg("trigger_on_value").toFloat(), true);
	else if(_webServer.server.hasArg("trigger_off_value") && _webServer.server.hasArg("trigger"))
		_settings.setTriggerOffValue(_webServer.server.arg("trigger").toInt(), _webServer.server.arg("trigger_off_value").toFloat(), true);
	//Scheduler
	else if(_webServer.server.hasArg("schedule_enabled") && _webServer.server.hasArg("schedule"))
		_settings.setScheduleEnabled(_webServer.server.arg("schedule").toInt(),_webServer.server.arg("schedule_enabled").toInt(), true);
	else if(_webServer.server.hasArg("schedule_name") && _webServer.server.hasArg("schedule"))
		_settings.setScheduleName(_webServer.server.arg("schedule").toInt(), _webServer.server.arg("schedule_name"), true);
	else if(_webServer.server.hasArg("schedule_relay") && _webServer.server.hasArg("schedule"))
		_settings.setScheduleRelay(_webServer.server.arg("schedule").toInt(), _webServer.server.arg("schedule_relay").toInt(), true);
	else if(_webServer.server.hasArg("schedule_start_time") && _webServer.server.hasArg("schedule"))
		_settings.setScheduleStartTime(_webServer.server.arg("schedule").toInt(), _webServer.server.arg("schedule_start_time").toInt(), true);
	else if(_webServer.server.hasArg("schedule_on_seconds") && _webServer.server.hasArg("schedule"))
		_settings.setScheduleOnSeconds(_webServer.server.arg("schedule").toInt(), _webServer.server.arg("schedule_on_seconds").toInt(), true);
	else if(_webServer.server.hasArg("schedule_off_seconds") && _webServer.server.hasArg("schedule"))
		_settings.setScheduleOffSeconds(_webServer.server.arg("schedule").toInt(), _webServer.server.arg("schedule_off_seconds").toInt(), true);
	else if(_webServer.server.hasArg("schedule_repeat") && _webServer.server.hasArg("schedule"))
		_settings.setScheduleRepeat(_webServer.server.arg("schedule").toInt(), _webServer.server.arg("schedule_repeat").toInt(), true);
	//Screen
	else if(_webServer.server.hasArg("screen_enabled") && _webServer.server.hasArg("screen"))
		_settings.setScreenEnabled(_webServer.server.arg("screen").toInt(),_webServer.server.arg("screen_enabled").toInt(), true);
	else if(_webServer.server.hasArg("screen_name") && _webServer.server.hasArg("screen"))
		_settings.setScreenName(_webServer.server.arg("screen").toInt(), _webServer.server.arg("screen_name"), true);
	else if(_webServer.server.hasArg("screen_source") && _webServer.server.hasArg("screen")){
		DynamicJsonBuffer jsonBuffer;
		JsonObject& root = jsonBuffer.parseObject(_webServer.server.arg("screen_source"));
		_settings.setScreenSource(_webServer.server.arg("screen").toInt(), root["type"].as<unsigned int>(), root["number"].as<unsigned int>(), true);
	}else if(_webServer.server.hasArg("screen_position") && _webServer.server.hasArg("screen"))
		_settings.setScreenPosition(_webServer.server.arg("screen").toInt(),_webServer.server.arg("screen_position").toInt(), true);
	//Board
	else if(_webServer.server.hasArg("reboot"))
		_board.reboot(1000);
	else if(_webServer.server.hasArg("reset"))
		_board.reset(1000);
	else if(_webServer.server.hasArg("factory_reset"))
		_board.factoryReset(1000);
	else if(_webServer.server.hasArg("datetime"))
		_board.clock.setDateTime(_webServer.server.arg("datetime").toInt());
	//Network
	else if(_webServer.server.hasArg("port"))
		_settings.setPort(_webServer.server.arg("port").toInt(), true);
	else if(_webServer.server.hasArg("dhcp"))
		_settings.setDhcp(_webServer.server.arg("dhcp").toInt(), true);
	else if(_webServer.server.hasArg("ap"))
		_settings.setAp(_webServer.server.arg("ap").toInt(), true);
	else if(_webServer.server.hasArg("ip"))
		_settings.setIp(_webServer.server.arg("ip"), true);
	else if(_webServer.server.hasArg("gateway"))
		_settings.setGateway(_webServer.server.arg("gateway"), true);
	else if(_webServer.server.hasArg("subnet"))
		_settings.setSubnet(_webServer.server.arg("subnet"), true);
	else if(_webServer.server.hasArg("dns1"))
		_settings.setDns1(_webServer.server.arg("dns1"), true);
	else if(_webServer.server.hasArg("dns2"))
		_settings.setDns2(_webServer.server.arg("dns2"), true);
	else if(_webServer.server.hasArg("login"))
		_settings.setLogin(_webServer.server.arg("login"), true);
	else if(_webServer.server.hasArg("password"))
		_settings.setPassword(_webServer.server.arg("password"), true);
	else if(_webServer.server.hasArg("ssid"))
		_settings.setSsid(_webServer.server.arg("ssid"), true);
	else if(_webServer.server.hasArg("wifi_password"))
		_settings.setWifiPassword(_webServer.server.arg("wifi_password"), true);
	//NTP
	else if(_webServer.server.hasArg("ntp"))
		_settings.setNtp(_webServer.server.arg("ntp").toInt(), true);
	else if(_webServer.server.hasArg("ntp_offset"))
		_board.clock.setNtpOffset(_webServer.server.arg("ntp_offset").toInt());
	else if(_webServer.server.hasArg("ntp_update_interval"))
		_board.clock.setNtpUpdateInterval(_webServer.server.arg("ntp_update_interval").toInt());
	else if(_webServer.server.hasArg("ntp_update"))
		_board.clock.ntpUpdate();
}

void Controller::handleStartConfig()
{
	if(_webServer.server.hasArg("login"))
		_settings.setLogin(_webServer.server.arg("login"), false);
	if(_webServer.server.hasArg("password"))
		_settings.setPassword(_webServer.server.arg("password"), false);
	if(_webServer.server.hasArg("ssid"))
		_settings.setSsid(_webServer.server.arg("ssid"), false);
	if(_webServer.server.hasArg("wifi_password"))
		_settings.setWifiPassword(_webServer.server.arg("wifi_password"), false);
	if(_webServer.server.hasArg("ip"))
		_settings.setIp(_webServer.server.arg("ip"), false);
	if(_webServer.server.hasArg("gateway"))
		_settings.setGateway(_webServer.server.arg("gateway"), false);
	if(_webServer.server.hasArg("subnet"))
		_settings.setSubnet(_webServer.server.arg("subnet"), false);
	if(!_webServer.server.hasArg("ap"))
		_settings.setAp(0, false);
	if(_webServer.server.args()>0){
		_settings.setStart(0, false);
		_settings.saveConfig();
	}
}
void Controller::handleLogin()
{
	if(!_webServer.server.authenticate(_settings.config.login.value, _settings.config.password.value))
	      return _webServer.server.requestAuthentication();
}

void Controller::handleUpdateFirmware()
{
	HTTPUpload& upload = _webServer.server.upload();
	if(upload.status == UPLOAD_FILE_START){
		Serial.setDebugOutput(true);
		Serial.printf("Update: %s\n", upload.filename.c_str());
		uint32_t maxSketchSpace = (ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000;
		if(!Update.begin(maxSketchSpace)){//start with max available size
		  Update.printError(Serial);
		}
	} else if(upload.status == UPLOAD_FILE_WRITE){
		if(Update.write(upload.buf, upload.currentSize) != upload.currentSize){
		  Update.printError(Serial);
		}
	} else if(upload.status == UPLOAD_FILE_END){
		if(Update.end(true)){ //true to set the size to the current progress
		  Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
		} else {
		  Update.printError(Serial);
		}
		Serial.setDebugOutput(false);
	}
	yield();
}
void Controller::handleUpdateSettings()
{
	HTTPUpload& upload = _webServer.server.upload();
	static String json = "";
	if(upload.status == UPLOAD_FILE_START){
	} else if(upload.status == UPLOAD_FILE_WRITE){
	} else if(upload.status == UPLOAD_FILE_END){
		for(byte i=0;i<upload.totalSize;i++)
			json += String((char)upload.buf[i]);
		_settings.setFromJson(json, true);
	}
}
void Controller::handleFileUpload(String name)
{
	HTTPUpload& upload = _webServer.server.upload();
	static File file;
	if(upload.status == UPLOAD_FILE_START){
		file = SPIFFS.open("/"+name, "w");
	} else if(upload.status == UPLOAD_FILE_WRITE){
		if(file)
			file.write(upload.buf, upload.currentSize);
	} else if(upload.status == UPLOAD_FILE_END){
		if(file)
			file.close();
	}
}
String Controller::getContentType(String name){
  if(name.endsWith(".css")) return F("text/css");
  else if(name.endsWith(".js")) return F("application/javascript");
  return F("text/plain");
}

void Controller::setupRoutes()
{
	if(_settings.config.start.value==1){
		//Start
		_webServer.server.on("/", HTTP_GET, [this](){
			_webServer.server.send(200, F("text/html"), _webServer.views.getStart());
		});
		_webServer.server.on("/", HTTP_POST, [this](){
			if(_webServer.server.args()>0){
				handleStartConfig();
				_webServer.server.send(200, F("text/html"), _webServer.views.getStartRedirect());
				_board.reboot(1000);
			}else
				_webServer.server.send(400, "Bad Request.");
		});
		_webServer.server.onNotFound([this](){
			_webServer.server.send(404, F("text/html"), _webServer.views.getNotFound());
		});
	}else{
		if(_settings.config.ap.value!=1 || (_settings.config.ap.value==1 && _webServer.checkLocalMainScripts())){
			//Index
			_webServer.server.on("/", HTTP_GET, [this](){
				handleLogin();
				if(_webServer.server.args()>0){
					_webServer.server.send(200);
					doJob();
				}else
					_webServer.server.send(200, F("text/html"), _webServer.views.getIndex());
			});
			//Ajax
			_webServer.server.on("/refresh", HTTP_GET, [this](){
				handleLogin();
				_webServer.server.send(200, F("text/html"), _webServer.views.getRefresh());
			});
			_webServer.server.on("/network_settings", HTTP_GET, [this](){
				handleLogin();
				_webServer.server.send(200, F("text/html"), _webServer.views.getNetworkSettings());
			});
			_webServer.server.on("/relays_settings", HTTP_GET, [this](){
				handleLogin();
				_webServer.server.send(200, F("text/html"), _webServer.views.getRelaysSettings());
			});
			_webServer.server.on("/sensors_settings", HTTP_GET, [this](){
				handleLogin();
				_webServer.server.send(200, F("text/html"), _webServer.views.getSensorsSettings());
			});
			_webServer.server.on("/triggers_settings", HTTP_GET, [this](){
				handleLogin();
				_webServer.server.send(200, F("text/html"), _webServer.views.getTriggersSettings());
			});
			_webServer.server.on("/scheduler_settings", HTTP_GET, [this](){
				handleLogin();
				_webServer.server.send(200, F("text/html"), _webServer.views.getSchedulerSettings());
			});
			_webServer.server.on("/screen_settings", HTTP_GET, [this](){
				handleLogin();
				_webServer.server.send(200, F("text/html"), _webServer.views.getScreenSettings());
			});
			_webServer.server.on("/board_settings", HTTP_GET, [this](){
				handleLogin();
				_webServer.server.send(200, F("text/html"), _webServer.views.getBoardSettings());
			});
			_webServer.server.on("/watchdog_settings", HTTP_GET, [this](){
				handleLogin();
				_webServer.server.send(200, F("text/html"), _webServer.views.getWatchdogSettings());
			});
			//Sensor
			_webServer.server.on("/sensor", HTTP_GET, [this](){
				handleLogin();
				_webServer.server.send(200, F("text/html"), String(_board.sensors.getSensorValue(_webServer.server.arg("id").toInt())));
			});
			//Log
			_webServer.server.on("/board_log", HTTP_GET, [this](){
				handleLogin();
				_webServer.server.send(200, F("text/plain"), _log.read(F("board.log")));
			});
			_webServer.server.on("/relay_log", HTTP_GET, [this](){
				handleLogin();
				_webServer.server.send(200, F("text/plain"), _log.read(F("relay.log")));
			});
			_webServer.server.on("/sensor_log", HTTP_GET, [this](){
				handleLogin();
				_webServer.server.send(200, F("text/plain"), _log.read(F("sensor.log")));
			});
			_webServer.server.on("/scheduler_log", HTTP_GET, [this](){
				handleLogin();
				_webServer.server.send(200, F("text/plain"), _log.read(F("trigger.log")));
			});
			//
			_webServer.server.on("/i2c_devices", HTTP_GET, [this](){
				handleLogin();
				_webServer.server.send(200, F("text/plain"), _webServer.views.getBoardI2cDevices());
			});
		}
		_webServer.server.onNotFound([this](){
			handleLogin();
			_webServer.server.send(404, F("text/html"), _webServer.views.getNotFound());
		});
		//Update
		_webServer.server.on("/update", HTTP_GET, [this](){
			handleLogin();
			_webServer.server.send(200, F("text/html"), _webServer.views.getUpdate());
		});
		_webServer.server.on("/updateFirmware", HTTP_POST, [this](){
			_webServer.server.sendHeader(F("Connection"), F("close"));
			_webServer.server.sendHeader(F("Access-Control-Allow-Origin"), F("*"));
			_webServer.server.send(200, F("text/html"), (Update.hasError())
					?_webServer.views.getUpdateErrorRedirect()
					:_webServer.views.getUpdateSuccessRedirect());
			_log.write(F("board.log"), F("Firmware updated."));
			_board.reboot(1000);
	    },[this](){
    	  handleLogin();
    	  handleUpdateFirmware();
	    });
		_webServer.server.on("/updateSettings", HTTP_POST, [this](){
			_webServer.server.sendHeader(F("Connection"), F("close"));
			_webServer.server.sendHeader(F("Access-Control-Allow-Origin"), F("*"));
			_webServer.server.send(200, F("text/html"), _webServer.views.getUpdateSuccessRedirect());
			_log.write(F("board.log"), F("Settings uploaded."));
			_board.reboot(1000);
	    },[this](){
    	  handleLogin();
    	  handleUpdateSettings();
	    });
		//Settings
		_webServer.server.on("/settings.json", HTTP_GET, [this](){
			handleLogin();
			_webServer.server.sendHeader(F("Content-Disposition"), F("attachment"));
			_webServer.server.sendHeader(F("filename"), F("settings.json"));
			_settings.getJson(true);
			_webServer.server.send(200, "application/json", _settings.settingsJson);
		});
		//Resources
		_webServer.server.on("/upload", HTTP_POST, [this](){
			_webServer.server.sendHeader(F("Connection"), F("close"));
			_webServer.server.sendHeader(F("Access-Control-Allow-Origin"), F("*"));
			_webServer.server.send(200, F("text/html"), _webServer.views.getUploadRedirect());
	    },[this](){
			handleLogin();
			handleFileUpload(_webServer.server.arg("file"));
	    });
		_webServer.server.on("/download", HTTP_GET, [this](){
			handleLogin();
		    File file = SPIFFS.open("/"+_webServer.server.arg("file"), "r");
		    if(file){
				_webServer.server.streamFile(file, getContentType(_webServer.server.arg("file")));
				file.close();
		    }else
				_webServer.server.send(404, F("text/html"), _webServer.views.getNotFound());
		});
		_webServer.server.on("/delete", HTTP_GET, [this](){
			handleLogin();
			SPIFFS.remove("/"+_webServer.server.arg("file"));
			_webServer.server.send(200, F("text/html"), _webServer.views.getUploadRedirect());
		});
	}
}

