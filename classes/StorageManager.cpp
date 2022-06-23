/*
 * StorageManager.cpp
 */

#include "StorageManager.h"

#include "settings/LocalSettingsStorage.h"
#include "log/LocalLogStorage.h"

StorageManager::StorageManager() {}

Storage* StorageManager::getStorage(storage_type type)
{
	Storage* storage = NULL;

	switch (type){
		case SETTINGS_FS:
			storage = new LocalSettingsStorage;
			return storage;
		case LOG_FS:
			storage = new LocalLogStorage;
			return storage;
		default:
			Serial.println(F("Wrong storage type!"));
			return storage;
	}
}
