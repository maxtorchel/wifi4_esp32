/*
 * LocalSettingsStorage.h
 */

#ifndef CLASSES_LOCALSETTINGSSTORAGE_H_
#define CLASSES_LOCALSETTINGSSTORAGE_H_

#include "../Storage.h"

class LocalSettingsStorage : public Storage {
public:
	LocalSettingsStorage();

	String load(String name);
	bool save(String &json, String name);
	bool clear(String name);
};

#endif /* CLASSES_LOCALSETTINGSSTORAGE_H_ */
