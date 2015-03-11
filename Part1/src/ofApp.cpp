#include "ofApp.h"
#define	FILEPATH "../data/matrix.csv"

//--------------------------------------------------------------
void ofApp::setup(){
	ofToggleFullscreen();
	myGraph = new graph();
	gui_setup();
}

//--------------------------------------------------------------
void ofApp::gui_setup(){
	ofSetVerticalSync(true); 
	ofEnableSmoothing();
    drawPadding = false;
    gui = new ofxUICanvas();

    gui->addSpacer();
    
    vector<string> vnames; vnames.push_back("Depth-First Search"); 
    vnames.push_back("Non-Deterministic Search"); 
    vnames.push_back("Greedy Search");
    vnames.push_back("Estimate-Extended Uniform Cost");
    gui->addLabel("Algo ", OFX_UI_FONT_MEDIUM);
    ofxUIRadio *radio = gui->addRadio("VR", vnames, OFX_UI_ORIENTATION_VERTICAL);
    radio->activateToggle("DFS");

    gui->addSpacer();
    gui->addLabel("Start"); 
    gui->addTextInput("MEDIUM TEXTINPUT", myGraph->getStart(), OFX_UI_FONT_MEDIUM);

    gui->addSpacer();
    gui->addLabel("Goal"); 
    gui->addTextInput("MEDIUM TEXTINPUT", myGraph->getGoal(), OFX_UI_FONT_MEDIUM);
        
    gui->addSpacer();
    gui->addLabelToggle("RUN !", false);

    gui->addSpacer();

    buffer = new float[256];     
    for(int i = 0; i < 256; i++) { buffer[i] = ofNoise(i/100.0); }
    
	gui->addLabel("WAVEFORM GRAPH");     
	gui->addWaveform("WAVEFORM", buffer, 256, 0.0, 1.0);

    gui->addLabel("SPECTRUM GRAPH");        
    gui->addSpectrum("SPECTRUM", buffer, 256, 0.0, 1.0);

    gui->addSpacer();

    gui->autoSizeToFitWidgets();
    ofAddListener(gui->newGUIEvent,this,&ofApp::guiEvent);
    

}

//--------------------------------------------------------------
void ofApp::update(){
    // for(int i = 0; i < 256; i++) { buffer[i] = ofNoise(i/100.0, ofGetElapsedTimef()); }
}

//--------------------------------------------------------------
void ofApp::draw(){
	myGraph->draw();
}

//--------------------------------------------------------------
void ofApp::guiEvent(ofxUIEventArgs &e)
{
	string name = e.widget->getName(); 
	int kind = e.widget->getKind(); 
    
    if(kind == OFX_UI_WIDGET_BUTTON)
    {
        ofxUIButton *button = (ofxUIButton *) e.widget; 
        cout << name << "\t value: " << button->getValue() << endl;         
    }
    else if(kind == OFX_UI_WIDGET_TOGGLE)
    {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget; 
        cout << name << "\t value: " << toggle->getValue() << endl;             
    }
    else if(kind == OFX_UI_WIDGET_IMAGEBUTTON)
    {
        ofxUIImageButton *button = (ofxUIImageButton *) e.widget; 
        cout << name << "\t value: " << button->getValue() << endl;                 
    }
    else if(kind == OFX_UI_WIDGET_IMAGETOGGLE)
    {
        ofxUIImageToggle *toggle = (ofxUIImageToggle *) e.widget; 
        cout << name << "\t value: " << toggle->getValue() << endl;                 
    }
	else if(kind == OFX_UI_WIDGET_LABELBUTTON)
    {
        ofxUILabelButton *button = (ofxUILabelButton *) e.widget; 
        cout << name << "\t value: " << button->getValue() << endl;                 
    }
    else if(kind == OFX_UI_WIDGET_LABELTOGGLE)
    {
        ofxUILabelToggle *toggle = (ofxUILabelToggle *) e.widget; 
        cout << name << "\t value: " << toggle->getValue() << endl;                 
    }
	else if(name == "B1")
	{
        ofxUIButton *button = (ofxUIButton *) e.widget; 
        cout << "value: " << button->getValue() << endl; 
	}
    else if(name == "B2")
    {
        ofxUIButton *button = (ofxUIButton *) e.widget; 
        cout << "value: " << button->getValue() << endl;         
    }
    else if(name == "T1")
    {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget; 
        cout << "value: " << toggle->getValue() << endl;     
    }
    else if(name == "T2")
    {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget; 
        cout << "value: " << toggle->getValue() << endl;     
    }
}
//--------------------------------------------------------------
void ofApp::exit()
{
    delete gui; 
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	static float plop = 0;
    switch (key)
    {
    case 'f':
        ofToggleFullscreen();
        break;
    case 'g':
		gui->toggleVisible(); 
        break;
    case 'n':
		myGraph->next_hop(); 
    	for(int i = 0; i < 256; i++) { buffer[i] = ofNoise(i/100.0, plop+=0.0003); }
        break;
    case 'r':
		myGraph->resetGraph(); 
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
	myGraph->resetPositions(w, h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
