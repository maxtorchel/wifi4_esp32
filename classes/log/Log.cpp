/*
 * Log.cpp
 */

#include "Log.h"

Log::Log() {}

bool Log::write(String source, String message)
{
	String text = _clock.getDateTimeString(0, true)+" - "+message;
	std::unique_ptr<Storage> storage(_storageManager.getStorage(LOG_FS));
	if(!storage->save(text, source)){
		Serial.println(F("Log saving failed!"));
		return false;
	}

	return true;
}
String Log::read(String source)
{
	std::unique_ptr<Storage> storage(_storageManager.getStorage(LOG_FS));
	return storage->load(source);
}
