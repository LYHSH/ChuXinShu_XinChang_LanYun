#include "itemMgr.h"

itemMgr::itemMgr()
{
	
}


itemMgr::~itemMgr()
{
}

void itemMgr::setup()
{
	loadData();
	star.setup();

	{
		minBirthx = 0 + boundSpace + imgWidth/2.0f;
		maxBirthx = SCREEN_W - boundSpace - imgWidth / 2.0f;
		middleX = SCREEN_W * 0.5f;
		lastRandomX = ofRandom(minBirthx, maxBirthx);
	}
	reset();
}

void itemMgr::update()
{
	if (true)
	{
		auto item = createItem();
		if (NULL != item)
		{
			items.push_back(item);
		}
	}
	auto ite = items.begin();
	while (items.end() != ite)
	{
		if ((*ite)->isOut())			//去除出局的对象
		{
			auto obj = *ite;
			ite = items.erase(ite);

			delete obj;
			obj = NULL;
		}
		else
		{
			(*ite)->update();
			ite++;
		}
	}
	star.update();
}

void itemMgr::draw()
{
	for (auto ite = items.begin(); ite != items.end(); ite++)
	{
		(*ite)->draw();
	}
	star.draw();

	ofPushStyle();
	ofSetColor(255, 0, 0);
	stringstream sss;
	sss << "item nums:" << items.size() << endl;
	sss << "fps:" << ofGetFrameRate() << endl;
	ofDrawBitmapString(sss.str(),20,20);
	ofPopStyle();
}

showItem * itemMgr::createItem()
{
	if (!(nextIndex >= 0 && nextIndex < itemDatas.size()))
	{
		//ofLogError() << "index out of range" << endl;
		return NULL;
	}
	
	auto & itemData = itemDatas[nextIndex];

	float x;
	if (lastRandomX > middleX)
	{
		x = ofRandom(minBirthx,middleX - 0.0f);		//左侧生成
	}
	else
	{
		x = ofRandom(middleX + 0.0f, maxBirthx);			//右侧生成
	}
	
	float y = -(itemData.tex->getHeight() * 0.5f);

	randomBirthRect.setFromCenter(x, y, itemData.tex->getWidth(), itemData.tex->getHeight());
	ofRectangle hotRect;				//识别判断是否遮挡区域
	hotRect.setFromCenter(x, y, itemData.tex->getWidth() * 1.2f, itemData.tex->getHeight() * 1.2f);

	bool flag = true;
	if (!items.empty() && (items.back())->getRect().getTop() < hotRect.getBottom())		//Y轴不碰到
	{
		flag = false;
	}

	if (flag)
	{
		lastRandomX = x;
		showItem * p = new showItem();
		p->setup(itemData.tex, randomBirthRect,itemData.texts);
		p->setBackTex(&itemBacktex);
		nextIndex = (++nextIndex) % itemDatas.size();
		return p;
	}
	
	return NULL;
}

//--------------------------------------------------------------
void itemMgr::mouseMoved(int x, int y) {
// 	if (!star.isMasking())
// 	{
// 		for (auto ite = items.begin(); ite != items.end(); ite++)
// 		{
// 			(*ite)->mouseMoved(x, y);
// 		}
// 	}
}

//--------------------------------------------------------------
void itemMgr::mouseDragged(int x, int y, int button) {
// 	if (!star.isMasking())
// 	{
// 		for (auto ite = items.begin(); ite != items.end(); ite++)
// 		{
// 			(*ite)->mouseDragged(x, y, button);
// 		}
// 	}
}

//--------------------------------------------------------------
void itemMgr::mousePressed(int x, int y, int button) {
	if (!star.isMasking())
	{
		for (auto ite = items.begin(); ite != items.end(); ite++)
		{
			if ((*ite)->isTouch(x, y))
			{
				//star.doShowing((*ite)->getTex(), (*ite)->getRect());
				star.doShowing((*ite)->getTex(), (*ite)->getRect(),&itemBacktex,(*ite)->getTexts());
			}
		}
	}


	if (!star.isMasking())
	{
		for (auto ite = items.begin(); ite != items.end(); ite++)
		{
			(*ite)->mousePressed(x, y, button);
		}
	}
	

	star.mousePressed(x, y, button);
}

//--------------------------------------------------------------
void itemMgr::mouseReleased(int x, int y, int button) {
// 	if (!star.isMasking())
// 	{
// 		for (auto ite = items.begin(); ite != items.end(); ite++)
// 		{
// 			(*ite)->mouseReleased(x,y,button);
// 		}
// 	}
}

void itemMgr::reset()
{
	//清除掉所有元素
	auto ite = items.begin();
	while (items.end() != ite)
	{
		auto obj = *ite;
		ite = items.erase(ite);

		delete obj;
		obj = NULL;
	}

	nextIndex = 0;
}

void itemMgr::loadData()
{
	ofxXmlSettings xml;
	xml.load("photos/photo.xml");

	int nums = xml.getNumTags("photo");
	itemDatas.resize(nums);
	for (int i = 0;i < nums;i++)
	{
		xml.pushTag("photo", i);
		itemDatas[i].tex = new ofImage();

		auto * p = itemDatas[i].tex;
		string imgName = xml.getValue("img", "photos/default.jpg");
		p->load(imgName);

		if (p->getWidth() != imgWidth)			//修正不规则图片并保存
		{
			p->resize(imgWidth, imgWidth / (p->getWidth() / p->getHeight()));
			p->save(imgName);
			//ofLogNotice() << imgName << " resize to: " << p->getWidth << "x" << p->getHeight() << endl;
		}

		int textNums = xml.getNumTags("text");
		for (int j = 0; j < textNums;j++)
		{
			itemDatas[i].texts.push_back(xml.getValue("text", "数据未读取",j));
		}
		xml.popTag();
	}

	itemBacktex.load("photos/back.png");
}