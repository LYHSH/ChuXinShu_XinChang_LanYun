#include "largeStars.h"



largeStars::largeStars()
{
	_pTex = NULL;
	Tweenzor::init();
}


largeStars::~largeStars()
{
}

void largeStars::setup()
{
	targetRect.set(0,0,SCREEN_W, SCREEN_H);

	alpha = 0.0f;
}

void largeStars::update()
{
	Tweenzor::update(ofGetElapsedTimeMillis());
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
	if (isMaskFulling())
	{
		doHiding();
	}
}

bool largeStars::isMasking()
{
	return alpha > 0.0f;
}

bool largeStars::isMaskFulling()
{
	return alpha >= fullMaskAlpha;
}

void largeStars::doShowing(ofImage * _tex, ofRectangle _birthRect)
{
	_pTex = _tex;
	birthRect = _birthRect;

	rect = _birthRect;
	
	float w = SCREEN_W;
	float h = SCREEN_W * (_pTex->getHeight() / _pTex->getWidth());

	targetRect.setFromCenter(SCREEN_W / 2, SCREEN_H / 2, w, h);

	Tweenzor::add(&rect, rect, targetRect, 0.0f, duration, EASE_IN_OUT_BACK,0.8);
	Tweenzor::add(&alpha, alpha, fullMaskAlpha, 0.0f, duration, EASE_OUT_QUAD);
}

void largeStars::doHiding()
{
	if (!_pTex)return;

	float w = SCREEN_W;
	float h = SCREEN_W * (_pTex->getHeight() / _pTex->getWidth());

	targetRect.setFromCenter(-SCREEN_W / 2, SCREEN_H / 2, w, h);

	birthRect = rect;

	Tweenzor::add(&rect, rect, targetRect, 0.0f, duration, EASE_IN_OUT_BACK,0.8);
	Tweenzor::add(&alpha, alpha, 0.0f, 0.0f, duration, EASE_OUT_QUAD);
}
