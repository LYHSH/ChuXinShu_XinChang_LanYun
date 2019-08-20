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

void showItem::update()
{
	Tweenzor::update(ofGetElapsedTimeMillis());

	pos += vec;
}

void showItem::draw()
{
	ofPushMatrix();
	ofTranslate(pos);
	pTex->draw(0,0,w * size,h * size);
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
	if (getRect().inside(x, y))
	{
		Tweenzor::add(&size, size, 1.1f, 0.f, duration, EASE_LINEAR);
	}
	else
	{
		Tweenzor::add(&size, size, 1.0f, 0.f, duration, EASE_LINEAR);
	}
}

bool showItem::mouseReleased(int x, int y, int button)
{
	return getRect().inside(x, y);
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