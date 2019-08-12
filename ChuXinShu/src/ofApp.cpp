#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
//	goToLoop();
	stars.setup();

	{
		ofDirectory dir;
		dir.allowExt("png");

		dir.listDir("photos/imgs/");
		imgs.resize(dir.size());
		for (int i = 0;i < dir.size();i++)
		{
			imgs[i].load(dir.getPath(i));
		}
	}

	{
		items.resize(20);
		for (int i = 0;i < items.size();i++)
		{
			items[i] = new showItem();
			items[i]->setup(&imgs[ofRandom(imgs.size())], ofVec2f(ofRandom(SCREEN_W), ofRandom(SCREEN_H)));
		}
	}

	{
		centerListener.Create();
		centerListener.SetNonBlocking(true);
		centerListener.Bind(PORT_CENTER_CONTROL);
	}

	soundStream.setup(this, 2, 0, 44100, 512, 4);

	{
		//Connect to Port
		myTuio.connect(3333);

		//Assign Global TUIO Callback Functions
		ofAddListener(ofEvents().touchDown, this, &ofApp::touchDown);
		ofAddListener(ofEvents().touchUp, this, &ofApp::touchUp);
		ofAddListener(ofEvents().touchMoved, this, &ofApp::touchMoved);
	}

	ofSetWindowShape(SCREEN_W * SCREEN_SCALE, SCREEN_H * SCREEN_SCALE);
	ofSetFrameRate(60);
}

//--------------------------------------------------------------
void ofApp::update(){
	{
		char data[100];
		centerListener.Receive(data, 100);
		string msg = data;
		if ("" != msg)
		{
			if (msg == CMD_GOTO_LOOP)
			{
				goToLoop();
			}
			else if (msg == CMD_GOTO_SWITCH)
			{
				goToSwitch();
			}
		}
	}

	myTuio.update();

// 	switch (gameState)
// 	{
// 	case ofApp::STATE_LOOP:
// 	{
// 		backVideo.update();
// 	}
// 		break;
// 	case ofApp::STATE_SWITCH:
// 		break;
// 	case ofApp::STATE_SHOWING:
// 		break;
// 	default:
// 		break;
// 	}

	stars.update();

	for (int i = 0; i < items.size(); i++)
	{
		items[i]->update();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0);
	ofScale(SCREEN_SCALE, SCREEN_SCALE);
// 	switch (gameState)
// 	{
// 	case ofApp::STATE_LOOP:
// 	{
// 		backVideo.draw(0, 0, SCREEN_W, SCREEN_H);
// 	}
// 		break;
// 	case ofApp::STATE_SWITCH:
// 		break;
// 	case ofApp::STATE_SHOWING:
// 		break;
// 	default:
// 		break;
// 	}
	for (int i = 0; i < items.size(); i++)
	{
		items[i]->draw();
	}
	stars.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key)
	{
	case '1':
		goToLoop();
		break;
	case '2':
		goToSwitch();
		break;
		goToShowing();  
	case '3':
		break;
	default:
		break;
	}

	if ('g' == key)
	{
		ofRectangle rect = ofRectangle(ofRandom(0,SCREEN_W),ofRandom(0,SCREEN_H), ofRandom(100, 300),ofRandom(100,300));
		stars.doShowing(&imgs[ofRandom(imgs.size())],rect);
	}
	else if ('q' == key)
	{
		stars.doHiding();
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	for (int i = 0; i < items.size(); i++)
	{
		items[i]->mouseMoved(x, y);
	}
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	for (int i = 0; i < items.size(); i++)
	{
		items[i]->mouseDragged(x, y,button);
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	for (int i = 0; i < items.size(); i++)
	{
		items[i]->mousePressed(x, y,button);
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	for (int i = 0; i < items.size(); i++)
	{
		if (items[i]->mouseReleased(x, y, button))
		{
			//ofRectangle rect = ofRectangle(ofRandom(0, SCREEN_W), ofRandom(0, SCREEN_H), ofRandom(100, 300), ofRandom(100, 300));
			stars.doShowing(items[i]->getTex(), items[i]->getRect());
		}
	}
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::audioOut(float * output, int bufferSize, int nChannels)
{
	backVideo.audioOut(output, bufferSize, nChannels);
}

void ofApp::goToLoop()
{
	gameState = STATE_LOOP;

	ofDirectory dir;
	dir.allowExt("mov");
	dir.allowExt("mp4");
	dir.allowExt("avi");
	dir.listDir("videos/loop/");

	if (dir.size())
	{
		backVideo.load(dir.getPath(0));
		backVideo.play();
		backVideo.setLoopState(OF_LOOP_NORMAL);
	}	
}

void ofApp::goToSwitch()
{
	gameState = STATE_LOOP;

	ofDirectory dir;
	dir.allowExt("mov");
	dir.allowExt("mp4");
	dir.allowExt("avi");
	dir.listDir("videos/switch/");

	if (dir.size())
	{
		backVideo.load(dir.getPath(0));
		backVideo.play();
		backVideo.setLoopState(OF_LOOP_NONE);
	}
}

void ofApp::goToShowing()
{
	gameState = STATE_SHOWING;

	ofDirectory dir;
	dir.allowExt("mov");
	dir.allowExt("mp4");
	dir.allowExt("avi");
	dir.listDir("videos/show/");

	if (dir.size())
	{
		backVideo.load(dir.getPath(0));
		backVideo.play();
		backVideo.setLoopState(OF_LOOP_NORMAL);
	}
}

void ofApp::exit()
{
	ofRemoveListener(ofEvents().touchDown, this, &ofApp::touchDown);
	ofRemoveListener(ofEvents().touchUp, this, &ofApp::touchUp);
	ofRemoveListener(ofEvents().touchMoved, this, &ofApp::touchMoved);
}

void ofApp::touchDown(ofTouchEventArgs & touch) {
	int x = touch.x * SCREEN_W;
	int y = touch.y * SCREEN_H;
}

void ofApp::touchUp(ofTouchEventArgs & touch) { 
	int x = touch.x * SCREEN_W;
	int y = touch.y * SCREEN_H;

	mouseReleased(x, y, 0);
}

void ofApp::touchMoved(ofTouchEventArgs & touch) {
	int x = touch.x * SCREEN_W;
	int y = touch.y * SCREEN_H;

	mouseMoved(x, y);
	
}
