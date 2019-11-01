#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	Tweenzor::init();
	ofLogToConsole();
	//ofLogToFile("log.log", true);

	{
		ofxXmlSettings xml;
		xml.load("config.xml");
		isVideoShowing = xml.getValue("isVideoShowing", 0);
		if (isVideoShowing)
		{
			ofDirectory dir;
			dir.allowExt("mov");
			dir.allowExt("mp4");
			dir.allowExt("avi");
			dir.listDir("itemVideo/");

			if (dir.size())
			{
				itemVideo.load(dir.getPath(0));
				itemVideo.setLoopState(OF_LOOP_NONE);
				itemVideo.stop();
			}
		}
	}

	myItemMgr.setup();

	{
		centerListener.Create();
		centerListener.SetNonBlocking(true);
		centerListener.Bind(PORT_CENTER_CONTROL);
	}
	
// 	ofSoundStreamSettings settings;
// 	settings.setInListener(this);
// 	settings.setOutListener(this);
// 	settings.numOutputChannels = 2;
// 	settings.numInputChannels = 0;
// 	settings.sampleRate = 44100;
// 	settings.bufferSize = 512;
// 	settings.numBuffers = 4;

	soundStream.setup(this, 2, 0, 44100, 512, 4);

	{
		//Connect to Port
		myTuio.connect(3333);

		//Assign Global TUIO Callback Functions
		ofAddListener(ofEvents().touchDown, this, &ofApp::touchDown);
		ofAddListener(ofEvents().touchUp, this, &ofApp::touchUp);
		ofAddListener(ofEvents().touchMoved, this, &ofApp::touchMoved);
	}


	{
		fboimg.load("fboImg.jpg");

		tipImg.load("tip.png");
	}

	if (backVideo.isServering())
	{
		ofxXmlSettings xml;
		xml.load("window.xml");
		bool noWindow = xml.getValue("no_window", 1);
		noWindow ? ofNoWindow() : "";
	}
	else
	{
		ofScreenCrossTopmost(SCREEN_W * SCREEN_SCALE, SCREEN_H * SCREEN_SCALE);
	}
	
	FreeConsole();
	ofSetFrameRate(60);


	goToLoop();
}

//--------------------------------------------------------------
void ofApp::update(){
	Tweenzor::update(ofGetElapsedTimeMillis());
	{
		char data[100];
		centerListener.Receive(data, 100);
		string msg = data;
		if ("" != msg)
		{
			if (msg == CMD_GOTO_LOOP)
			{
				if (STATE_LOOP != gameState)
				{
					goToLoop();
				}
			}
			else if (msg == CMD_GOTO_SWITCH)
			{
				if (STATE_SWITCH != gameState)
				{
					goToSwitch();
				}
			}
		}
	}

	myTuio.update();

 	switch (gameState)
 	{
 	case ofApp::STATE_LOOP:
 	{
 		backVideo.update();
 	}
 		break;
 	case ofApp::STATE_SWITCH:
	{
		backVideo.update();
		if (backVideo.isPlaying() && backVideo.getPosition() > 0.99f)
		{
			goToShowing();
		}
	}
 		break;
 	case ofApp::STATE_SHOWING:
	{
		backVideo.update();
		if (isVideoShowing)
		{
			itemVideo.update();
		}
		else
		{
			myItemMgr.update();
		}
		
	}
 		break;
 	default:
 		break;
 	}
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0);
	ofScale(SCREEN_SCALE, SCREEN_SCALE);
	switch (gameState)
	{
	case ofApp::STATE_LOOP:
	{
		backVideo.draw(0, 0, SCREEN_W, SCREEN_H);
	}
		break;
	case ofApp::STATE_SWITCH:
	{
		backVideo.draw(0, 0, SCREEN_W, SCREEN_H);
	}
		break;
	case ofApp::STATE_SHOWING:
	{
		fboimg.draw(0,0,SCREEN_W,SCREEN_H);
		if (isVideoShowing)
		{
			ofPushStyle();
			ofEnableAlphaBlending();
			ofSetColor(255, 255, 255, backVideoAlpha);
			backVideo.draw(0, 0, SCREEN_W, SCREEN_H);
			if (!itemVideo.getIsMovieDone())
			{
				itemVideo.draw(0, 0, SCREEN_W, SCREEN_H);
			}
			else
			{
				tipImg.draw(0, 0, SCREEN_W, SCREEN_H);
			}
			
			ofPopStyle();
		}
		else
		{
			
			ofPushStyle();
			ofEnableAlphaBlending();
			ofSetColor(255, 255, 255, backVideoAlpha);
			backVideo.draw(0, 0, SCREEN_W, SCREEN_H);
			myItemMgr.draw();
			ofPopStyle();
		}
	}
		break;
	default:
		break;
	}

	if (isDebug)
	{
		ofPushStyle();
		stringstream sss;
		switch (gameState)
		{
		case ofApp::STATE_LOOP:
			sss << "state:" << "STATE_LOOP" << endl;
			break;
		case ofApp::STATE_SWITCH:
			sss << "state:" << "STATE_SWITCH" << endl;
			break;
		case ofApp::STATE_SHOWING:
			sss << "state:" << "STATE_SHOWING" << endl;
			break;
		default:
			break;
		}

		sss << "video showing:" << isVideoShowing << endl;
		sss << "itemMgr:" << myItemMgr.debugMessage() << endl;
		sss << "backVideo pos:" << backVideo.getPosition() << endl;

		ofSetColor(255, 0, 0);
		ofDrawBitmapString(sss.str(),50,SCREEN_H/2);
		ofPopStyle();
	}
	
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
	case 'd':
		isDebug = !isDebug;
		break;
	default:
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	x /= SCREEN_SCALE;
	y /= SCREEN_SCALE;

	switch (gameState)
	{
	case ofApp::STATE_LOOP:
		break;
	case ofApp::STATE_SWITCH:
		break;
	case ofApp::STATE_SHOWING:
	{
		myItemMgr.mouseMoved(x, y);
	}
		break;
	default:
		break;
	}
	
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	x /= SCREEN_SCALE;
	y /= SCREEN_SCALE;
	switch (gameState)
	{
	case ofApp::STATE_LOOP:
		break;
	case ofApp::STATE_SWITCH:
		break;
	case ofApp::STATE_SHOWING:
	{
		myItemMgr.mouseDragged(x, y, button);
	}
		break;
	default:
		break;
	}
	
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	x /= SCREEN_SCALE;
	y /= SCREEN_SCALE;

	switch (gameState)
	{
	case ofApp::STATE_LOOP:
		break;
	case ofApp::STATE_SWITCH:
		break;
	case ofApp::STATE_SHOWING:
	{
		myItemMgr.mousePressed(x, y, button);
	}
		break;
	default:
		break;
	}
	
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	x /= SCREEN_SCALE;
	y /= SCREEN_SCALE;

	switch (gameState)
	{
	case ofApp::STATE_LOOP:
		break;
	case ofApp::STATE_SWITCH:
		break;
	case ofApp::STATE_SHOWING:
	{
		myItemMgr.mouseReleased(x, y, button);
	}
		break;
	default:
		break;
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
		Sleep(10);
		backVideo.play();
		backVideo.setLoopState(OF_LOOP_NORMAL);
		backVideo.setVolume(1.0f);
	}	


	if (isVideoShowing)
	{
		itemVideo.setFrame(0);
		itemVideo.setPaused(true);
	}

	myItemMgr.reset();
}

