/*
 * IndexView.cpp
 */

#include <algorithm>
#include <vector>
#include <FS.h>
#include <SPIFFS.h>

#include "IndexView.h"

IndexView::IndexView(){}

String IndexView::printPage()
{
	String html = "";
	String jqueryJs = SPIFFS.exists("/jquery.js")?"/download?file=jquery.js":"http://code.jquery.com/jquery-latest.min.js";
	String bootstrapJs = SPIFFS.exists("/bootstrap.js")?"/download?file=bootstrap.js":"http://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js";
	String bootstrapEditableJs = SPIFFS.exists("/bootstrap-editable.js")?"/download?file=bootstrap-editable.js":"http://cdnjs.cloudflare.com/ajax/libs/x-editable/1.5.0/bootstrap3-editable/js/bootstrap-editable.min.js";
	String jqueryMaskJs = SPIFFS.exists("/jquery-mask.js")?"/download?file=jquery-mask.js":"http://cdnjs.cloudflare.com/ajax/libs/jquery.mask/1.14.8/jquery.mask.min.js";
	String bootstrapCss = SPIFFS.exists("/bootstrap.css")?"/download?file=bootstrap.css":"http://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css";
	String bootstrapEditableCss = SPIFFS.exists("/bootstrap-editable.css")?"/download?file=bootstrap-editable.css":"http://cdnjs.cloudflare.com/ajax/libs/x-editable/1.5.0/bootstrap3-editable/css/bootstrap-editable.css";

	html += F("<!DOCTYPE HTML>"
	"<html>"
	"<head>"
	"<meta charset='utf-8'>"
	"<meta name='viewport' content='width=device-width, initial-scale=1'>"
	"<title>Relay control page</title>");
	html += "<script src='"+jqueryJs+"' type='text/javascript'></script>";
	html += "<script src='"+bootstrapJs+"' type='text/javascript'></script>";
	html += "<script src='"+bootstrapEditableJs+"' type='text/javascript'></script>";
	html += "<script src='"+jqueryMaskJs+"' type='text/javascript'></script>";
	html += "<link href='"+bootstrapCss+"' type='text/css' rel='stylesheet'/>";
	html += "<link href='"+bootstrapEditableCss+"' type='text/css' rel='stylesheet'/>";
	html += F("<script type='text/javascript'>"
		"var refreshing = false;"
	    "$(document).ready(function(){"
			"refreshTimer();"
			"installEditable();"
            "$('.collapse').on('show.bs.collapse', function(){"
                "$(this).load($(this).attr('href'));"
    		"});"
		"});"
		"function clickButton(el,disable){"
			"$(el).prop('disabled',disable);"
			"$.get($(el).attr('href'), function(){"
				"refresh();"
			"});"
		"}"
		"function refreshTimer(){"
			"setTimeout(function(){"
				"refresh();"
				"refreshTimer();"
			"},10000);"
		"}"
		"function refresh(){"
			"if(!refreshing){"
				"refreshing=true;"
				"$.ajax({"
					"type: 'GET',"
					"url: '/refresh',"
					"success: function(data){"
						"$('.refreshable').each(function () {"
							"$(this).html($(data).find('#'+$(this).attr('id')).html());"
						"});"
						"$('#overlay').css({'pointer-events':'auto','opacity':'1'});"
						"refreshing=false;"
					"},"
					"error: function(){"
						"refreshing=false;"
					"}"
				"});"
			"}"
		"}"
		"$.fn.editable.defaults.ajaxOptions = {"
			"type: 'GET'"
		"};"
		"$.fn.editable.defaults.send = 'always';"
		"$.fn.editable.defaults.params = function(params) {"
			"params[params.name] = params.value.replace('/','');"
			"params.pk = undefined;"
			"params.name = undefined;"
			"params.value = undefined;"
			"return params;"
		"};"
		"function installEditable() {"
			"$('.editable').editable({tpl: '<input type=\"text\" class=\"text\" maxlength=\"16\">'});"
			"$('.editable-password').editable({tpl: '<input type=\"text\" class=\"text\" minlength=\"8\" maxlength=\"16\">'});"
			"$('.editable-num').editable({tpl: '<input type=\"text\" class=\"num\" maxlength=\"8\">', emptytext: '0'});"
			"$('.editable-ip').editable({tpl: '<input type=\"text\" class=\"ip\" maxlength=\"15\">'});"
			"$('.editable-select').editable({"
				"type: 'select',"
				"placement: 'left',"
				"source: function(){return $.parseJSON($(this).attr('data-source'));}"
			"});"
			"$('.editable-datetime').editable({"
				"tpl: '<input type=\"text\" class=\"datetime\" maxlength=\"16\">',"
				"placement: 'left',"
				"display: function(value) {"
					"if(value){"
						"var dateTimeParts = value.split(' ');"
						"$(this).text(dateTimeParts[1]);"
					"}else{"
						"$(this).text('00:00');"
					"}"
				"},"
				"params: function(params) {"
					"if(params.value){"
						"var dateString = params.value,"
							"dateTimeParts = dateString.split(' '),"
							"timeParts = dateTimeParts[1].split(':'),"
							"dateParts = dateTimeParts[0].split('.'),"
							"date;"
						"date = new Date(dateParts[2], parseInt(dateParts[1], 10) - 1, dateParts[0], timeParts[0], timeParts[1]);"

						"params[params.name] = date.getTime()/1000 - date.getTimezoneOffset()*60;"
					"}else{"
						"params[params.name] = 0;"
					"}"
					"params.pk = undefined;"
					"params.name = undefined;"
					"params.value = undefined;"
					"return params;"
				"}"
			"});"
		"}"
		"$(document).on('focus', '.ip', function () {"
			"$(this).mask('099.099.099.099', {clearIfNotMatch: true});"
		"});"
		"$(document).on('focus', '.num', function () {"
			"$(this).mask('09999Z99',{"
				"translation:  {"
					"'Z': {pattern: /\./, optional: true}"
				"}"
			"});"
		"});"
		"$(document).on('focus', '.datetime', function () {"
			"$(this).mask('00.00.0000 00:00', {placeholder: '00.00.0000 00:00', clearIfNotMatch: true});"
		"});"
		"$(document).on('focus', '.text', function () {"
			"$(this).mask('ZZZZZZZZZZZZZZZZ',{"
				"translation:  {"
					"'Z': {pattern: /[a-zA-Z0-9-_ .]/, optional: true}"
				"}"
			"});"
		"});"
		"$(document).on('click', 'i.toggle', function(){"
			"var enabled = $(this).hasClass('glyphicon-green');"
			"$.ajax({"
				"url: $(this).attr('data-url')+'&'+$(this).attr('data-name')+'='+(enabled?'0':'1'),"
				"context: this,"
				"success: function(){"
					"enabled?$(this).removeClass('glyphicon-green'):$(this).addClass('glyphicon-green');"
				"}"
			"});"
		"});"
	"</script>"
	"<style type='text/css'>"
		"div.panel-body div{"
			"white-space:nowrap;"
		"}"
		"a.noborder, a.noborder:hover{"
			"text-decoration: none;"
			"border-bottom: none;"
		"}"
		"i.glyphicon-green{"
			"color:limegreen;"
		"}"
	"</style>"
	"</head>"
	"<body>"

	  "<div class='container-fluid'>"
		  "<!--content-->"
		  "<div class='row' style='padding-top: 20px;' id='overlay'>"

		    "<div class='col-md-2'>"
			  "<div class='row'>"
				"<div class='col-md-12'>");

					html += printRefresh(5);

				html += F("</div>"
			  "</div>"
			"</div>"

		    "<div class='col-md-6'>"
			  "<div class='row'>"
				  "<div class='col-md-12'>"
					"<div class='col-md-6 col-md-offset-3'>"
					  "<h4 class='text-center'>RELAY LIST</h4>"
					  "<hr/>"
				  "</div>"
				"</div>"
			  "</div>");

			html += printRefresh(1);

			html += F("</div>"
			"<div class='col-md-4'>"
			  "<div class='row text-center pull-left' style='margin-left: 0;'>");
				html += F("<h5>");
				html += printRefresh(4);
				html += F("</h5>");
			  html += F("</div>"

			  "<div class='row text-center pull-right' style='margin-right: 0;'>");
				if(_board.clock.exists()){
					html += F("<h5>");
					html += printRefresh(3);
					html += F(" <a class='editable-datetime noborder' href='#' data-name='datetime' data-display='false' data-url='/'>"
							   "<i class='glyphicon glyphicon-time' title='Set date and time'></i>"
							"</a>"
					"</h5>");
				}
			  html += F("</div>"
			  "<div class='row'>"

				"<div class='col-md-12'>"

					"<div class='panel-group' id='settings'>"

						"<div class='panel panel-default'>"
							"<div id='relays_header' class='text-center panel-heading'  data-toggle='collapse' data-parent='#settings' href='#relays_collapse' role='button'>"
								"RELAYS"
							"</div>"
							"<div id='relays_collapse' href='/relays_settings' class='panel-collapse collapse'>"
							"</div>"
						"</div>"

						"<div class='panel panel-default'>"
							"<div id='sensors_header' class='text-center panel-heading'  data-toggle='collapse' data-parent='#settings' href='#sensors_collapse' role='button'>"
								"SENSORS"
							"</div>"
							"<div id='sensors_collapse' href='/sensors_settings' class='panel-collapse collapse'>"
							"</div>"
						"</div>"

						"<div class='panel panel-default'>"
							"<div id='triggers_header' class='text-center panel-heading'  data-toggle='collapse' data-parent='#settings' href='#triggers_collapse' role='button'>"
								"TRIGGERS"
							"</div>"
							"<div id='triggers_collapse' href='/triggers_settings' class='panel-collapse collapse'>"
							"</div>"
						"</div>");

					  	if(_board.clock.exists()){
					  		html += F("<div class='panel panel-default'>"
								"<div id='scheduler_header' class='text-center panel-heading'  data-toggle='collapse' data-parent='#settings' href='#scheduler_collapse' role='button'>"
									"SCHEDULER"
								"</div>"
								"<div id='scheduler_collapse' href='/scheduler_settings' class='panel-collapse collapse'>"
								"</div>"
							"</div>");
					  	}

						if(_board.screen.exists()){
							html += F("<div class='panel panel-default'>"
								"<div id='screen_header' class='text-center panel-heading'  data-toggle='collapse' data-parent='#settings' href='#screen_collapse' role='button'>"
									"SCREEN"
								"</div>"
								"<div id='screen_collapse' href='/screen_settings' class='panel-collapse collapse'>"
								"</div>"
							"</div>");
						}

						html += F("<div class='panel panel-default'>"
							"<div id='watchdog_header' class='text-center panel-heading' data-toggle='collapse' data-parent='#settings' href='#watchdog_collapse' role='button'>"
								"WATCHDOG"
							"</div>"
							"<div id='watchdog_collapse' href='/watchdog_settings' class='panel-collapse collapse'>"
							"</div>"
						"</div>"

						"<div class='panel panel-default'>"
							"<div id='network_header' class='text-center panel-heading' data-toggle='collapse' data-parent='#settings' href='#network_collapse' role='button'>"
								"NETWORK"
							"</div>"
							"<div id='network_collapse' href='/network_settings' class='panel-collapse collapse'>"
							"</div>"
						"</div>"

						"<div class='panel panel-default'>");
							html += printRefresh(2);
							html += F("<div id='board_collapse' href='/board_settings' class='panel-collapse collapse'>"
							"</div>"
						"</div>"

					"</div>"

				"</div>"
			  "</div>"

			"</div>"
		  "</div>"
		  "<!--content-->"
	  "</div>"

	"</body>"
	"</html>");

	return html;
}

