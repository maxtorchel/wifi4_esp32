/*
 * IndexView.h
 */

#ifndef CLASSES_VIEWS_INDEXVIEW_H_
#define CLASSES_VIEWS_INDEXVIEW_H_

#include "../../equipment/Board.h"

class IndexView {
public:
	IndexView();

	const static byte REFRESH_COUNT = 5;

	String printPage();
	String printRefresh(byte element);
private:
	Settings& _settings = Settings::Instance();
	Board _board;
};

#endif /* CLASSES_VIEWS_INDEXVIEW_H_ */
