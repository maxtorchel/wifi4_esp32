/*
 * UpdateView.h
 */

#ifndef CLASSES_VIEWS_UPDATEVIEW_H_
#define CLASSES_VIEWS_UPDATEVIEW_H_

#include "../../settings/Settings.h"
#include "../../Help.h"

class UpdateView {
public:
	UpdateView();

	String printPage();
	String printSuccessRedirect();
	String printErrorRedirect();
	String printUploadRedirect();
private:
	Settings& _settings = Settings::Instance();
	Help _help;

	String printRedirect(String url, String content, unsigned int timeout);
};

#endif /* CLASSES_VIEWS_UPDATEVIEW_H_ */
