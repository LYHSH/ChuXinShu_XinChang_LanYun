#include "largeStars.h"



largeStars::largeStars()
{
}


largeStars::~largeStars()
{
}

void largeStars::setup()
{
	targetRect.set(0,0,SCREEN_W, SCREEN_H);
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
}

void largeStars::draw()
{
	if (_pTex)
	{
		_pTex->draw(rect);
	}
}

void largeStars::doShowing(ofImage * _tex, ofRectangle _birthRect)
{
	initTime = ofGetElapsedTimef();

	_pTex = _tex;
	birthRect = _birthRect;
	
	float w = SCREEN_W;
	float h = SCREEN_W * (_pTex->getHeight() / _pTex->getWidth());

	targetRect.setFromCenter(SCREEN_W / 2, SCREEN_H / 2, w, h);


	//cout << targetRect << endl;
}

void largeStars::doHiding()
{
	initTime = ofGetElapsedTimef();

	float w = SCREEN_W;
	float h = SCREEN_W * (_pTex->getHeight() / _pTex->getWidth());

	targetRect.setFromCenter(-SCREEN_W / 2, SCREEN_H / 2, w, h);

	birthRect = rect;
}
