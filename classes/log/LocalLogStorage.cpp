/*
 * LocalLogStorage.cpp
 */

#include <algorithm>
#include <FS.h>
#include <SPIFFS.h>

#include "LocalLogStorage.h"

LocalLogStorage::LocalLogStorage(){}

std::vector<String> LocalLogStorage::loadLines(String &name, bool inverse /*= true*/) {
	std::vector<String> lines;

	File file = SPIFFS.open("/"+name, "r");
	if(file){
    	while(file.available())
    		lines.insert(lines.begin(), file.readStringUntil('\n'));
    	file.close();
	}

	return lines;
}

String LocalLogStorage::linesToText(std::vector<String> lines) {
	String text;

	for(unsigned int i=0;i<lines.size();i++)
		text += lines[i];

	return text;
}

String LocalLogStorage::load(String name)
{
	return linesToText(loadLines(name));
}

void LocalLogStorage::removeFirstLine(String &name)
{
	File file = SPIFFS.open("/"+name, "r");
	if(file){
		file.readStringUntil('\n');
		String cutText = file.readString();
		file.close();

		File cutFile = SPIFFS.open("/"+name, "w");
		if(cutFile){
			cutFile.print(cutText);
			cutFile.close();
		}
	}
}

void LocalLogStorage::cutFile(String &name)
{
	File file = SPIFFS.open("/"+name, "r");

	while(file.size()>FILE_SIZE)
		removeFirstLine(name);

	file.close();
}

bool LocalLogStorage::save(String &text, String name)
{
	File file = SPIFFS.open("/"+name, "a+");
	if(file){
		unsigned int filesize = file.size();
		if(file.println(text)){
			if(filesize>FILE_SIZE)
				cutFile(name);

			return true;
		}

		file.close();
	}

	return false;
}

bool LocalLogStorage::clear(String name)
{
	return (SPIFFS.remove("/"+name));
}
