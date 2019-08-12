#pragma once
#include "ofMain.h"
#include "ofxEasing.h"
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
	void update();
	void draw();

	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	bool mouseReleased(int x, int y, int button);

	ofImage * getTex();
	ofRectangle getRect();

private:
	ofRectangle rect;

	ofImage * pTex;
	ofVec2f pos;
	float w, h;

	float initTime;

	bool isTouching; 

	float size;
	float touchSize;
};

