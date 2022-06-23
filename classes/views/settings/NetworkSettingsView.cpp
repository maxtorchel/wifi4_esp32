/*
 * NetworkSettingsView.cpp
 *
 *  Created on: 25 янв. 2017 г.
 *      Author: maxtor
 */

#include "NetworkSettingsView.h"

NetworkSettingsView::NetworkSettingsView(){}

String NetworkSettingsView::printPage()
{
	String html = "";

	html += F("<script type='text/javascript'>"
		"$(document).ready(function(){"
			"installEditable();"
		"});"
	"</script>");

	html += F("<div class='panel-body'>"
		"<div>SSID: <a class='editable' href='#' data-name='ssid' data-url='/'>");
		html += String(_settings.config.ssid.value);
		html += F("</a></div>"
		"<div>WIFI PASSWORD: <a class='editable-password' href='#' data-name='wifi_password' data-url='/'>******</a></div>"
		"<hr/>");
		html += printRefresh(1);
		html += F("<hr/>"
		"<div>MAC: ");
		html += WiFi.macAddress();
		html += F("</div>"
		"<div>IP: <a class='editable-ip' href='#' data-name='ip' data-url='/'>");
		html += _help.charToString(_settings.config.ip.value,".");
		html += F("</a></div>"
		"<div>GATEWAY: <a class='editable-ip' href='#' data-name='gateway' data-url='/'>");
		html += _help.charToString(_settings.config.gateway.value,".");
		html += F("</a></div>"
		"<div>SUBNET: <a class='editable-ip' href='#' data-name='subnet' data-url='/'>");
		html += _help.charToString(_settings.config.subnet.value,".");
		html += F("</a></div>"
		"<div>DNS1: <a class='editable-ip' href='#' data-name='dns1' data-url='/'>");
		html += _help.charToString(_settings.config.dns1.value,".");
		html += F("</a></div>"
		"<div>DNS2: <a class='editable-ip' href='#' data-name='dns2' data-url='/'>");
		html += _help.charToString(_settings.config.dns2.value,".");
		html += F("</a></div>"
		"<div>PORT: <a class='editable-num' href='#' data-name='port' data-url='/'>");
		html += String(_settings.config.port.value);
		html += F("</a></div>"
		"<hr/>"
		"<div>LOGIN: <a class='editable' href='#' data-name='login' data-url='/'>");
		html += String(_settings.config.login.value);
		html += F("</a></div>"
		"<div>PASSWORD: <a class='editable-password' href='#' data-name='password' data-url='/'>******</a></div>"
		"<hr/>");
		html += printRefresh(2);
		html += F(
		"<div>NTP OFFSET: <a class='editable-num' title='Time zone offset seconds' href='#' data-name='ntp_offset' data-url='/'>");
		html += String(_settings.config.ntp.offset);
		html += F("</a></div>"
		"<div>NTP INTERVAL: <a class='editable-num' title='NTP update interval seconds' href='#' data-name='ntp_update_interval' data-url='/'>");
		html += String(_settings.config.ntp.interval);
		html += F("</a></div>"
	"</div>");
	return html;
}

String NetworkSettingsView::printRefresh(byte element)
{
	String html = "";

	switch (element){
		case 1:
			html += F("<div id='dhcp_ap_button' class='refreshable'>");
			if(_settings.config.ap.value!=1){
				if(_settings.config.dhcp.value==1)
					html += F("<button href='?dhcp=0' class='btn btn-block btn-sm btn-success' title='IP Address' onclick='clickButton(this,true);'>DHCP</button>");
				else
					html += F("<button href='?dhcp=1' class='btn btn-block btn-sm btn-warning' title='IP Address' onclick='clickButton(this,true);'>STATIC</button>");
			}
			if(_settings.config.ap.value==1)
				html += F("<button href='?ap=0' class='btn btn-block btn-sm btn-success' title='WiFi Mode' onclick='clickButton(this,true);'>ACCESS POINT</button>");
			else
				html += F("<button href='?ap=1' class='btn btn-block btn-sm btn-info' title='WiFi Mode' onclick='clickButton(this,true);'>CLIENT</button>");
			html += F("</div>");
			break;
		case 2:
			html += F("<div id='ntp_button' class='refreshable'>");
			if(_settings.config.ntp.value==1){
				html += F("<button href='?ntp=0' class='btn btn-block btn-sm btn-success' onclick='clickButton(this,true);'>NTP ON</button>");
				html += F("<button href='?ntp_update=1' class='btn btn-block btn-sm' onclick='clickButton(this,false);'>NTP UPDATE</button>");
			}else
				html += F("<button href='?ntp=1' class='btn btn-block btn-sm btn-warning' onclick='clickButton(this,true);'>NTP OFF</button>");
			html += F("</div>");
			break;
	}
	return html;
}
