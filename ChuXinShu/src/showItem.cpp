#include "showItem.h"



showItem::showItem()
{
	w = ofRandom(100, 300);
	h = ofRandom(100, 300);
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
	touchSize = 1.0f;

	isTouching = false;

	initTime = 0.0f;
}

void showItem::setup(ofImage * _p, ofRectangle _rect)
{
	w = _rect.getWidth();
	h = _rect.getHeight();
	setup(_p, _rect.getCenter());
}

void showItem::update()
{
	{	//animtion
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
	
	pos += vec;
}

void showItem::draw()
{
	ofPushMatrix();
	ofTranslate(pos);
	pTex->draw(0,0,w * size,h * size);
	ofPopMatrix();
//	rect.setFromCenter(rect.getCenter(), w * size, h * size);

//	pTex->draw(rect);
}

void showItem::mouseMoved(int x, int y)
{
	if (getRect().inside(x,y))
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