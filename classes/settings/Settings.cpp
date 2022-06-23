/*
 * Settings.cpp
 */

#include "Settings.h"

Settings::Settings() {}

bool Settings::checkConfig()
{
	std::unique_ptr<Storage> storage(_storageManager.getStorage(SETTINGS_FS));
	settingsJson = storage->load(F("settings.json"));

	if(settingsJson == "")
		return false;

	DynamicJsonBuffer jsonBuffer;
	JsonObject& settingsObject = jsonBuffer.parseObject(settingsJson);

	return settingsObject.success();
}

bool Settings::loadConfig()
{
	//if config never written or demaged
	if(!checkConfig()){
		Serial.println(F("Init config."));
		saveConfig();
		loadConfig();
	}else{
		std::unique_ptr<Storage> storage(_storageManager.getStorage(SETTINGS_FS));
		settingsJson = storage->load(F("settings.json"));

		if(settingsJson != "" && setFromJson(settingsJson, false)){
			Serial.println(F("Config successfully loaded."));
		}else{
			Serial.println(F("Config loading failed!"));
			return false;
		}
	}

	return true;
}

bool Settings::saveConfig()
{
	if(!getJson()){
		Serial.println(F("Config saving failed!"));
		return false;
	}
	std::unique_ptr<Storage> storage(_storageManager.getStorage(SETTINGS_FS));
	if(!storage->save(settingsJson, F("settings.json"))){
		Serial.println(F("Config saving failed!"));
		return false;
	}

	return true;
}

bool Settings::resetConfig()
{
	std::unique_ptr<Storage> storage(_storageManager.getStorage(SETTINGS_FS));
	if(!storage->clear(F("settings.json"))){
		Serial.println(F("Remove config failed!"));
		return false;
	}

	return true;
}

