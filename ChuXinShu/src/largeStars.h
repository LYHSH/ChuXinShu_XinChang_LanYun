#pragma once
#include "ofMain.h"
#include "ofxEasing.h"
#include "myContants.h"
#include "ofxTweenzor.h"
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

	void mousePressed(int x, int y, int button);

	bool isMasking();
	bool isMaskFulling();
private:
	ofImage * _pTex;
	ofRectangle birthRect;
	ofRectangle rect;
	ofRectangle targetRect;

	float alpha = 0.0f;

	const float duration = 1.0f;
	const float fullMaskAlpha = 180.0f;
};

