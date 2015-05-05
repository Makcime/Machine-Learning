#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofToggleFullscreen();
    ofSetFrameRate(20);
    game = new GameOfMill();
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    game->draw();
}


//--------------------------------------------------------------
void ofApp::exit()
{
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	static float plop = 0;
    switch (key)
    {
    case 'f':
        ofToggleFullscreen();
        break;
    case KEY_RIGHT:
        game->select();
        break;
    case KEY_LEFT:
        game->select();
        break;
    case KEY_DOWN:
        game->selectPlace();
        break;
    case KEY_UP:
        game->selectPlace();
        break;
    case KEY_ENTER:
        game->Go();
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
void ofApp::windowResized(int w, int h){
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
