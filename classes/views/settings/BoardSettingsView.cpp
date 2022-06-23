/*
 * BoardSettingsView.cpp
 */

#include "BoardSettingsView.h"

BoardSettingsView::BoardSettingsView(){}

String BoardSettingsView::printPage()
{
	String html = "";

	html += F("<script type='text/javascript'>"
		"$(document).ready(function(){"
			"installEditable();"
		"});"
	"</script>"

	"<div class='panel-body'>"
		"<button href='?reboot=1' class='btn btn-block btn-sm btn-warning' title='Reboot' onclick='$(\"#overlay\").css({\"pointer-events\":\"none\",\"opacity\":\"0.5\"});clickButton(this,false);'>REBOOT</button>"
		"<button href='?reset=1' class='btn btn-block btn-sm btn-danger' title='Settings Reset' onclick='if(confirm(\"Reset settings?\")){$(\"#overlay\").css({\"pointer-events\":\"none\",\"opacity\":\"0.5\"});clickButton(this,false);}'>RESET</button>"
		"<button href='?factory_reset=1' class='btn btn-block btn-sm btn-danger' title='Factory Reset' onclick='if(confirm(\"Reset to factory state? This will format filesystem!\")){$(\"#overlay\").css({\"pointer-events\":\"none\",\"opacity\":\"0.5\"});clickButton(this,false);}'>FACTORY RESET</button>"
		"<a href='/update' class='btn btn-block btn-sm btn-danger' title='Upload Firmware/Settings'>UPLOAD FW/SET</a>"
		"<a href='/i2c_devices' target='_blank' class='btn btn-block btn-sm btn-info' title='Log'>I2C DEVICES</a>"
		"<a href='/board_log' target='_blank' class='btn btn-block btn-sm btn-default' title='Log'>LOG</a>"
	"</div>");

	return html;
}

String BoardSettingsView::printI2cDevices()
{
	String html = "";

	int nDevices = 0;
	for(byte address = 1; address < 127; address++ ){
		if (_board.i2cDeviceExists(address))
		{
			char hexstr[5];
			sprintf(hexstr,"%x",address);
			html += F("I2C device found at address ");
			html += String(address)+" (0x"+String(hexstr)+")";
			html += F(".\n");

			nDevices++;
		}
	}
	if (nDevices == 0)
		html += F("No I2C devices found.\n");

	return html;
}
