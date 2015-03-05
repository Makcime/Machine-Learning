#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include <vector>
#include "vertex.h"


#define MAP_SIZE 64
#define SQRT_SIZE 8
// #define MAP_SIZE 22
#define MAX_CONNECTIONS 10

class ofApp : public ofBaseApp{

	private:
		vertex connections[MAX_CONNECTIONS];
		vector < vertex * > map;
		vector < int > path;

		ofxPanel gui;

		ofxToggle filled;

		ofTrueTypeFont myfont;

	public:
		void setup();
		void update();
		void draw();

		void dfs(vertex * start, vertex * goal);
		void dfs2(vertex * start, vertex * goal);
		void nds(vertex * start, vertex * goal);
		void print_matrix();
		void print_matrix_as_csv();

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
