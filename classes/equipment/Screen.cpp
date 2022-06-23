/*
 * Screen.cpp
 */

#include "Screen.h"

Screen::Screen() {}

void Screen::init()
{
	if(exists()){
		ssd.init();
		ssd.flipScreenVertically();
		ssd.setFont(ArialMT_Plain_16);
		ssd.setTextAlignment(TEXT_ALIGN_LEFT);
	}
}

bool Screen::exists()
{
    Wire.beginTransmission(0x3c);
    return Wire.endTransmission()==0;
}

void Screen::display()
{
	unsigned long curmillis = millis();
	if(curmillis - timestamp > 10000 && exists()){
		timestamp = curmillis;

		ssd.clear();
		displayHeader();
		displayContent();
		ssd.display();
	}
}
void Screen::displayHeader()
{

}
void Screen::displayContent()
{
//	ssd.drawString(0, 0, "Ligth: 58 lx");
//	ssd.drawString(0, 16, "Ligth: 58 lx");
//	ssd.drawString(0, 32, "Ligth: 58 lx");
//	ssd.drawString(0, 48, "Ligth: 58 lx");

	for(byte i=0;i<_settings.SCREEN_COUNT;i++){
		if(_settings.checkScreen(i)){
			byte position = _settings.config.screen.list[i].position-1;
			String name = _settings.config.screen.list[i].name;
			String nameStr = name!=""?name+": ":"";

			switch (_settings.config.screen.list[i].source_type){
				case CLOCK:{
					if(_clock.exists()){
						String text = nameStr+_clock.getDateTimeString();
						ssd.drawString(positions[position].x, positions[position].y, text);
					}
				}
				break;
				case SENSOR:{
					byte sensorId = _settings.config.screen.list[i].source_number-1;

					if(_settings.checkSensor(sensorId)){
						String value = String(_sensors.getSensorValue(sensorId));
						String unit = _sensors.getSensorUnit(sensorId);
						String text = nameStr+value+unit;

						ssd.drawString(positions[position].x, positions[position].y, text);
					}
				}
				break;
				default:
					Serial.println(F("Wrong screen source type!"));
			}
		}
	}
}
