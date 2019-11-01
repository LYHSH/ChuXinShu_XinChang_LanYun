#pragma once
#include "myContants.h"
#include "showItem.h"
#include "largeStars.h"
#include "ofxXmlSettings.h"
#include "ofxTweenzor.h"
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
	void doTweenVec();
	string debugMessage()const;
private:
	struct ITEM_DATA
	{
		vector<string> texts;
		ofImage * tex;
	};

	vector<ITEM_DATA> itemDatas;
	ofImage itemBacktex;

	int nextIndex = 0;
	float const imgWidth = 550.0f;
	float const boundSpace = 30.0f;
	float middleX = 0.0f;
	float lastRandomX = 0.0f;
	float minBirthx = 0.0f;
	float maxBirthx = 0.0f;


	list<showItem *> items;

	ofRectangle randomBirthRect;

	void loadData();

	showItem * createItem();

	largeStars star;


	ofVec2f vec;
};