bool Settings::getJson(bool pretty)
{
	DynamicJsonBuffer jsonBuffer;
	JsonObject& settingsObject = jsonBuffer.createObject();

	settingsObject["start"] = config.start.value;
	settingsObject["login"] = config.login.value;
	settingsObject["password"] = config.password.value;
	settingsObject["ssid"] = config.ssid.value;
	settingsObject["wifi_password"] = config.wifi_password.value;
	settingsObject["ip"] = _help.charToString(config.ip.value,".");
	settingsObject["gateway"] = _help.charToString(config.gateway.value,".");
	settingsObject["subnet"] = _help.charToString(config.subnet.value,".");
	settingsObject["dns1"] = _help.charToString(config.dns1.value,".");
	settingsObject["dns2"] = _help.charToString(config.dns2.value,".");
	settingsObject["port"] = config.port.value;
	settingsObject["dhcp"] = config.dhcp.value;
	settingsObject["ap"] = config.ap.value;
	settingsObject["watchdog_host"] = config.watchdog.host;
	settingsObject["watchdog_interval"] = config.watchdog.interval;
	settingsObject["watchdog_try_count"] = config.watchdog.try_count;
	settingsObject["ntp"] = config.ntp.value;
	settingsObject["ntp_offset"] = config.ntp.offset;
	settingsObject["ntp_update_interval"] = config.ntp.interval;

	JsonArray& relays = settingsObject.createNestedArray("relays");
	for(byte i=0;i<RELAYS_COUNT;i++){
		JsonObject& relay = relays.createNestedObject();
		relay["name"] = config.relays.list[i].name;
		relay["enabled"] = config.relays.list[i].enabled;
		relay["pin"] = config.relays.list[i].pin;
		relay["inverse"] = config.relays.list[i].inverse;
		relay["state"] = config.relays.list[i].state;
		relay["save"] = config.relays.list[i].save;
		relay["watchdog"] = config.relays.list[i].watchdog;
		relay["host"] = config.relays.list[i].host;
	}
	JsonArray& sensors = settingsObject.createNestedArray("sensors");
	for(byte i=0;i<SENSORS_COUNT;i++){
		JsonObject& sensor = sensors.createNestedObject();
		sensor["name"] = config.sensors.list[i].name;
		sensor["enabled"] = config.sensors.list[i].enabled;
		sensor["type"] = config.sensors.list[i].type;
		sensor["pin"] = config.sensors.list[i].pin;
		sensor["group"] = config.sensors.list[i].group;
		sensor["log_interval"] = config.sensors.list[i].log_interval;
		sensor["host"] = config.sensors.list[i].host;
	}
	JsonArray& triggers = settingsObject.createNestedArray("triggers");
	for(byte i=0;i<TRIGGERS_COUNT;i++){
		JsonObject& trigger = triggers.createNestedObject();
		trigger["name"] = config.triggers.list[i].name;
		trigger["enabled"] = config.triggers.list[i].enabled;
		trigger["sensor"] = config.triggers.list[i].sensor;
		trigger["target_type"] = config.triggers.list[i].target_type;
		trigger["target_number"] = config.triggers.list[i].target_number;
		trigger["on_value"] = config.triggers.list[i].on_value;
		trigger["off_value"] = config.triggers.list[i].off_value;
	}
	JsonArray& scheduler = settingsObject.createNestedArray("scheduler");
	for(byte i=0;i<SCHEDULER_COUNT;i++){
		JsonObject& schedule = scheduler.createNestedObject();
		schedule["name"] = config.scheduler.list[i].name;
		schedule["enabled"] = config.scheduler.list[i].enabled;
		schedule["relay"] = config.scheduler.list[i].relay;
		schedule["start_time"] = config.scheduler.list[i].start_time;
		schedule["on_seconds"] = config.scheduler.list[i].on_seconds;
		schedule["off_seconds"] = config.scheduler.list[i].off_seconds;
		schedule["repeat"] = config.scheduler.list[i].repeat;
	}
	JsonArray& screen = settingsObject.createNestedArray("screen");
	for(byte i=0;i<SCREEN_COUNT;i++){
		JsonObject& content = screen.createNestedObject();
		content["name"] = config.screen.list[i].name;
		content["enabled"] = config.screen.list[i].enabled;
		content["source_type"] = config.screen.list[i].source_type;
		content["source_number"] = config.screen.list[i].source_number;
		content["position"] = config.screen.list[i].position;
	}

	settingsJson = "";
	size_t bytes = pretty?settingsObject.prettyPrintTo(settingsJson):settingsObject.printTo(settingsJson);

	return bytes>0;
}

