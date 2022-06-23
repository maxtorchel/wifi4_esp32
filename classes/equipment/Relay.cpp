/*
 * Relay.cpp
 */

#include "Relay.h"

Relay::Relay() {}

void Relay::initRelays()
{
	for(byte i=0;i<_settings.RELAYS_COUNT;i++){
		if(String(_settings.config.relays.list[i].name)!="" && _settings.config.relays.list[i].pin!=0)
			initRelay(i);
	}
}

void Relay::initRelay(byte relayId)
{
	if(_settings.config.relays.list[relayId].save!=1)
		_settings.config.relays.list[relayId].state = 0;

	byte pin = _settings.config.relays.list[relayId].pin;
	byte state = _settings.config.relays.list[relayId].state;
    pinMode(pin, OUTPUT);
    switchRelay(relayId, state, false);
}

void Relay::switchRelay(byte relayId, byte state, boolean save /*= true*/)
{
	if(_settings.checkRelay(relayId)){
		if(String(_settings.config.relays.list[relayId].host)==""){
			if(_settings.config.relays.list[relayId].inverse==1){
				byte inverseState = (state==1)?0:1;
				digitalWrite(_settings.config.relays.list[relayId].pin, inverseState);
			}else
				digitalWrite(_settings.config.relays.list[relayId].pin, state);
		}else
			save = switchRemoteRelay(relayId, state);

		if(save)
			_settings.setRelayState(relayId, state, true);
	}else
		_log.write(F("relay.log"), "Can not switch R"+String(relayId+1)+" because it is disabled.");
}
bool Relay::switchRemoteRelay(byte relayId, byte state)
{
	HTTPClient http;
	http.begin(_settings.config.relays.list[relayId].host, _settings.config.port.value, "/?switch="+String(state)+"&relay="+String(relayId));
	http.setAuthorization(_settings.config.login.value, _settings.config.password.value);
	int code = http.GET();
	http.end();

	return code == HTTP_CODE_OK;
}

void Relay::handleWatchdog()
{
	unsigned long curmillis = millis();
	if(curmillis - timestamp > _settings.config.watchdog.interval * 1000){
		if(String(_settings.config.watchdog.host)!=""){
			if(!_watchdog.checkHost(_settings.config.watchdog.host)){
				byte switchedRelays[_settings.RELAYS_COUNT];
				for(byte i=0;i<_settings.RELAYS_COUNT;i++)
					if(_settings.config.relays.list[i].watchdog!=0 && _settings.config.relays.list[i].state==1){
						switchRelay(i, 0, false);
						switchedRelays[i] = 1;
						_log.write(F("relay.log"), "R"+String(i+1)+" off by Watchdog host "+String(_settings.config.watchdog.host)+".");
					}

				delay(10000);

				for(byte i=0;i<_settings.RELAYS_COUNT;i++)
					if(_settings.config.relays.list[i].watchdog!=0 && switchedRelays[i] == 1){
						switchRelay(i, 1, false);
						_log.write(F("relay.log"), "R"+String(i+1)+" on by Watchdog host "+String(_settings.config.watchdog.host)+".");
					}
			}
		}

		timestamp = millis();
	}
}
