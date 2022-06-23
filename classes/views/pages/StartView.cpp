/*
 * StartView.cpp
 */

#include "StartView.h"

StartView::StartView() {}

String StartView::printPage()
{
	String html = "";

	html += F("<!DOCTYPE HTML>"
	"<html>"
	"<head>"
	"<title>IoT board</title>"
	"<meta name='viewport' content='width=device-width, initial-scale=1'>"
	"</head>"
	"<body>"
	"<div>"
	"<form action='/' method='POST'>"
	"<label>Login: </label>");
	html += "<input type='text' name='login' maxlength='16' value='"+String(_settings.config.login.value)+"'>";
	html += F("<br><label>Password: </label><input type='password' name='password' minlength='8' maxlength='16' value='");
	html += String(_settings.config.password.value);
	html += F("'><br><label>Ssid: </label><input type='text' name='ssid' maxlength='16' value='");
	html += String(_settings.config.ssid.value);
	html += F("'><br><label>Wifi password: </label><input type='password' name='wifi_password' minlength='8' maxlength='16' value='");
	html += String(_settings.config.wifi_password.value);
	html += F("'><br><label>Ip: </label><input type='text' name='ip' maxlength='15' value='");
	html += _help.charToString(_settings.config.ip.value,".");
	html += F("'><br><label>Gateway: </label><input type='text' name='gateway' maxlength='15' value='");
	html += _help.charToString(_settings.config.gateway.value,".");
	html += F("'><br><label>Subnet: </label><input type='text' name='subnet' maxlength='15' value='");
	html += _help.charToString(_settings.config.subnet.value,".");
	html += F("'><br><label>Access point: </label>"
	"<input type='checkbox' name='ap'><br>"
	"<button type='submit'>Apply</button>"
	"</form>"
	"</div>"
	"</body>"
	"</html>");

	return html;
}

String StartView::printRedirect()
{
	String html = "";

	html += F("<html>"
	"<head>"
	"<title>IoT board</title>"
	"<meta name='viewport' content='width=device-width, initial-scale=1'>"
	"<script type='text/javascript'>setTimeout(function(){"
		"window.location = 'http://");
		html += _help.charToString(_settings.config.ip.value,".");
		html += F("';"
	"},60000);</script>"
	"</head>"
	"<body>"
	"Applying..."
	"</body>"
	"</html>");

	return html;
}

