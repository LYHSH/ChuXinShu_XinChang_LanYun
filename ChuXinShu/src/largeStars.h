#pragma once
#include "ofMain.h"
#include "ofxEasing.h"
#include "myContants.h"
/************************************************************************/
/* file:∂Øª≠∂‘œÛ
/* date:2019.8.12
/* author: hui
/************************************************************************/
class largeStars
{
public:
	largeStars();
	~largeStars();

	void doShowing(ofImage * _tex,ofRectangle _birthRect);
	void doHiding();

	void setup();
	void update();
	void draw();
private:
	ofImage * _pTex;
	ofRectangle birthRect;
	ofRectangle rect;

	ofRectangle targetRect;

	float initTime;
};

