#pragma once

#include "ofMain.h"
#include "frameSynAvServer.h"
#include "myContants.h"
#include "largeStars.h"
#include "showItem.h"
#include "ofxUDPManager.h"
#include "ofxTuioClient.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void exit();
		
		enum GameState
		{
			STATE_LOOP,
			STATE_SWITCH,
			STATE_SHOWING,
		}gameState;

		frameSynAvServer backVideo;
		ofSoundStream soundStream;
		void audioOut(float * output, int bufferSize, int nChannels);

		void goToLoop();
		void goToSwitch();
		void goToShowing();

		largeStars stars;

		vector<ofImage> imgs;

		vector<showItem *> items;

		ofxUDPManager centerListener;

		ofxTuioClient myTuio;

		void touchDown(ofTouchEventArgs & touch);
		void touchUp(ofTouchEventArgs & touch);
		void touchMoved(ofTouchEventArgs & touch);
};
