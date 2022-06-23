/*
 * RemoteSettingsStorage.cpp
 */

#include "RemoteSettingsStorage.h"

RemoteSettingsStorage::RemoteSettingsStorage() {}

String RemoteSettingsStorage::load(String name)
{
	String json;
	HTTPClient http;
	http.begin(F("host"), _settings.config.port.value, "/"+name);
	http.setAuthorization(_settings.config.login.value, _settings.config.password.value);
	if(http.GET() == HTTP_CODE_OK)
		json = http.getString();
	http.end();

	return json;
}

bool RemoteSettingsStorage::save(String &json, String name)
{
	HTTPClient http;
	http.begin(F("host"), _settings.config.port.value, F("/updateSettings"));
	http.setAuthorization(_settings.config.login.value, _settings.config.password.value);
	http.addHeader(F("Content-Type"), F("application/octet-stream"));
	http.addHeader(F("Content-Disposition"), F("form-data"));
	http.addHeader(F("filename"), name);
	int code = http.POST(json);
	http.end();

	return code == HTTP_CODE_OK;
}

bool RemoteSettingsStorage::clear(String name)
{
	HTTPClient http;
	http.begin(F("host"), _settings.config.port.value, F("/?reset=1"));
	http.setAuthorization(_settings.config.login.value, _settings.config.password.value);
	int code = http.GET();
	http.end();

	return code == HTTP_CODE_OK;
}

