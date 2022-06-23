/*
 * SensorsSettingsView.cpp
 */

#include "SensorsSettingsView.h"

SensorsSettingsView::SensorsSettingsView() {}

String SensorsSettingsView::printPage()
{
	String html = "";

	String types = F("[{value:0,text:\"\"},{value:2,text:\"Light");
		types += String(_board.i2cDeviceExists(74)?" +":" -");
		types += F("\"},{value:3,text:\"ATemp");
		types += String(_board.i2cDeviceExists(92)?" +":" -");
		types += F("\"},{value:4,text:\"AHumid");
		types += String(_board.i2cDeviceExists(92)?" +":" -");
		types += F("\"},{value:5,text:\"APress");
		types += String(_board.i2cDeviceExists(119)?" +":" -");
		types += F("\"},{value:6,text:\"WPress ?\"}"
		",{value:11,text:\"WLeak ?\"}"
	"]");

	String pins = F("["
					  "{value:0,text:\"\"},"
					  "{value:2,text:\"D2\"},"
					  "{value:4,text:\"D4\"},"
					  "{value:5,text:\"D5\"},"
					  "{value:13,text:\"D13\"},"
					  "{value:14,text:\"D14\"},"
					  "{value:15,text:\"D15\"},"
					  "{value:18,text:\"D18\"},"
					  "{value:19,text:\"D19\"},"
					  "{value:23,text:\"D23\"},"
					  "{value:25,text:\"D25\"},"
					  "{value:26,text:\"D26\"},"
					  "{value:27,text:\"D27\"},"
					  "{value:32,text:\"D32\"},"
					  "{value:33,text:\"D33\"},"
					  "{value:16,text:\"RX2\"},"
					  "{value:17,text:\"TX2\"},"
				  "]");

	html += F("<script type='text/javascript'>"
		"$(document).ready(function(){"
			"installEditable();"
		"});"
	"</script>"

	"<div class='panel-body'>");
	for(byte i=0;i<_settings.SENSORS_COUNT;i++){
		String sensorNumber = String(i+1);
		html += F("<div><i class='toggle glyphicon glyphicon-off ");
			html += String(_settings.config.sensors.list[i].enabled==1?"glyphicon-green":"");
			html += F("' title='Enable' data-name='sensor_enabled' data-url='?sensor=");
			html += String(i)+"' role='button'></i> S"+sensorNumber;
			html += F(" - <a class='editable-select' href='#' title='Type' data-name='sensor_type' data-url='?sensor=");
			html += String(i)+"' data-value='"+String(_settings.config.sensors.list[i].type)+"' data-source='"+types;
			html += F("'></a> : <a class='editable-select' href='#' title='Pin' data-name='sensor_pin' data-url='?sensor=");
			html += String(i)+"' data-value='"+String(_settings.config.sensors.list[i].pin)+"' data-source='"+pins;
			html += F("'></a> : <a class='editable' href='#' title='Name' data-name='sensor_name' data-url='?sensor=");
			html += String(i)+"'>"+String(_settings.config.sensors.list[i].name);
			html += F("</a> - <a class='editable' href='#' title='Group' data-name='sensor_group' data-url='?sensor=");
			html += String(i)+"'>"+String(_settings.config.sensors.list[i].group);
			html += F("</a> | <a class='editable-num' href='#' title='Log interval' data-name='sensor_log_interval' data-url='?sensor=");
			html += String(i)+"'>"+String(_settings.config.sensors.list[i].log_interval);
			html += F("</a> : <a class='editable' href='#' title='Host' data-name='sensor_host' data-url='?sensor=");
			html += String(i)+"'>"+String(_settings.config.sensors.list[i].host);
		html += F("</a></div>");
	}
	html += F("<hr><a href='/sensor_log' target='_blank' class='btn btn-block btn-sm btn-default' title='Log'>LOG</a></div>");

	return html;
}
