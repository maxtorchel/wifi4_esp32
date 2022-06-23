/*
 * TriggersSettingsView.cpp
 */

#include "TriggersSettingsView.h"

TriggersSettingsView::TriggersSettingsView() {}

String TriggersSettingsView::printPage()
{
	String html = "";
	String sensors = F("[{value:0,text:\"\"}");
	for(byte i=0;i<_settings.SENSORS_COUNT;i++){
		if(_settings.checkSensor(i))
			sensors += ",{value:"+String(i+1)+",text:\"S"+String(i+1)+"\"}";
	}
	sensors += F("]");
	String targets = F("[{value:\"/{type:0,number:0}\",text:\"\"}");
	for(byte i=0;i<_settings.RELAYS_COUNT;i++){
		if(_settings.checkRelay(i))
			targets += ",{value:\"/{type:1,number:"+String(i+1)+"}\",text:\"R"+String(i+1)+"\"}";
	}
	for(byte i=0;i<_settings.SCHEDULER_COUNT;i++){
		if(_settings.checkSchedule(i))
			targets += ",{value:\"/{type:2,number:"+String(i+1)+"}\",text:\"SC"+String(i+1)+"\"}";
	}
	targets += F("]");

	html += F("<script type='text/javascript'>"
		"$(document).ready(function(){"
			"installEditable();"
		"});"
	"</script>"

	"<div class='panel-body'>");
	for(byte i=0;i<_settings.TRIGGERS_COUNT;i++){
		String triggerNumber = String(i+1);

		html += F("<div><i class='toggle glyphicon glyphicon-off ");
			html += String(_settings.config.triggers.list[i].enabled==1?"glyphicon-green":"");
			html += F("' title='Enable' data-name='trigger_enabled' data-url='?trigger=");
			html += String(i);
			html += F("' role='button'></i> T");
			html += triggerNumber;
			html += F(" - <a class='editable' href='#' title='Name' data-name='trigger_name' data-url='?trigger=");
			html += String(i)+"'>"+String(_settings.config.triggers.list[i].name);
			html += F("</a> : <a class='editable-select' href='#' title='Sensor' data-name='trigger_sensor' data-url='?trigger=");
			html += String(i)+"' data-value='"+String(_settings.config.triggers.list[i].sensor)+"' data-source='"+sensors;
			html += F("'></a> : <a class='editable-select' href='#' title='Target' data-name='trigger_target' data-url='?trigger=");
			html += String(i)+"' data-value='/{type:"+String(_settings.config.triggers.list[i].target_type)+",number:"+String(_settings.config.triggers.list[i].target_number)+"}' data-source='"+targets;
			html += F("'></a> | <a class='editable-num' href='#' title='On value' data-name='trigger_on_value' data-url='?trigger=");
			html += String(i)+"'>"+String(_settings.config.triggers.list[i].on_value);
			html += F("</a> : <a class='editable-num' href='#' title='Off value' data-name='trigger_off_value' data-url='?trigger=");
			html += String(i)+"'>"+String(_settings.config.triggers.list[i].off_value);
		html += F("</a></div>");
	}
	html += F("</div>");

	return html;
}
