/*
 * StartView.h
 */

#ifndef CLASSES_VIEWS_STARTVIEW_H_
#define CLASSES_VIEWS_STARTVIEW_H_

#include "../../settings/Settings.h"
#include "../../Help.h"

class StartView {
public:
	StartView();

	String printPage();
	String printRedirect();
private:
	Settings& _settings = Settings::Instance();
	Help _help;
};

#endif /* CLASSES_VIEWS_STARTVIEW_H_ */
