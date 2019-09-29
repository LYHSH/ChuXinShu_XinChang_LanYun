#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofLogToConsole();
	goToLoop();
	//goToShowing();

	myItemMgr.setup();

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

	{
		fbo.allocate(SCREEN_W, SCREEN_H);
	}
	FreeConsole();
	//ofSetWindowShape(SCREEN_W * SCREEN_SCALE, SCREEN_H * SCREEN_SCALE);
	if (backVideo.isServering())
	{
		ofNoWindow();
		//ofScreenCrossTopmost(SCREEN_W * SCREEN_SCALE, SCREEN_H * SCREEN_SCALE);
	}
	else
	{
		ofScreenCrossTopmost(SCREEN_W * SCREEN_SCALE, SCREEN_H * SCREEN_SCALE);
	}
	
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

		//if (!backVideo.isPlaying() && backVideo.getPosition() > 0.9f)
		if (backVideo.getPosition() > 0.999f)
		{
			fbo.begin();
			ofClear(0);
			backVideo.draw(0, 0, SCREEN_W, SCREEN_H);
			fbo.end();
			initTime = ofGetElapsedTimef();
			goToShowing();
		}
	}
		
 		break;
 	case ofApp::STATE_SHOWING:
	{
		backVideo.update();
		myItemMgr.update();

		auto duration = 1.0f;
		auto endTime = initTime + duration;
		auto now = ofGetElapsedTimef();
		moveY = ofxeasing::map_clamp(now, initTime, endTime, 0.0f, SCREEN_H, &ofxeasing::linear::easeIn);
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
		//backVideo.draw(0, -SCREEN_H + moveY, SCREEN_W, SCREEN_H);
		backVideo.draw(0, 0, SCREEN_W, SCREEN_H);
		ofPushStyle();
		ofEnableAlphaBlending();
		float alpha = (1.0f - moveY / (float)SCREEN_H) * 255.0f;
		//cout << alpha << endl;
		ofSetColor(255, 255, 255, alpha);
		fbo.draw(0,0,SCREEN_W,SCREEN_H);
		//fbo.draw(0, moveY, SCREEN_W, SCREEN_H);
		ofPopStyle();
		myItemMgr.draw();
	}
		break;
	default:
		break;
	}

// 	ofPushStyle();
// 	ofSetColor(255, 0, 0);
// 	ofDrawBitmapString(ofToString(backVideo.getPosition()), 20, 20);
// 	ofPopStyle();
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
		backVideo.play();
		backVideo.setLoopState(OF_LOOP_NORMAL);
	}	
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

	myItemMgr.reset();
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