bool Settings::setFromJson(String &json, bool save /*= false*/)
{
	DynamicJsonBuffer jsonBuffer;
	JsonObject& settingsObject = jsonBuffer.parseObject(json);

	if (!settingsObject.success()){
		Serial.println(F("Load settings failed!"));
		return false;
	}

	if(settingsObject.containsKey("start"))
		setStart(settingsObject["start"].as<unsigned char>(), false);
	if(settingsObject.containsKey("login"))
		setLogin(settingsObject["login"].as<String>(), false);
	if(settingsObject.containsKey("password"))
		setPassword(String(settingsObject["password"].as<String>()), false);
	if(settingsObject.containsKey("ssid"))
		setSsid(settingsObject["ssid"].as<String>(), false);
	if(settingsObject.containsKey("wifi_password"))
		setWifiPassword(settingsObject["wifi_password"].as<String>(), false);
	if(settingsObject.containsKey("ip"))
		setIp(settingsObject["ip"].as<String>(), false);
	if(settingsObject.containsKey("gateway"))
		setGateway(settingsObject["gateway"].as<String>(), false);
	if(settingsObject.containsKey("subnet"))
		setSubnet(settingsObject["subnet"].as<String>(), false);
	if(settingsObject.containsKey("dns1"))
		setDns1(settingsObject["dns1"].as<String>(), false);
	if(settingsObject.containsKey("dns2"))
		setDns2(settingsObject["dns2"].as<String>(), false);
	if(settingsObject.containsKey("port"))
		setPort(settingsObject["port"].as<unsigned int>(), false);
	if(settingsObject.containsKey("dhcp"))
		setDhcp(settingsObject["dhcp"].as<unsigned char>(), false);
	if(settingsObject.containsKey("ap"))
		setAp(settingsObject["ap"].as<unsigned char>(), false);
	if(settingsObject.containsKey("watchdog_host"))
		setWatchdogHost(settingsObject["watchdog_host"].as<String>(), false);
	if(settingsObject.containsKey("watchdog_interval"))
		setWatchdogInterval(settingsObject["watchdog_interval"].as<unsigned int>(), false);
	if(settingsObject.containsKey("watchdog_try_count"))
		setWatchdogTryCount(settingsObject["watchdog_try_count"].as<unsigned char>(), false);
	if(settingsObject.containsKey("ntp"))
		setNtp(settingsObject["ntp"].as<unsigned char>(), false);
	if(settingsObject.containsKey("ntp_offset"))
		setNtpOffset(settingsObject["ntp_offset"].as<int>(), false);
	if(settingsObject.containsKey("ntp_update_interval"))
		setNtpUpdateInterval(settingsObject["ntp_update_interval"].as<unsigned int>(), false);

	if(settingsObject.containsKey("relays"))
		for(byte i=0;i<RELAYS_COUNT;i++){
			setRelayName(i, settingsObject["relays"][i]["name"].as<String>(), false);
			setRelayEnabled(i, settingsObject["relays"][i]["enabled"].as<unsigned char>(), false);
			setRelayPin(i, settingsObject["relays"][i]["pin"].as<unsigned char>(), false);
			setRelayInverse(i, settingsObject["relays"][i]["inverse"].as<unsigned char>(), false);
			setRelayRememberState(i, settingsObject["relays"][i]["save"].as<unsigned char>(), false);
			setRelayState(i, settingsObject["relays"][i]["state"].as<unsigned char>(), false);
			setRelayWatchdog(i, settingsObject["relays"][i]["watchdog"].as<unsigned char>(), false);
			setRelayHost(i, settingsObject["relays"][i]["host"].as<String>(), false);
		}
	if(settingsObject.containsKey("sensors"))
		for(byte i=0;i<SENSORS_COUNT;i++){
			setSensorName(i, settingsObject["sensors"][i]["name"].as<String>(), false);
			setSensorEnabled(i, settingsObject["sensors"][i]["enabled"].as<unsigned char>(), false);
			setSensorType(i, settingsObject["sensors"][i]["type"].as<unsigned char>(), false);
			setSensorPin(i, settingsObject["sensors"][i]["pin"].as<unsigned char>(), false);
			setSensorGroup(i, settingsObject["sensors"][i]["group"].as<String>(), false);
			setSensorLogInterval(i, settingsObject["sensors"][i]["log_interval"].as<unsigned int>(), false);
			setSensorHost(i, settingsObject["sensors"][i]["host"].as<String>(), false);
		}
	if(settingsObject.containsKey("triggers"))
		for(byte i=0;i<TRIGGERS_COUNT;i++){
			setTriggerName(i, settingsObject["triggers"][i]["name"].as<String>(), false);
			setTriggerEnabled(i, settingsObject["triggers"][i]["enabled"].as<unsigned char>(), false);
			setTriggerSensor(i, settingsObject["triggers"][i]["sensor"].as<unsigned char>(), false);
			setTriggerTarget(i, settingsObject["triggers"][i]["target_type"].as<unsigned char>(), settingsObject["triggers"][i]["target_number"].as<unsigned char>(), false);
			setTriggerOnValue(i, settingsObject["triggers"][i]["on_value"].as<double>(), false);
			setTriggerOffValue(i, settingsObject["triggers"][i]["off_value"].as<double>(), false);
		}
	if(settingsObject.containsKey("scheduler"))
		for(byte i=0;i<SCHEDULER_COUNT;i++){
			setScheduleName(i, settingsObject["scheduler"][i]["name"].as<String>(), false);
			setScheduleEnabled(i, settingsObject["scheduler"][i]["enabled"].as<unsigned char>(), false);
			setScheduleRelay(i, settingsObject["scheduler"][i]["relay"].as<unsigned char>(), false);
			setScheduleStartTime(i, settingsObject["scheduler"][i]["start_time"].as<unsigned long>(), false);
			setScheduleOnSeconds(i, settingsObject["scheduler"][i]["on_seconds"].as<unsigned int>(), false);
			setScheduleOffSeconds(i, settingsObject["scheduler"][i]["off_seconds"].as<unsigned int>(), false);
			setScheduleRepeat(i, settingsObject["scheduler"][i]["repeat"].as<unsigned char>(), false);
		}
	if(settingsObject.containsKey("screen"))
		for(byte i=0;i<SCREEN_COUNT;i++){
			setScreenName(i, settingsObject["screen"][i]["name"].as<String>(), false);
			setScreenEnabled(i, settingsObject["screen"][i]["enabled"].as<unsigned char>(), false);
			setScreenSource(i, settingsObject["screen"][i]["source_type"].as<unsigned char>(), settingsObject["screen"][i]["source_number"].as<unsigned char>(), false);
			setScreenPosition(i, settingsObject["screen"][i]["position"].as<unsigned char>(), false);
		}

	if(save){
		saveConfig();
		NEED_REBOOT = 1;
	}

	return true;
}

