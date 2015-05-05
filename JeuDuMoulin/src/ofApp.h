
#ifndef OF_APP		
#define OF_APP

#pragma once

#include "ofMain.h"
#include "gameOfMill.h"

#define KEY_LEFT 356
#define KEY_UP 357
#define KEY_RIGHT 358
#define KEY_DOWN 359
#define KEY_ENTER 13

class ofApp : public ofBaseApp{

	private:

		GameOfMill* game;

	public:
		void setup();
		void update();
		void draw();
    	void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

};

#endif
