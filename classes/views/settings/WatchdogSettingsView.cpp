/*
 * WatchdogSettingsView.cpp
 *
 *  Created on: 16 мая 2017 г.
 *      Author: maxtor
 */

#include "WatchdogSettingsView.h"

WatchdogSettingsView::WatchdogSettingsView() {}

String WatchdogSettingsView::printPage()
{
	String html = "";

	html += F("<script type='text/javascript'>"
		"$(document).ready(function(){"
			"installEditable();"
		"});"
	"</script>"

	"<div class='panel-body'>");
		html += F("<div>HOST: <a class='editable' href='#' data-name='watchdog_host' data-url='/'>");
		html += String(_settings.config.watchdog.host);
		html += F("</a></div><div>INTERVAL: <a class='editable-num' href='#' data-name='watchdog_interval' data-url='/'>");
		html += String(_settings.config.watchdog.interval);
		html += F("</a></div><div>TRY COUNT: <a class='editable-num' href='#' data-name='watchdog_try_count' data-url='/'>");
		html += String(_settings.config.watchdog.try_count);
	html += F("</a></div></div>");

	return html;
}
