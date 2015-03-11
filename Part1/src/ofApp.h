
#ifndef OF_APP		
#define OF_APP

#pragma once

#include "ofMain.h"
#include "ofxUI.h"
#include "ofxGui.h"
#include "graph.h"
#include <vector>


// #define MAP_SIZE 49
// #define SQRT_SIZE 7
// #define MAP_SIZE 22
#define MAX_CONNECTIONS 10

class ofApp : public ofBaseApp{

	struct globalSettings
	{
		int start, goal;
		int algo;
	};

	private:

		globalSettings globSet;

		graph *myGraph;

		// vector < vertex * > map;
		// vector < int > path;

		ofxToggle filled;
		// ofTrueTypeFont myfont;
    	float *buffer; 

	public:
		void setup();
		void gui_setup();
		void update();
		void draw();
    	void exit();

		// void dfs(vertex * start, vertex * goal);
		// void dfs2(vertex * start, vertex * goal);
		// void nds(vertex * start, vertex * goal);
		// void print_matrix();
		// void print_matrix_as_csv();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofxUICanvas *gui;   	
		void guiEvent(ofxUIEventArgs &e);
    	bool drawPadding; 
		
};

#endif
