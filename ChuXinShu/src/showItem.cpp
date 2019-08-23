#include "showItem.h"



showItem::showItem()
{
	w = ofRandom(100, 300);
	h = ofRandom(100, 300);

	Tweenzor::init();
}


showItem::~showItem()
{
}

void showItem::setup(ofImage * _p,ofVec2f _pos)
{
	pTex = _p;
	pTex->setAnchorPercent(0.5f, 0.5f);
	pos = _pos;

	vec.set(0, 1.0f);

	rect.setFromCenter(pos, w, h);

	size = 1.0f;
}

void showItem::setup(ofImage * _p, ofRectangle _rect)
{
	w = _rect.getWidth();
	h = _rect.getHeight();
	setup(_p, _rect.getCenter());
}

void showItem::setup(ofImage * _p, ofRectangle _rect,vector<string> _texts)
{
	texts = _texts;
	setup(_p, _rect);
}

void showItem::setBackTex(ofImage * _tex)
{
	backTex = _tex;
	backTex->setAnchorPercent(0.5f, 0.5f);
}

void showItem::update()
{
	Tweenzor::update(ofGetElapsedTimeMillis());

	pos += vec;
}

void showItem::draw()
{
	ofPushMatrix();
	ofTranslate(pos);
	ofPushStyle();
	ofEnableAlphaBlending();
	//backTex->draw(0,0,w * size * (1.0f + boardSpaceDensity), h * size * (1.0f + boardSpaceDensity));
	backTex->draw(0, 0, w * size * (1.0f + boardSpaceDensity), h * size + w * size * boardSpaceDensity);
	pTex->draw(0,0,w * size,h * size);
	ofPopStyle();
	ofPopMatrix();
}

void showItem::mouseMoved(int x, int y)
{
	if (getRect().inside(x,y))
	{
		Tweenzor::add(&size, size, 1.1f, 0.f, duration, EASE_LINEAR);
	}
	else
	{
		Tweenzor::add(&size, size, 1.0f, 0.f, duration, EASE_LINEAR);
	}
}

void showItem::mouseDragged(int x, int y, int button)
{
	if (getRect().inside(x, y))
	{
		Tweenzor::add(&size, size, 1.1f, 0.f, duration, EASE_LINEAR);
	}
	else
	{
		Tweenzor::add(&size, size, 1.0f, 0.f, duration, EASE_LINEAR);
	}
}

void showItem::mousePressed(int x, int y, int button)
{
// 	if (getRect().inside(x, y))
// 	{
// 		Tweenzor::add(&size, size, 1.1f, 0.f, duration, EASE_LINEAR);
// 	}
// 	else
// 	{
// 		Tweenzor::add(&size, size, 1.0f, 0.f, duration, EASE_LINEAR);
// 	}
}

void showItem::mouseReleased(int x, int y, int button)
{
	
}

bool showItem::isTouch(int _x, int _y)
{
	return getRect().inside(_x, _y);
}

ofImage * showItem::getTex()
{
	return pTex;
}

ofRectangle showItem::getRect()
{
	ofRectangle rect;
	rect.setFromCenter(pos, w * size, h * size);
	return rect;
}

bool showItem::isOut()
{
	return getRect().getTop() > SCREEN_H + 100.0f;
}

vector<string> showItem::getTexts()
{
	return texts;
}