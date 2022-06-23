/*
 * RemoteSettingsStorage.h
 */

#ifndef CLASSES_SETTINGS_REMOTESETTINGSSTORAGE_H_
#define CLASSES_SETTINGS_REMOTESETTINGSSTORAGE_H_

#include <HTTPClient.h>

#include "../Storage.h"
#include "../settings/Settings.h"

class RemoteSettingsStorage : public Storage {
public:
	RemoteSettingsStorage();

	String load(String name);
	bool save(String &json, String name);
	bool clear(String name);

private:
	Settings& _settings = Settings::Instance();
};

#endif /* CLASSES_SETTINGS_REMOTESETTINGSSTORAGE_H_ */
