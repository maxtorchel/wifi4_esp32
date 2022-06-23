/*
 * LocalSettingsStorage.cpp
 */

#include <FS.h>
#include <SPIFFS.h>

#include "LocalSettingsStorage.h"

LocalSettingsStorage::LocalSettingsStorage(){}

String LocalSettingsStorage::load(String name)
{
	String json;
	File file = SPIFFS.open("/"+name, "r");
	if(file){
		json = file.readString();
		file.close();
	}

	return json;
}

bool LocalSettingsStorage::save(String &json, String name)
{
	File file = SPIFFS.open("/"+name, "w");
	if(file){
		if(!file.print(json))
			return false;
		file.close();
	}else
		return false;

	return true;
}

bool LocalSettingsStorage::clear(String name)
{
	return SPIFFS.remove("/"+name);
}
