/*
 * Log.h
 */

#ifndef CLASSES_LOG_H_
#define CLASSES_LOG_H_

#include <memory>

#include "../StorageManager.h"
#include "../equipment/Clock.h"

class Log {
public:
	Log();

	bool write(String source, String message);
	String read(String source);

private:
	StorageManager _storageManager;
	Clock _clock;
};

#endif /* CLASSES_LOG_H_ */
