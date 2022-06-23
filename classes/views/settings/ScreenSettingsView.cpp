/*
 * ScreenSettingsView.cpp
 */

#include "ScreenSettingsView.h"

ScreenSettingsView::ScreenSettingsView() {}

String ScreenSettingsView::printPage()
{
	String html = "";

	String positions = F("[{value:0,text:\"\"}");
	for(byte i=0;i<_screen.POSITIONS_COUNT;i++){
		positions += ",{value:"+String(i+1)+",text:\"P"+String(i+1)+"\"}";
	}
	positions += F("]");

	String sources = F("[{value:\"/{type:0,number:0}\",text:\"\"},");

	if(_clock.exists())
		sources += F("{value:\"/{type:1,number:1}\",text:\"CLOCK\"}");
	for(byte i=0;i<_settings.SENSORS_COUNT;i++){
		if(_settings.checkSensor(i))
			sources += ",{value:\"/{type:2,number:"+String(i+1)+"}\",text:\"S"+String(i+1)+"\"}";
	}
	sources += F("]");

	html += F("<script type='text/javascript'>"
		"$(document).ready(function(){"
			"installEditable();"
		"});"
	"</script>"

	"<div class='panel-body'>");
	for(byte i=0;i<_settings.SCREEN_COUNT;i++){
		html += F("<div><i class='toggle glyphicon glyphicon-off ");
			html += String(_settings.config.screen.list[i].enabled==1?"glyphicon-green":"");
			html += F("' title='Enable' data-name='screen_enabled' data-url='?screen=");
			html += String(i);
			html += F("' role='button'></i> <a class='editable' href='#' title='Name' data-name='screen_name' data-url='?screen=");
			html += String(i)+"'>"+String(_settings.config.screen.list[i].name);
			html += F("</a> : <a class='editable-select' href='#' title='Source' data-name='screen_source' data-url='?screen=");
			html += String(i)+"' data-value='/{type:"+String(_settings.config.screen.list[i].source_type)+",number:"+String(_settings.config.screen.list[i].source_number)+"}' data-source='"+sources;
			html += F("'></a> : <a class='editable-select' href='#' title='Position' data-name='screen_position' data-url='?screen=");
			html += String(i)+"' data-value='"+String(_settings.config.screen.list[i].position)+"' data-source='"+positions;
		html += F("'></a></div>");
	}
	html += F("</div>");

	return html;
}
