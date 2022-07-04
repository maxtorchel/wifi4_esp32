/*
 * RelaysSettingsView.cpp
 */

#include "RelaysSettingsView.h"

RelaysSettingsView::RelaysSettingsView(){}

String RelaysSettingsView::printPage()
{
	String html = "";
	String pins = F("["
					  "{value:0,text:\"\"},"
					  "{value:2,text:\"D2\"},"
					  "{value:4,text:\"D4\"},"
					  "{value:13,text:\"D13\"},"
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
	for(byte i=0;i<_settings.RELAYS_COUNT;i++){
		String relayNumber = String(i+1);
		html += F("<div><i class='toggle glyphicon glyphicon-off ");
			html += String(_settings.config.relays.list[i].enabled==1?"glyphicon-green":"");
			html += F("' title='Enable' data-name='relay_enabled' data-url='?relay=");
			html += String(i);
			html += F("' role='button'></i> <i class='toggle glyphicon glyphicon-random ");
			html += String(_settings.config.relays.list[i].inverse==1?"glyphicon-green":"");
			html += F("' title='Inverse' data-name='relay_inverse' data-url='?relay=");
			html += String(i);
			html += F("' role='button'></i> R");
			html += relayNumber;
			html += F(" - <a class='editable-select' href='#' title='Pin' data-name='relay_pin' data-url='?relay=");
			html += String(i)+"' data-value='"+String(_settings.config.relays.list[i].pin)+"' data-source='"+pins;
			html += F("'></a> : <a class='editable' href='#' title='Name' data-name='relay_name' data-url='?relay=");
			html += String(i)+"'>"+String(_settings.config.relays.list[i].name);
			html += F("</a> | <a class='editable' href='#' title='Host' data-name='relay_host' data-url='?relay=");
			html += String(i)+"'>"+String(_settings.config.relays.list[i].host);
		html += F("</a></div>");
	}
	html += F("<hr><a href='/relay_log' target='_blank' class='btn btn-block btn-sm btn-default' title='Log'>LOG</a></div>");

	return html;
}
