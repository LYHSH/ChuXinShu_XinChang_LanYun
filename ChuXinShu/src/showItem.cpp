#include "showItem.h"



showItem::showItem()
{
}


showItem::~showItem()
{
}

void showItem::setup(ofImage * _p,ofVec2f _pos)
{
	pTex = _p;
	pos = _pos;

	w = ofRandom(100, 300);
	h = ofRandom(100, 300);

	rect.setFromCenter(pos, w, h);

	size = 1.0f;
	touchSize = 1.0f;

	isTouching = false;

	initTime = 0.0f;
}

void showItem::update()
{
	auto duration = 0.1f;
	auto endTime = initTime + duration;
	auto now = ofGetElapsedTimef();
	if (isTouching)
	{
		size = ofxeasing::map_clamp(now, initTime, endTime, touchSize, 1.1f, &ofxeasing::linear::easeIn);
	}
	else
	{
		size = ofxeasing::map_clamp(now, initTime, endTime, touchSize, 1.0f, &ofxeasing::linear::easeIn);
	}
}

void showItem::draw()
{
	rect.setFromCenter(rect.getCenter(), w * size, h * size);

	pTex->draw(rect);
}

void showItem::mouseMoved(int x, int y)
{
	if (rect.inside(x,y))
	{
		if (!isTouching)
		{
			isTouching = true;
			initTime = ofGetElapsedTimef();
			touchSize = size;
		}
	}
	else
	{
		if (isTouching)
		{
			isTouching = false;
			initTime = ofGetElapsedTimef();
			touchSize = size;
		}
	}
}

void showItem::mouseDragged(int x, int y, int button)
{

}

void showItem::mousePressed(int x, int y, int button)
{

}

bool showItem::mouseReleased(int x, int y, int button)
{
	return rect.inside(x, y);
}

ofImage * showItem::getTex()
{
	return pTex;
}

ofRectangle showItem::getRect()
{
	return rect;
}