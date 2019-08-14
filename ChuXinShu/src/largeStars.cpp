#include "largeStars.h"



largeStars::largeStars()
{
	_pTex = NULL;
}


largeStars::~largeStars()
{
}

void largeStars::setup()
{
	targetRect.set(0,0,SCREEN_W, SCREEN_H);

	isShowing = false;

	alpha = 0.0f;
}

void largeStars::update()
{
	auto duration = 1.0f;
	auto endTime = initTime + duration;
	auto now = ofGetElapsedTimef();
//	rect.x = ofxeasing::map_clamp(now, initTime, endTime, birthRect.x, targetRect.x, &ofxeasing::linear::easeIn);
//	rect.y = ofxeasing::map_clamp(now, initTime, endTime, birthRect.y, targetRect.y, &ofxeasing::linear::easeIn);
//	rect.width = ofxeasing::map_clamp(now, initTime, endTime, birthRect.width, targetRect.width, &ofxeasing::back::easeOut_s, 0.8);
//	rect.height = ofxeasing::map_clamp(now, initTime, endTime, birthRect.height, targetRect.height, &ofxeasing::back::easeOut_s, 0.8);


	rect.x = ofxeasing::map_clamp(now, initTime, endTime, birthRect.x, targetRect.x, &ofxeasing::back::easeOut_s, 0.8);
	rect.y = ofxeasing::map_clamp(now, initTime, endTime, birthRect.y, targetRect.y, &ofxeasing::back::easeOut_s, 0.8);
	rect.width = ofxeasing::map_clamp(now, initTime, endTime, birthRect.width, targetRect.width, &ofxeasing::back::easeOut_s, 0.8);
	rect.height = ofxeasing::map_clamp(now, initTime, endTime, birthRect.height, targetRect.height, &ofxeasing::back::easeOut_s, 0.8);

	if (isShowing)
	{
		alpha = ofxeasing::map_clamp(now, initTime, endTime, 0.0f, 180.0f, &ofxeasing::back::easeOut_s, 0.8);
	}
	else
	{
		alpha = ofxeasing::map_clamp(now, initTime, endTime, 180.0f, 0.0f, &ofxeasing::back::easeOut_s, 0.8);
	}
}

void largeStars::draw()
{
	if (_pTex)
	{
		ofPushStyle();
		ofEnableAlphaBlending();
		ofSetColor(0, 0, 0, alpha);
		ofFill();
		ofDrawRectangle(0, 0, SCREEN_W, SCREEN_H);
		//ofDrawCircle(50, 50, 500);
		ofPopStyle();
		ofPushMatrix();
		ofTranslate(rect.getCenter());
		_pTex->draw(0,0,rect.getWidth(),rect.getHeight());
		ofPopMatrix();
	}
}

void largeStars::mousePressed(int x, int y, int button)
{
	if (isShowing && ofGetElapsedTimef() - initTime > 1.0f)
	{
		doHiding();
	}
}

bool largeStars::isMasking()
{
	return alpha > 0.0f;
}

void largeStars::doShowing(ofImage * _tex, ofRectangle _birthRect)
{
	initTime = ofGetElapsedTimef();

	_pTex = _tex;
	birthRect = _birthRect;
	
	float w = SCREEN_W;
	float h = SCREEN_W * (_pTex->getHeight() / _pTex->getWidth());

	targetRect.setFromCenter(SCREEN_W / 2, SCREEN_H / 2, w, h);

	isShowing = true;
	//cout << targetRect << endl;
}

void largeStars::doHiding()
{
	if (!_pTex)return;

	initTime = ofGetElapsedTimef();

	float w = SCREEN_W;
	float h = SCREEN_W * (_pTex->getHeight() / _pTex->getWidth());

	targetRect.setFromCenter(-SCREEN_W / 2, SCREEN_H / 2, w, h);

	birthRect = rect;

	isShowing = false;
}