String IndexView::printRefresh(byte element)
{
	String html = "";

	switch (element){
		case 1:
			html += F("<div id='relay_list' class='refreshable'>");
			for(byte i=0;i<_settings.RELAYS_COUNT;i++){
				String relayIndexString = String(i);
				String relayNumber = String(i+1);
				String relayName = String(_settings.config.relays.list[i].name);

				if(_settings.checkRelay(i)){
					html += F("<div class='row'>"
                    "<div class='col-md-12'>"
					  "<div class='col-md-3 btn'>"
						"<label class='pull-right'>");
							html += relayName;
						html += F("</label>"
					  "</div>"

					  "<div class='col-md-3'>");
						if(_settings.config.relays.list[i].state!=1){
							html += F("<button href='?switch=1&relay=");
							html += relayIndexString;
							html += F("' class='btn btn-block btn-default' onclick='clickButton(this,true);'>R");
							html += relayNumber;
							html += F(" OFF</button>");
						}else{
							html += F("<button href='?switch=0&relay=");
							html += relayIndexString;
							html += F("' class='btn btn-block btn-success' onclick='clickButton(this,true);'>R");
							html += relayNumber;
							html += F(" ON</button>");
						}
						html += F("</div>"

					  "<div class='col-md-3'>");
						if(_settings.config.relays.list[i].save!=1){
							html += F("<button href='?relay_remember=1&relay=");
							html += relayIndexString;
							html += F("' class='btn btn-default' onclick='clickButton(this,true);'>SAVE OFF</button>");
						}else{
						    html += F("<button href='?relay_remember=0&relay=");
							html += relayIndexString;
							html += F("' class='btn btn-success' onclick='clickButton(this,true);'>SAVE ON</button>");
						}
					  html += F("</div>"

					  "<div class='col-md-3'>");
						if(_settings.config.relays.list[i].watchdog!=1){
							html += F("<button href='?relay_watchdog=1&relay=");
							html += relayIndexString;
							html += F("' class='btn btn-default' onclick='clickButton(this,true);'>WATCHDOG OFF</button>");
						}else{
						    html += F("<button href='?relay_watchdog=0&relay=");
							html += relayIndexString;
							html += F("' class='btn btn-success' onclick='clickButton(this,true);'>WATCHDOG ON</button>");
						}
					  html += F("</div>"

                     "</div>"
					"</div>");
				}
			}
			html += F("</div>");
			break;
		case 2:
			html += F("<div id='board_header' class='text-center panel-heading refreshable'  data-toggle='collapse' data-parent='#settings' href='#board_collapse' role='button'>"
				"BOARD");
				if(_settings.NEED_REBOOT==1)
					html += F("<i class='glyphicon glyphicon-alert pull-right' style='color:orange;' title='Need Reboot'></i>");
				html += F("</div>");
			break;
		case 3:
			if(_board.clock.exists()){
				html += F("<span id='clock' class='refreshable'>");
					html += _board.clock.getDateTimeString();
				html += F("</span>");
			}
			break;
		case 4:
//			FSInfo fs_info;
//			SPIFFS.info(fs_info);
			html += F("<div id='memory' class='refreshable'>"
			   "<div><i class='glyphicon glyphicon-dashboard'></i> ");
					html += String((double)ESP.getFreeHeap()/1000);
					html += F("kB ");
					html += F("<i class='glyphicon glyphicon-hdd'></i> ");
					html += String((double)(SPIFFS.totalBytes()-SPIFFS.usedBytes())/1000);
					html += F("kB ");
				html += F("</div>"
			"</div>");
			break;
		case 5:
			html += F("<div id='sensors' class='panel-group refreshable'>");
			std::vector<String> groups;
			bool noGroup = false;
			for(byte i=0;i<_settings.SENSORS_COUNT;i++){
				if(_settings.checkSensor(i)){
					String group = String(_settings.config.sensors.list[i].group);
					if(group!=""){
						if(std::find(groups.begin(), groups.end(), group) == groups.end())
							groups.push_back(group);
					}else
						noGroup = true;
				}
			}

			for(byte i=0;i<groups.size();i++){
				String group = groups[i];
				html += F("<div class='panel panel-default'>"
					"<div class='text-center panel-heading'>");
						html += group;
					html += F("</div>"
					"<div class='panel-body'>");
					for(byte i=0;i<_settings.SENSORS_COUNT;i++){
						if(_settings.checkSensor(i) && String(_settings.config.sensors.list[i].group) == group){
							html += F("<div>");
								html += F("S");
								html += String(i+1);
								html += F(": ");
								html += String(_settings.config.sensors.list[i].name);
								html += F(" ");
								html += String(_board.sensors.getSensorValue(i));
								html += F(" ");
								html += _board.sensors.getSensorUnit(i);
							html += F("</div>");
						}
					}
					html += F("</div>"
				"</div>");
			}

			if(noGroup){
				html += F("<div class='panel panel-default'>"
					"<div class='panel-body'>");
					for(byte i=0;i<_settings.SENSORS_COUNT;i++){
						if(_settings.checkSensor(i) && String(_settings.config.sensors.list[i].group)==""){
							html += F("<div>");
								html += F("S");
								html += String(i+1);
								html += F(": ");
								html += String(_settings.config.sensors.list[i].name);
								html += F(" ");
								html += String(_board.sensors.getSensorValue(i));
								html += F(" ");
								html += _board.sensors.getSensorUnit(i);
							html += F("</div>");
						}
					}
					html += F("</div>"
				"</div>");
			}
			html += F("</div>");
			break;
	}

	return html;
}