void Settings::setLogin(String login, bool save /*= false*/)
{
	char buf[CHAR_SIZE];
	login.toCharArray(buf, CHAR_SIZE);
	memcpy(config.login.value,buf,CHAR_SIZE);
	if(save){
		saveConfig();
	}
}
void Settings::setPassword(String password, bool save /*= false*/)
{
	char buf[CHAR_SIZE];
	password.toCharArray(buf, CHAR_SIZE);
	memcpy(config.password.value,buf,CHAR_SIZE);
	if(save){
		saveConfig();
	}
}
void Settings::setSsid(String ssid, bool save /*= false*/)
{
	char buf[CHAR_SIZE];
	ssid.toCharArray(buf, CHAR_SIZE);
	memcpy(config.ssid.value,buf,CHAR_SIZE);
	if(save){
		saveConfig();
		NEED_REBOOT = 1;
	}
}
void Settings::setWifiPassword(String wifi_password, bool save /*= false*/)
{
	char buf[CHAR_SIZE];
	wifi_password.toCharArray(buf, CHAR_SIZE);
	memcpy(config.wifi_password.value,buf,CHAR_SIZE);
	if(save){
		saveConfig();
		NEED_REBOOT = 1;
	}
}
void Settings::setPort(unsigned int port, bool save /*= false*/)
{
	config.port.value = port;
	if(save){
		saveConfig();
		NEED_REBOOT = 1;
	}
}
void Settings::setIp(String ip, bool save /*= false*/)
{
	if(setExplodeBuffer(ip, ".", 4)){
		memcpy(config.ip.value,_explodeBuffer,4);
		if(save){
			saveConfig();
			NEED_REBOOT = 1;
		}
	}
}
void Settings::setGateway(String gateway, bool save /*= false*/)
{
	if(setExplodeBuffer(gateway, ".", 4)){
		memcpy(config.gateway.value,_explodeBuffer,4);
		if(save){
			saveConfig();
			NEED_REBOOT = 1;
		}
	}
}
void Settings::setSubnet(String subnet, bool save /*= false*/)
{
	if(setExplodeBuffer(subnet, ".", 4)){
		memcpy(config.subnet.value,_explodeBuffer,4);
		if(save){
			saveConfig();
			NEED_REBOOT = 1;
		}
	}
}
void Settings::setDns1(String dns1, bool save /*= false*/)
{
	if(setExplodeBuffer(dns1, ".", 4)){
		memcpy(config.dns1.value,_explodeBuffer,4);
		if(save){
			saveConfig();
			NEED_REBOOT = 1;
		}
	}
}
void Settings::setDns2(String dns2, bool save /*= false*/)
{
	if(setExplodeBuffer(dns2, ".", 4)){
		memcpy(config.dns2.value,_explodeBuffer,4);
		if(save){
			saveConfig();
			NEED_REBOOT = 1;
		}
	}
}
void Settings::setDhcp(byte dhcp, bool save /*= false*/)
{
	config.dhcp.value = dhcp;
	if(save){
		saveConfig();
		NEED_REBOOT = 1;
	}
}
void Settings::setAp(byte ap, bool save /*= false*/)
{
	config.ap.value = ap;
	if(save){
		saveConfig();
		NEED_REBOOT = 1;
	}
}

