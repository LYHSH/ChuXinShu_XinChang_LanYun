#include "itemMgr.h"

itemMgr::itemMgr()
{
	
}


itemMgr::~itemMgr()
{
}

void itemMgr::setup()
{
	birthRects.resize(3);

	birthRects[0].setFromCenter(ofVec2f(180, -200), 340, 340);
	birthRects[1].setFromCenter(ofVec2f(540, -250), 340, 340);
	birthRects[2].setFromCenter(ofVec2f(900, -220), 340, 340);

	{
		ofDirectory dir;
		dir.allowExt("png");

		dir.listDir("photos/imgs/");
		imgs.resize(dir.size());
		for (int i = 0; i < dir.size(); i++)
		{
			imgs[i].load(dir.getPath(i));
		}
	}

	star.setup();
}

void itemMgr::update()
{
	//if ((int)ofRandom(10) == 1)
	if (1)
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
	for (int i = 0;i <birthRects.size();i++)
	{
		auto birthRect = birthRects[i];
		bool flag = true;

		auto ite = items.begin();
		while (items.end() != ite)
		{
			if ((*ite)->getRect().intersects(birthRect))		//矩形相交
			{
				flag = false;
				break;
			}
			ite++;
		}

		if (flag)
		{
			showItem * p = new showItem();
			p->setup(&imgs[ofRandom(imgs.size())], birthRect);
			return p;
		}
	}
	
	return NULL;
}

//--------------------------------------------------------------
void itemMgr::mouseMoved(int x, int y) {
	if (!star.isMasking())
	{
		for (auto ite = items.begin(); ite != items.end(); ite++)
		{
			(*ite)->mouseMoved(x, y);
		}
	}
}

//--------------------------------------------------------------
void itemMgr::mouseDragged(int x, int y, int button) {
	if (!star.isMasking())
	{
		for (auto ite = items.begin(); ite != items.end(); ite++)
		{
			(*ite)->mouseDragged(x, y, button);
		}
	}
}

//--------------------------------------------------------------
void itemMgr::mousePressed(int x, int y, int button) {
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
	if (!star.isMasking())
	{
		for (auto ite = items.begin(); ite != items.end(); ite++)
		{
			if ((*ite)->mouseReleased(x, y, button))
			{
				star.doShowing((*ite)->getTex(), (*ite)->getRect());
			}
		}
	}	
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
}