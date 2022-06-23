/*
 * SchedulerSettingsView.cpp
 */

#include "SchedulerSettingsView.h"

SchedulerSettingsView::SchedulerSettingsView() {}

String SchedulerSettingsView::printPage()
{
	String html = "";

	String relays = F("[{value:0,text:\"\"}");
	for(byte i=0;i<_settings.RELAYS_COUNT;i++){
		if(_settings.checkRelay(i))
			relays += ",{value:"+String(i+1)+",text:\"R"+String(i+1)+"\"}";
	}
	relays += F("]");

	html += F("<script type='text/javascript'>"
		"$(document).ready(function(){"
			"installEditable();"
		"});"
	"</script>"

	"<div class='panel-body'>");
	for(byte i=0;i<_settings.SCHEDULER_COUNT;i++){
		String scheduleNumber = String(i+1);
		unsigned long start_time = _settings.config.scheduler.list[i].start_time;

		html += "<div>"
			"<i class='toggle glyphicon glyphicon-off "+String(_settings.config.scheduler.list[i].enabled==1?"glyphicon-green":"")+"' title='Enable' data-name='schedule_enabled' data-url='?schedule="+String(i)+"' role='button'></i> "
			"<i class='toggle glyphicon glyphicon-repeat "+String(_settings.config.scheduler.list[i].repeat==1?"glyphicon-green":"")+"' title='Repeat' data-name='schedule_repeat' data-url='?schedule="+String(i)+"' role='button'></i> ";
			html += F("SC");
			html += scheduleNumber;
			html += F(" - <a class='editable' href='#' title='Name' data-name='schedule_name' data-url='?schedule=");
			html += String(i)+"'>"+String(_settings.config.scheduler.list[i].name);
			html += F("</a> : <a class='editable-select' href='#' title='Relay' data-name='schedule_relay' data-url='?schedule=");
			html += String(i)+"' data-value='"+String(_settings.config.scheduler.list[i].relay)+"' data-source='"+relays;
			html += F("'></a> : <a class='editable-datetime' href='#' title='Start time' data-name='schedule_start_time' data-value='");
			html += (start_time!=0?_clock.getDateTimeString(start_time):"")+"' data-url='?schedule="+String(i)+"'>"
				+(start_time!=0?_clock.getTimeString(start_time):"00:00");
			html += F("</a> | <a class='editable-num' href='#' title='On seconds' data-name='schedule_on_seconds' data-url='?schedule=");
			html += String(i)+"'>"+String(_settings.config.scheduler.list[i].on_seconds);
			html += F("</a> : <a class='editable-num' href='#' title='Off seconds' data-name='schedule_off_seconds' data-url='?schedule=");
			html += String(i)+"'>"+String(_settings.config.scheduler.list[i].off_seconds);
		html += F("</a></div>");
	}
	html += F("<hr><a href='/scheduler_log' target='_blank' class='btn btn-block btn-sm btn-default' title='Log'>LOG</a></div>");

	return html;
}
