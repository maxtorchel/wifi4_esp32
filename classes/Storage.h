/*
 * Storage.h
 */

#ifndef CLASSES_STORAGE_H_
#define CLASSES_STORAGE_H_

#include <Arduino.h>

enum storage_type{SETTINGS_FS = 1, LOG_FS};

class Storage {
public:
	Storage();
	virtual ~Storage(){}

	virtual String load(String name) = 0;
	virtual bool save(String &json, String name) = 0;
	virtual bool clear(String name) = 0;
};

#endif /* CLASSES_STORAGE_H_ */