void ofApp::goToSwitch()
{
	gameState = STATE_SWITCH;

	ofDirectory dir;
	dir.allowExt("mov");
	dir.allowExt("mp4");
	dir.allowExt("avi");
	dir.listDir("videos/switch/");

	if (dir.size())
	{
		
		if (!backVideo.load(dir.getPath(0)))
		{
			ofSystemAlertDialog("111111");
		}
		Sleep(10);
		backVideo.play();
		backVideo.setLoopState(OF_LOOP_NONE);
		backVideo.setVolume(1.0f);
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
		if (!backVideo.load(dir.getPath(0)))
		{
			ofSystemAlertDialog("111111");
		}
		Sleep(10);
		backVideo.play();
		backVideo.setLoopState(OF_LOOP_NORMAL);
		backVideo.setVolume(0.5f);
	}

	if (isVideoShowing)
	{
		itemVideo.setPaused(false);
		itemVideo.play();
		backVideoAlpha = 0.0f;
		Tweenzor::add(&backVideoAlpha, backVideoAlpha, 255.0f, 0.0f, 1.0f, EASE_IN_OUT_QUAD);
	}
	else
	{
		myItemMgr.reset();
		myItemMgr.doTweenVec();

		backVideoAlpha = 0.0f;
		Tweenzor::add(&backVideoAlpha, backVideoAlpha, 255.0f, 2.5f, 4.0f, EASE_IN_OUT_QUAD);
	}
	
}

void ofApp::exit()
{
	ofRemoveListener(ofEvents().touchDown, this, &ofApp::touchDown);
	ofRemoveListener(ofEvents().touchUp, this, &ofApp::touchUp);
	ofRemoveListener(ofEvents().touchMoved, this, &ofApp::touchMoved);

	Tweenzor::destroy();
}

void ofApp::touchDown(ofTouchEventArgs & touch) {
	int x = touch.x * SCREEN_W;
	int y = touch.y * SCREEN_H;

	mousePressed(x, y, 0);
}

void ofApp::touchUp(ofTouchEventArgs & touch) { 
	int x = touch.x * SCREEN_W;
	int y = touch.y * SCREEN_H;

	//mouseReleased(x, y, 0);
}

void ofApp::touchMoved(ofTouchEventArgs & touch) {
	int x = touch.x * SCREEN_W;
	int y = touch.y * SCREEN_H;

	//mouseMoved(x, y);
	mousePressed(x, y,0);
	
}
