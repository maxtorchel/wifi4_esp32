/*
 * UpdateView.cpp
 */

#include <FS.h>
#include <SPIFFS.h>

#include "UpdateView.h"

UpdateView::UpdateView() {}

String UpdateView::printPage()
{
	String html = "";

	html += F("<!DOCTYPE HTML>"
	"<html>"
	"<head>"
	"<title>IoT board</title>"
	"<meta name='viewport' content='width=device-width, initial-scale=1'>"
	"</head>"
	"<body>"
	"<div>");

	html += F("<div><form method='POST' action='/updateFirmware' enctype='multipart/form-data'>"
			"<label>Firmware: </label>"
			"<input type='file' name='firmware'>"
			"<button type='submit'>Update</button>"
			"<span> (Current: ");
			html += String(_settings.config.version.value);
			html += F(")</span>"
			"</form></div>");

	html += F("<div><form method='POST' action='/updateSettings' enctype='multipart/form-data'>"
			"<label>Settings: </label>"
			"<input type='file' name='settings'>"
			"<button type='submit'>Apply</button>"
			" <a href='/settings.json' title='Download settings'>Download</a>"
			"</form>"
			"</div><hr>");

	html += F("<div><form method='POST' action='/upload?file=jquery.js' enctype='multipart/form-data'>"
			"<label><a href='http://code.jquery.com/jquery-latest.min.js'>JqueryJs</a>: </label>"
			"<input type='file' name='jqueryJs'>"
			"<button type='submit'>Upload</button>");
			if(SPIFFS.exists(F("/jquery.js")))
				html += F(" <a href='/download?file=jquery.js' title='Download jquery.js'>Download</a> <a href='/delete?file=jquery.js' title='Delete jquery.js'>Delete</a>");
			html += F("</form>"
			"</div>");

	html += F("<div><form method='POST' action='/upload?file=bootstrap.js' enctype='multipart/form-data'>"
			"<label><a href='http://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js'>BootstrapJs</a>: </label>"
			"<input type='file' name='bootstrapJs'>"
			"<button type='submit'>Upload</button>");
			if(SPIFFS.exists(F("/bootstrap.js")))
				html += F(" <a href='/download?file=bootstrap.js' title='Download bootstrap.js'>Download</a> <a href='/delete?file=bootstrap.js' title='Delete bootstrap.js'>Delete</a>");
			html += F("</form>"
			"</div>");

	html += F("<div><form method='POST' action='/upload?file=bootstrap-editable.js' enctype='multipart/form-data'>"
			"<label><a href='http://cdnjs.cloudflare.com/ajax/libs/x-editable/1.5.0/bootstrap3-editable/js/bootstrap-editable.min.js'>BootstrapEditableJs</a>: </label>"
			"<input type='file' name='bootstrapEditableJs'>"
			"<button type='submit'>Upload</button>");
			if(SPIFFS.exists(F("/bootstrap-editable.js")))
				html += F(" <a href='/download?file=bootstrap-editable.js' title='Download bootstrap-editable.js'>Download</a> <a href='/delete?file=bootstrap-editable.js' title='Delete bootstrap-editable.js'>Delete</a>");
			html += F("</form>"
			"</div>");

	html += F("<div><form method='POST' action='/upload?file=jquery-mask.js' enctype='multipart/form-data'>"
			"<label><a href='http://cdnjs.cloudflare.com/ajax/libs/jquery.mask/1.14.8/jquery.mask.min.js'>JqueryMaskJs</a>: </label>"
			"<input type='file' name='jqueryMaskJs'>"
			"<button type='submit'>Upload</button>");
			if(SPIFFS.exists(F("/jquery-mask.js")))
				html += F(" <a href='/download?file=jquery-mask.js' title='Download jquery-mask.js'>Download</a> <a href='/delete?file=jquery-mask.js' title='Delete jquery-mask.js'>Delete</a>");
			html += F("</form>"
			"</div>");

	html += F("<div><form method='POST' action='/upload?file=bootstrap.css' enctype='multipart/form-data'>"
			"<label><a href='http://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css'>BootstrapCss</a>: </label>"
			"<input type='file' name='bootstrapCss'>"
			"<button type='submit'>Upload</button>");
			if(SPIFFS.exists(F("/bootstrap.css")))
				html += F(" <a href='/download?file=bootstrap.css' title='Download bootstrap.css'>Download</a> <a href='/delete?file=bootstrap.css' title='Delete bootstrap.css'>Delete</a>");
			html += F("</form>"
			"</div>");

	html += F("<div><form method='POST' action='/upload?file=bootstrap-editable.css' enctype='multipart/form-data'>"
			"<label><a href='http://cdnjs.cloudflare.com/ajax/libs/x-editable/1.5.0/bootstrap3-editable/css/bootstrap-editable.css'>BootstrapEditableCss</a>: </label>"
			"<input type='file' name='bootstrapEditableCss'>"
			"<button type='submit'>Upload</button>");
			if(SPIFFS.exists(F("/bootstrap-editable.css")))
				html += F(" <a href='/download?file=bootstrap-editable.css' title='Download bootstrap-editable.css'>Download</a> <a href='/delete?file=bootstrap-editable.css' title='Delete bootstrap-editable.css'>Delete</a>");
			html += F("</form>"
			"</div>");

	html += F("<br><br><a href='/'>main</a>");

	html += F("</div>"
	"</body>"
	"</html>");

	return html;
}

String UpdateView::printSuccessRedirect()
{
	return printRedirect(_help.charToString(_settings.config.ip.value,"."), F("Uploading..."), 60000);
}
String UpdateView::printErrorRedirect()
{
	return printRedirect(_help.charToString(_settings.config.ip.value,"."), F("Uploading failed! Rebooting..."), 30000);
}
String UpdateView::printUploadRedirect()
{
	return printRedirect(_help.charToString(_settings.config.ip.value,".")+"/update", "", 0);
}
String UpdateView::printRedirect(String url, String content, unsigned int timeout)
{
	String html = "";

	html += F("<!DOCTYPE HTML>"
	"<html>"
	"<head>"
	"<title>IoT board</title>"
	"<meta name='viewport' content='width=device-width, initial-scale=1'>"
	"<script type='text/javascript'>"
		"setTimeout(function(){"
			"window.location = 'http://");
			html += url+"';";
		html += "},"+String(timeout)+");";
	html += F("</script>"
	"</head>"
	"<body>");
	html += content;
	html += F("</body>"
	"</html>");

	return html;
}

