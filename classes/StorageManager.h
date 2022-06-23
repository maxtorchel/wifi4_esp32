/*
 * StorageManager.h
 */

#ifndef CLASSES_STORAGEMANAGER_H_
#define CLASSES_STORAGEMANAGER_H_

#include "Storage.h"

class StorageManager {
public:
	StorageManager();

	Storage* getStorage(storage_type type);
};

#endif /* CLASSES_STORAGEMANAGER_H_ */
