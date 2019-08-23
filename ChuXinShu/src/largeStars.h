#pragma once
#include "ofMain.h"
#include "ofxEasing.h"
#include "myContants.h"
#include "ofxTweenzor.h"
#include "ofxTrueTypeFontUC.h"
/************************************************************************/
/* file:动画对象
/* date:2019.8.12
/* author: hui
/************************************************************************/
class largeStars
{
public:
	largeStars();
	~largeStars();

	void doShowing(ofImage * _tex,ofRectangle _birthRect);
	void doShowing(ofImage * _tex, ofRectangle _birthRect, ofImage * _backTex, vector<string> _texts);
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

	ofImage * backTex;
	ofImage * textBackTex;
	ofRectangle textRect;
	ofRectangle textRect1;
	vector<string> texts;

	ofImage closeTex;

	const float boardSpaceDensity = 0.065f;		//边框比例

	float alpha = 0.0f;

	const float duration = 1.0f;
	const float fullMaskAlpha = 180.0f;

	void onComplete(float* arg);

	ofxTrueTypeFontUC font;
};