void Settings::setStart(byte start, bool save /*= false*/)
{
	config.start.value = start;
	if(save){
		saveConfig();
		NEED_REBOOT = 1;
	}
}

boolean Settings::setExplodeBuffer(String string, String separator, byte count)
{
	byte buf[count];
	_help.explodeString(string, separator);
	byte i=0;
	while(i<count){
		unsigned int num = _help.stringArray[i].toInt();
		if(num<256){
			buf[i] = num;
			i++;
		}else
			break;
	}
	if(i==count){
		memcpy(_explodeBuffer,buf,4);
		return true;
	}else
		return false;
}

/* RELAY */
void Settings::setRelayEnabled(byte relayId, byte enabled, bool save /*= false*/)
{
	config.relays.list[relayId].enabled = enabled;
	if(save){
		saveConfig();
	}
}
void Settings::setRelayState(byte relayId, byte state, bool save /*= false*/)
{
	config.relays.list[relayId].state = state;
    if(config.relays.list[relayId].save==1)
    	if(save){
    		saveConfig();
    	}
}
void Settings::setRelayRememberState(byte relayId, byte state, bool save /*= false*/)
{
	config.relays.list[relayId].save = state;
	if(save){
		saveConfig();
	}
}
void Settings::setRelayWatchdog(byte relayId, byte state, bool save /*= false*/)
{
	config.relays.list[relayId].watchdog = state;
	if(save){
		saveConfig();
	}
}
void Settings::setRelayHost(byte relayId, String host, bool save /*= false*/)
{
	char buf[CHAR_SIZE];
	host.toCharArray(buf, CHAR_SIZE);
	memcpy(config.relays.list[relayId].host,buf,CHAR_SIZE);
	if(save){
		saveConfig();
	}
}
void Settings::setRelayPin(byte relayId, byte pin, bool save /*= false*/)
{
	config.relays.list[relayId].pin = pin;
	if(save){
		saveConfig();
		NEED_REBOOT = 1;
	}
}
void Settings::setRelayName(byte relayId, String name, bool save /*= false*/)
{
	char buf[CHAR_SIZE];
	name.toCharArray(buf, CHAR_SIZE);
	memcpy(config.relays.list[relayId].name,buf,CHAR_SIZE);
	if(save){
		saveConfig();
		NEED_REBOOT = 1;
	}
}
void Settings::setRelayInverse(byte relayId, byte state, bool save /*= false*/)
{
	config.relays.list[relayId].inverse = state;
	if(save){
		saveConfig();
	}
}
bool Settings::checkRelay(byte relayId)
{
	return (config.relays.list[relayId].pin!=0
			&& config.relays.list[relayId].enabled!=0);
}
/* RELAY */

/* WATCHDOG */
void Settings::setWatchdogHost(String host, bool save /*= false*/)
{
	char buf[CHAR_SIZE];
	host.toCharArray(buf, CHAR_SIZE);
	memcpy(config.watchdog.host,buf,CHAR_SIZE);
	if(save){
		saveConfig();
	}
}
void Settings::setWatchdogInterval(unsigned int interval, bool save /*= false*/)
{
	config.watchdog.interval = interval;
	if(save){
		saveConfig();
	}
}
void Settings::setWatchdogTryCount(byte try_count, bool save /*= false*/)
{
	config.watchdog.try_count = try_count;
	if(save){
		saveConfig();
	}
}
/* WATCHDOG */

