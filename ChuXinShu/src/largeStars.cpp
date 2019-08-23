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

	textBackTex = new ofImage();
	textBackTex->load("photos/textBack.png");
	textBackTex->setAnchorPercent(0.5f, 0.5f);

	font.load("fonts/btn.TTF",24);

	closeTex.load("photos/close.png");
	closeTex.setAnchorPercent(0.5f, 0.0f);
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
		backTex->draw(0, 0, rect.getWidth(), rect.getHeight());
		//_pTex->draw(0,0,rect.getWidth() * (1.0f - boardSpaceDensity),rect.getHeight() * ((1.0f - boardSpaceDensity)));
		_pTex->draw(0, 0, rect.getWidth() * (1.0f - boardSpaceDensity), rect.getHeight() - rect.getWidth() * boardSpaceDensity);
		ofPopMatrix();

		ofPushMatrix();
		ofTranslate(textRect.getCenter());
		textBackTex->draw(0,0,textRect.getWidth(),textRect.getHeight());
		closeTex.draw(0,textRect.getHeight() * 0.5f + 10);
		ofPopMatrix();

		ofPushMatrix();
		ofTranslate(textRect1.getLeft(),textRect1.getTop());
		{
			//int textNums = texts.size() > 2 ? 2 : texts.size();
			int textNums = texts.size();
			for (int i = 0; i<  textNums;i++)
			{
				ofRectangle fontRect = font.getStringBoundingBox(texts[i], 0, 0);
				float x = (textRect1.getWidth() - fontRect.getWidth()) * 0.5f;
				float y = (textRect1.getHeight() - fontRect.getHeight()) * 0.5f;

				float offsetY = 0.0f;
				static float const space = 10.0f;
				float  gap = fontRect.getHeight() + space;
				if (textNums %2 == 0)
				{
					int middle = textNums / 2;
					offsetY = (i - middle) * gap + gap * 0.5f;
				}
				else
				{
					int middle = textNums / 2;
					offsetY = (i - middle) * gap;
				}
				ofPushStyle();
				ofSetColor(255, 255, 255);
				font.drawString(texts[i], x, y - fontRect.getY() + offsetY);
				ofPopStyle();
			}
			
		}
		ofPopMatrix();

// 		ofPushStyle();
// 		ofNoFill();
// 		ofSetColor(255, 0, 0);
// 		ofDrawRectangle(rect);
// 		ofDrawRectangle(textRect);
// 		ofDrawRectangle(textRect1);
// 		ofPopStyle();
	}
}

void largeStars::mousePressed(int x, int y, int button)
{
	if (isMaskFulling() && !rect.inside(x,y) && !textRect.inside(x,y))
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

	//targetRect.setFromCenter(SCREEN_W / 2, SCREEN_H / 2, w , h);
	targetRect.setFromCenter(SCREEN_W / 2, 1442, w, h);

	Tweenzor::add(&rect, rect, targetRect, 0.0f, duration, EASE_IN_OUT_BACK,0.8);
	Tweenzor::add(&alpha, alpha, fullMaskAlpha, 0.0f, duration + 0.1f, EASE_OUT_QUAD);

	{
		ofRectangle beginRect;
		ofRectangle endRect;

		beginRect.setFromCenter(SCREEN_W + SCREEN_W * 0.5, 146 * 0.5f + targetRect.getBottom() + 20.0f, 1039, 146);
		endRect.setFromCenter(SCREEN_W * 0.5, 146 * 0.5f + targetRect.getBottom() + 20.0f, 1039, 146);
		Tweenzor::add(&textRect, beginRect, endRect, 0.0f, duration, EASE_IN_OUT_BACK, 0.8);
		Tweenzor::add(&textRect1, beginRect, endRect, 0.1f, duration, EASE_IN_OUT_BACK, 0.8);
	}
	
	//Tweenzor::addCompleteListener(Tweenzor::getTween(&rect), this, &largeStars::onComplete);
}

void largeStars::doShowing(ofImage * _tex, ofRectangle _birthRect, ofImage * _backTex, vector<string> _texts)
{
	backTex = _backTex;
	texts = _texts;
	doShowing(_tex, _birthRect);
}

void largeStars::doHiding()
{
	if (!_pTex)return;

	float w = SCREEN_W;
	float h = SCREEN_W * (_pTex->getHeight() / _pTex->getWidth());

	//targetRect.setFromCenter(-SCREEN_W / 2, SCREEN_H / 2, w, h);
	targetRect.setFromCenter(-SCREEN_W / 2, 1442, w, h);

	birthRect = rect;

	Tweenzor::add(&rect, rect, targetRect, 0.0f, duration, EASE_IN_OUT_BACK,0.8);
	Tweenzor::add(&alpha, alpha, 0.0f, 0.0f, duration, EASE_OUT_QUAD);

	{
		ofRectangle endRect;

		endRect.setFromCenter(-SCREEN_W * 0.5, textRect.getCenter().y, 1039, 146);
		Tweenzor::add(&textRect, textRect, endRect, 0.1f, duration, EASE_IN_OUT_BACK, 0.8);
		Tweenzor::add(&textRect1, textRect1, endRect, 0.2f, duration, EASE_IN_OUT_BACK, 0.8);
	}
}

void largeStars::onComplete(float* arg)
{
	if (arg == &rect.position.x)
	{
		ofRectangle beginRect;
		ofRectangle endRect;

		beginRect.setFromCenter(SCREEN_W + SCREEN_W * 0.5, 146 * 0.5f + targetRect.getBottom() + 20.0f,1039,146);
		endRect.setFromCenter(SCREEN_W * 0.5, 146 * 0.5f + targetRect.getBottom() + 20.0f, 1039, 146);
		Tweenzor::add(&textRect, beginRect, endRect, 0.0f, duration, EASE_IN_OUT_BACK, 0.8);
		Tweenzor::add(&textRect1, beginRect, endRect, 0.1f, duration, EASE_IN_OUT_BACK, 0.8);
	}
}
