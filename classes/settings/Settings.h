/*
 * Settings.h
 */

#ifndef CLASSES_SETTINGS_H_
#define CLASSES_SETTINGS_H_

#include <memory>
#include <ArduinoJson.h>

#include "../StorageManager.h"
#include "../Help.h"

class Settings {
public:
	static Settings& Instance()
	{
		static Settings settingsInstance;
		return settingsInstance;
	}
	const static byte CHAR_SIZE = 24; //max char size
	const static byte RELAYS_COUNT = 8;
	const static byte SENSORS_COUNT = 8;
	const static byte TRIGGERS_COUNT = 8;
	const static byte SCHEDULER_COUNT = 8;
	const static byte SCREEN_COUNT = 4;

	byte NEED_REBOOT = 0;

	String settingsJson;

	struct Config{
		struct {
			const char name[6] = "login";
			char value[CHAR_SIZE] = "admin";
		} login;
		struct {
			const char name[9] = "password";
			char value[CHAR_SIZE] = "admin";
		} password;
		struct {
			const char name[5] = "ssid";
			char value[CHAR_SIZE] = "board";
		} ssid;
		struct {
			const char name[14] = "wifi_password";
			char value[CHAR_SIZE] = "1029384756";
		} wifi_password;
		struct {
			const char name[3] = "ip";
			byte value[4] = {192,168,1,15};
		} ip;
		struct {
			const char name[8] = "gateway";
			byte value[4] = {192,168,1,1};
		} gateway;
		struct {
			const char name[7] = "subnet";
			byte value[4] = {255,255,255,0};
		} subnet;
		struct {
			const char name[5] = "dns1";
			byte value[4] = {8,8,8,8};
		} dns1;
		struct {
			const char name[5] = "dns2";
			byte value[4] = {8,8,4,4};
		} dns2;
		struct {
			const char name[5] = "port";
			unsigned int value = 80;
		} port;
		struct {
			const char name[7] = "relays";
			struct {
				char name[CHAR_SIZE];
				byte enabled;
				byte pin;
				byte inverse;
				byte state;
				byte save;
				byte watchdog;
				char host[CHAR_SIZE];
			} list[RELAYS_COUNT] = {
								   	   {"",0,0,0,0,0,0,""},
								   	   {"",0,0,0,0,0,0,""},
								   	   {"",0,0,0,0,0,0,""},
								   	   {"",0,0,0,0,0,0,""},
								   	   {"",0,0,0,0,0,0,""},
								   	   {"",0,0,0,0,0,0,""},
								   	   {"",0,0,0,0,0,0,""},
								   	   {"",0,0,0,0,0,0,""},
								   };
		} relays;
		struct {
			const char name[8] = "sensors";
			struct {
				char name[CHAR_SIZE];
				byte enabled;
				byte type;
				byte pin;
				char group[CHAR_SIZE];
				unsigned int log_interval;
				char host[CHAR_SIZE];
			} list[SENSORS_COUNT] = {
								   	   {"",0,0,0,"",0,""},
								   	   {"",0,0,0,"",0,""},
								   	   {"",0,0,0,"",0,""},
								   	   {"",0,0,0,"",0,""},
								   	   {"",0,0,0,"",0,""},
								   	   {"",0,0,0,"",0,""},
								   	   {"",0,0,0,"",0,""},
								   	   {"",0,0,0,"",0,""},
								   };
		} sensors;
		struct {
			const char name[9] = "triggers";
			struct {
				char name[CHAR_SIZE];
				byte enabled;
				byte sensor;
				byte target_type;
				byte target_number;
				double on_value;
				double off_value;
			} list[TRIGGERS_COUNT] = {
								   	   {"",0,0,0,0,0,0},
								   	   {"",0,0,0,0,0,0},
								   	   {"",0,0,0,0,0,0},
								   	   {"",0,0,0,0,0,0},
								   	   {"",0,0,0,0,0,0},
								   	   {"",0,0,0,0,0,0},
								   	   {"",0,0,0,0,0,0},
								   	   {"",0,0,0,0,0,0},
								   };
		} triggers;
		struct {
			const char name[10] = "scheduler";
			struct {
				char name[CHAR_SIZE];
				byte enabled;
				byte relay;
				unsigned long start_time;
				unsigned int on_seconds;
				unsigned int off_seconds;
				byte repeat;
			} list[SCHEDULER_COUNT] = {
								   	   {"",0,0,0,0,0,0},
								   	   {"",0,0,0,0,0,0},
								   	   {"",0,0,0,0,0,0},
								   	   {"",0,0,0,0,0,0},
								   	   {"",0,0,0,0,0,0},
								   	   {"",0,0,0,0,0,0},
								   	   {"",0,0,0,0,0,0},
								   	   {"",0,0,0,0,0,0},
								   };
		} scheduler;
		struct {
			const char name[9] = "watchdog";
			char host[CHAR_SIZE] = "";
			unsigned int interval = 60; //seconds
			byte try_count = 5;
		} watchdog;
		struct {
			const char name[7] = "screen";
			struct {
				char name[CHAR_SIZE];
				byte enabled;
				byte source_type;
				byte source_number;
				byte position;
			} list[SCREEN_COUNT] = {
								   	   {"",0,0,0,0},
								   	   {"",0,0,0,0},
								   	   {"",0,0,0,0},
								   	   {"",0,0,0,0},
								   };
		} screen;
		struct {
			const char name[5] = "dhcp";
			byte value = 0;
		} dhcp;
		struct {
			const char name[3] = "ap";
			byte value = 1;
		} ap;
		struct {
			const char name[4] = "ntp";
			byte value = 1;
			int offset = 0; //time zone offset in seconds
			unsigned int interval = 43200; //update interval in seconds
		} ntp;
		struct {
			const char name[6] = "start"; //first boot
			byte value = 1;
		} start;
		struct {
			const char name[8] = "version";
			char value[CHAR_SIZE] = "0.9c";
		} version;
	} config;