/* SENSOR */
void Settings::setSensorEnabled(byte sensorId, byte enabled, bool save /*= false*/)
{
	config.sensors.list[sensorId].enabled = enabled;
	if(save){
		saveConfig();
	}
}
void Settings::setSensorName(byte sensorId, String name, bool save /*= false*/)
{
	char buf[CHAR_SIZE];
	name.toCharArray(buf, CHAR_SIZE);
	memcpy(config.sensors.list[sensorId].name,buf,CHAR_SIZE);
	if(save){
		saveConfig();
	}
}
void Settings::setSensorType(byte sensorId, byte type, bool save /*= false*/)
{
	config.sensors.list[sensorId].type = type;
	if(save){
		saveConfig();
	}
}
void Settings::setSensorPin(byte sensorId, byte pin, bool save /*= false*/)
{
	config.sensors.list[sensorId].pin = pin;
	if(save){
		saveConfig();
		NEED_REBOOT = 1;
	}
}
void Settings::setSensorGroup(byte sensorId, String group, bool save /*= false*/)
{
	char buf[CHAR_SIZE];
	group.toCharArray(buf, CHAR_SIZE);
	memcpy(config.sensors.list[sensorId].group,buf,CHAR_SIZE);
	if(save){
		saveConfig();
	}
}
void Settings::setSensorHost(byte sensorId, String host, bool save /*= false*/)
{
	char buf[CHAR_SIZE];
	host.toCharArray(buf, CHAR_SIZE);
	memcpy(config.sensors.list[sensorId].host,buf,CHAR_SIZE);
	if(save){
		saveConfig();
	}
}
void Settings::setSensorLogInterval(byte sensorId, unsigned int seconds, bool save /*= false*/)
{
	config.sensors.list[sensorId].log_interval = seconds;
	if(save){
		saveConfig();
	}
}
bool Settings::checkSensor(byte sensorId)
{
	return (config.sensors.list[sensorId].type!=0
			&& config.sensors.list[sensorId].enabled!=0
			&& (config.sensors.list[sensorId].type<=10 || (config.sensors.list[sensorId].type>10 && config.sensors.list[sensorId].pin!=0)));
}
/* SENSOR */

/* TRIGGER */
void Settings::setTriggerEnabled(byte triggerId, byte enabled, bool save /*= false*/)
{
	config.triggers.list[triggerId].enabled = enabled;
	if(save){
		saveConfig();
	}
}
void Settings::setTriggerName(byte triggerId, String name, bool save /*= false*/)
{
	char buf[CHAR_SIZE];
	name.toCharArray(buf, CHAR_SIZE);
	memcpy(config.triggers.list[triggerId].name,buf,CHAR_SIZE);
	if(save){
		saveConfig();
	}
}
void Settings::setTriggerSensor(byte triggerId, byte sensor, bool save /*= false*/)
{
	config.triggers.list[triggerId].sensor = sensor;
	if(save){
		saveConfig();
	}
}
void Settings::setTriggerTarget(byte triggerId, byte type, byte number, bool save /*= false*/)
{
	config.triggers.list[triggerId].target_type = type;
	config.triggers.list[triggerId].target_number = number;
	if(save){
		saveConfig();
	}
}
void Settings::setTriggerOnValue(byte triggerId, double on_value, bool save /*= false*/)
{
	config.triggers.list[triggerId].on_value = on_value;
	if(save){
		saveConfig();
	}
}
void Settings::setTriggerOffValue(byte triggerId, double off_value, bool save /*= false*/)
{
	config.triggers.list[triggerId].off_value = off_value;
	if(save){
		saveConfig();
	}
}
bool Settings::checkTrigger(byte triggerId)
{
	return (config.triggers.list[triggerId].sensor!=0
			&& config.triggers.list[triggerId].target_type!=0
			&& config.triggers.list[triggerId].target_number!=0
			&& config.triggers.list[triggerId].enabled!=0);
}
/* TRIGGER */

