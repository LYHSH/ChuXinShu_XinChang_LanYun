#pragma once
#include "ofMain.h"
#include "ofxEasing.h"
#include "myContants.h"
#include "ofxTweenzor.h"
/************************************************************************/
/* file:
/* date:2019.8.11
/* author: hui
/************************************************************************/
class showItem
{
public:
	showItem();
	~showItem();

	void setup(ofImage * _p,ofVec2f _pos);
	void setup(ofImage * _p, ofRectangle _rect);
	void update();
	void draw();

	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	bool mouseReleased(int x, int y, int button);

	ofImage * getTex();
	ofRectangle getRect();

	bool isOut();
private:
	ofRectangle rect;

	ofImage * pTex;
	ofVec2f pos;
	float w, h;

	ofVec2f vec;

	float size;
	float const normaleSize = 1.0f;
	float const selectSize = 1.1f;

	float duration = 0.1f;
};

