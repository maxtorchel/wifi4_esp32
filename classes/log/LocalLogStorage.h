/*
 * LocalLogStorage.h
 */

#ifndef CLASSES_LOCALLOGSTORAGE_H_
#define CLASSES_LOCALLOGSTORAGE_H_

#include <vector>

#include "../Storage.h"

class LocalLogStorage : public Storage {
public:
	LocalLogStorage();

	const static unsigned int FILE_SIZE = 10000; //max log file size in bytes

	String load(String name);
	bool save(String &text, String name);
	bool clear(String name);

private:
	std::vector<String> loadLines(String &name, bool inverse = true);
	String linesToText(std::vector<String> lines);
	void removeFirstLine(String &name);
	void cutFile(String &name);
};

#endif /* CLASSES_LOCALLOGSTORAGE_H_ */
