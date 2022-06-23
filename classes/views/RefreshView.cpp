/*
 * RefreshView.cpp
 *
 *  Created on: 25 янв. 2017 г.
 *      Author: maxtor
 */

#include "RefreshView.h"

RefreshView::RefreshView(){}

String RefreshView::printPage()
{
	String html = "";

	html += F("<div id='refresh_elements'>");

	IndexView index;
	for(byte i=1;i<=IndexView::REFRESH_COUNT;i++){
		html += index.printRefresh(i);
	}

	NetworkSettingsView networkSettings;
	for(byte i=1;i<=NetworkSettingsView::REFRESH_COUNT;i++){
		html += networkSettings.printRefresh(i);
	}

	html += F("</div>");

	return html;
}
