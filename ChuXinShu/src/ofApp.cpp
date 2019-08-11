#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	goToLoop();


	soundStream.setup(this, 2, 0, 44100, 512, 4);

	ofSetWindowShape(SCREEN_W * SCREEN_SCALE, SCREEN_H * SCREEN_SCALE);
	ofSetFrameRate(60);
}

//--------------------------------------------------------------
void ofApp::update(){
	switch (gameState)
	{
	case ofApp::STATE_LOOP:
	{
		backVideo.update();
	}
		break;
	case ofApp::STATE_SWITCH:
		break;
	case ofApp::STATE_SHOWING:
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
		break;
	case ofApp::STATE_SHOWING:
		break;
	default:
		break;
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
	default:
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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