/* SCHEDULER */
void Settings::setScheduleEnabled(byte scheduleId, byte enabled, bool save /*= false*/)
{
	config.scheduler.list[scheduleId].enabled = enabled;
	if(save){
		saveConfig();
	}
}
void Settings::setScheduleName(byte scheduleId, String name, bool save /*= false*/)
{
	char buf[CHAR_SIZE];
	name.toCharArray(buf, CHAR_SIZE);
	memcpy(config.scheduler.list[scheduleId].name,buf,CHAR_SIZE);
	if(save){
		saveConfig();
	}
}
void Settings::setScheduleRelay(byte scheduleId, byte relay, bool save /*= false*/)
{
	config.scheduler.list[scheduleId].relay = relay;
	if(save){
		saveConfig();
	}
}
void Settings::setScheduleStartTime(byte scheduleId, unsigned long unixtime, bool save /*= false*/)
{
	config.scheduler.list[scheduleId].start_time = unixtime;
	if(save){
		saveConfig();
	}
}
void Settings::setScheduleOnSeconds(byte scheduleId, unsigned int seconds, bool save /*= false*/)
{
	config.scheduler.list[scheduleId].on_seconds = seconds;
	if(save){
		saveConfig();
	}
}
void Settings::setScheduleOffSeconds(byte scheduleId, unsigned int seconds, bool save /*= false*/)
{
	config.scheduler.list[scheduleId].off_seconds = seconds;
	if(save){
		saveConfig();
	}
}
void Settings::setScheduleRepeat(byte scheduleId, byte state, bool save /*= false*/)
{
	config.scheduler.list[scheduleId].repeat = state;
	if(save){
		saveConfig();
	}
}
bool Settings::checkSchedule(byte scheduleId)
{
	return (config.scheduler.list[scheduleId].relay!=0
			&& config.scheduler.list[scheduleId].start_time!=0
			&& (config.scheduler.list[scheduleId].on_seconds+config.scheduler.list[scheduleId].off_seconds)!=0
			&& config.scheduler.list[scheduleId].enabled!=0);
}
/* SCHEDULER */

/* SCREEN */
void Settings::setScreenEnabled(byte screenId, byte enabled, bool save /*= false*/)
{
	config.screen.list[screenId].enabled = enabled;
	if(save){
		saveConfig();
	}
}
void Settings::setScreenName(byte screenId, String name, bool save /*= false*/)
{
	char buf[CHAR_SIZE];
	name.toCharArray(buf, CHAR_SIZE);
	memcpy(config.screen.list[screenId].name,buf,CHAR_SIZE);
	if(save){
		saveConfig();
	}
}
void Settings::setScreenSource(byte screenId, byte type, byte number, bool save /*= false*/)
{
	config.screen.list[screenId].source_type = type;
	config.screen.list[screenId].source_number = number;
	if(save){
		saveConfig();
	}
}
void Settings::setScreenPosition(byte screenId, byte position, bool save /*= false*/)
{
	config.screen.list[screenId].position = position;
	if(save){
		saveConfig();
	}
}
bool Settings::checkScreen(byte screenId)
{
	return (config.screen.list[screenId].position!=0
			&& config.screen.list[screenId].source_type!=0
			&& config.screen.list[screenId].source_number!=0
			&& config.screen.list[screenId].enabled!=0);
}
/* SCREEN */

/* NTP */
void Settings::setNtp(byte ntp, bool save /*= false*/)
{
	config.ntp.value = ntp;
	if(save){
		saveConfig();
	}
}
void Settings::setNtpOffset(int offset, bool save /*= false*/)
{
	config.ntp.offset = offset;
	if(save){
		saveConfig();
	}
}
void Settings::setNtpUpdateInterval(unsigned int interval, bool save /*= false*/)
{
	config.ntp.interval = interval;
	if(save){
		saveConfig();
	}
}
/* NTP */

