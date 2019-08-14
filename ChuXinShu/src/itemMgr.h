#pragma once
#include "myContants.h"
#include "showItem.h"
#include "largeStars.h"
/************************************************************************/
/* file:
/* date:2019.8.14
/* author: hui
/************************************************************************/
class itemMgr
{
public:
	itemMgr();
	~itemMgr();

	void setup();
	void update();
	void draw();

	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);

	void reset();
private:
	list<showItem *> items;

	vector<ofRectangle> birthRects;

	showItem * createItem();

	vector<ofImage> imgs;

	largeStars star;
};

