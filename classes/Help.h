/*
 * Help.h
 */

#ifndef CLASSES_HELP_H_
#define CLASSES_HELP_H_

#include <Arduino.h>  // for type definitions

class Help {
public:
	Help();

	const static byte EXPLODE_COUNT = 4; //max exploded substrings

	String stringArray[EXPLODE_COUNT];

	String charToString(unsigned char sourse[], String separator);
	void explodeString(String sourse, String separator);
};

#endif /* CLASSES_HELP_H_ */
