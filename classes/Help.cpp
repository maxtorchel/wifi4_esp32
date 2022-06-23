/*
 * Help.cpp
 */

#include "Help.h"

Help::Help() {}

String Help::charToString(unsigned char sourse[], String separator)
{
	String str = "";
	byte size = sizeof(sourse);
	for(byte i=0;i<size;i++){
		str += String(sourse[i]);
		str += i+1<size?separator:"";
	}
	return str;
}
void Help::explodeString(String sourse, String separator)
{
	String substring;
	for(byte i=0;i<EXPLODE_COUNT;i++){
		int index = sourse.indexOf(separator);
		substring = sourse.substring(0,index!=-1?index:sourse.length());
		if(substring=="")
			break;

		sourse = sourse.substring(index!=-1?index+1:sourse.length());
		stringArray[i] = substring;
	}
}
