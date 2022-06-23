/*
 * BoardSettingsView.h
 */

#ifndef CLASSES_VIEWS_BOARDSETTINGSVIEW_H_
#define CLASSES_VIEWS_BOARDSETTINGSVIEW_H_

#include "../../settings/Settings.h"
#include "../../equipment/Board.h"

class BoardSettingsView {
public:
	BoardSettingsView();

	String printPage();
	String printI2cDevices();
private:
	Settings& _settings = Settings::Instance();
	Board _board;
};

#endif /* CLASSES_VIEWS_BOARDSETTINGSVIEW_H_ */