	bool loadConfig();
	bool saveConfig();
	bool resetConfig();
	bool getJson(bool pretty = false);
	bool setFromJson(String &json, bool save = false);
	//Network
	void setLogin(String login, bool save = false);
	void setPassword(String password, bool save = false);
	void setSsid(String ssid, bool save = false);
	void setWifiPassword(String wifi_password, bool save = false);
	void setPort(unsigned int port, bool save = false);
	void setIp(String ip, bool save = false);
	void setGateway(String gateway, bool save = false);
	void setSubnet(String subnet, bool save = false);
	void setDns1(String dns1, bool save = false);
	void setDns2(String dns2, bool save = false);
	void setDhcp(byte dhcp, bool save = false);
	void setAp(byte ap, bool save = false);
	//Board
	void setStart(byte start, bool save = false);
	//Relay
	void setRelayEnabled(byte relayId, byte enabled, bool save = false);
	void setRelayState(byte relayId, byte state, bool save = false);
	void setRelayPin(byte relayId, byte pin, bool save = false);
	void setRelayName(byte relayId, String name, bool save = false);
	void setRelayInverse(byte relayId, byte state, bool save = false);
	void setRelayRememberState(byte relayId, byte state, bool save = false);
	void setRelayWatchdog(byte relayId, byte state, bool save = false);
	void setRelayHost(byte relayId, String host, bool save = false);
	void setWatchdogHost(String host, bool save = false);
	void setWatchdogInterval(unsigned int interval, bool save = false);
	void setWatchdogTryCount(byte try_count, bool save = false);
	bool checkRelay(byte relayId);
	//Sensor
	void setSensorEnabled(byte sensorId, byte enabled, bool save = false);
	void setSensorName(byte sensorId, String name, bool save = false);
	void setSensorType(byte sensorId, byte type, bool save = false);
	void setSensorPin(byte sensorId, byte pin, bool save = false);
	void setSensorGroup(byte sensorId, String group, bool save = false);
	void setSensorHost(byte sensorId, String host, bool save = false);
	void setSensorLogInterval(byte sensorId, unsigned int seconds, bool save = false);
	bool checkSensor(byte sensorId);
	//Trigger
	void setTriggerEnabled(byte triggerId, byte enabled, bool save = false);
	void setTriggerName(byte triggerId, String name, bool save = false);
	void setTriggerSensor(byte triggerId, byte sensor, bool save = false);
	void setTriggerTarget(byte triggerId, byte type, byte number, bool save = false);
	void setTriggerOnValue(byte triggerId, double on_value, bool save = false);
	void setTriggerOffValue(byte triggerId, double off_value, bool save = false);
	bool checkTrigger(byte triggerId);
	//Scheduler
	void setScheduleEnabled(byte scheduleId, byte enabled, bool save = false);
	void setScheduleName(byte scheduleId, String name, bool save = false);
	void setScheduleRelay(byte scheduleId, byte relay, bool save = false);
	void setScheduleStartTime(byte scheduleId, unsigned long unixtime, bool save = false);
	void setScheduleOnSeconds(byte scheduleId, unsigned int seconds, bool save = false);
	void setScheduleOffSeconds(byte scheduleId, unsigned int seconds, bool save = false);
	void setScheduleRepeat(byte scheduleId, byte state, bool save = false);
	bool checkSchedule(byte scheduleId);
	//SCREEN
	void setScreenEnabled(byte screenId, byte enabled, bool save = false);
	void setScreenName(byte screenId, String name, bool save = false);
	void setScreenSource(byte screenId, byte type, byte number, bool save = false);
	void setScreenPosition(byte screenId, byte position, bool save = false);
	bool checkScreen(byte screenId);
	//NTP
	void setNtp(byte ntp, bool save = false);
	void setNtpOffset(int offset, bool save = false);
	void setNtpUpdateInterval(unsigned int interval, bool save = false);


private:
	Settings();
	Settings(const Settings&);
	Settings& operator=(const Settings&);

	StorageManager _storageManager;
	Help _help;
	byte _explodeBuffer[4];

//	bool setPrivateFromJson(String &json, bool save = false);
//	bool getPrivateJson(bool pretty = false);

	boolean setExplodeBuffer(String string, String separator, byte count);
	bool checkConfig();
};

#endif /* CLASSES_SETTINGS_H_ */
