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
	void setup(ofImage * _p, ofRectangle _rect,vector<string> _texts);
	void setBackTex(ofImage * _tex);
	void update();
	void update(const ofVec2f &  _vec);
	void draw();

	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);

	bool isTouch(int _x,int _y);

	ofImage * getTex();
	ofRectangle getRect();

	bool isOut();

	vector<string> getTexts();
private:
	ofRectangle rect;
	ofImage * backTex;
	ofImage * pTex;
	vector<string> texts;
	ofVec2f pos;
	float w, h;
	const float boardSpaceDensity = 0.065f;		//±ß¿ò±ÈÀý

	ofVec2f vec;

	float size;
	float const normaleSize = 1.0f;
	float const selectSize = 1.1f;

	float duration = 0.1f;
};

