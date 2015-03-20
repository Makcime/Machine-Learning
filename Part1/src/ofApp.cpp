#include "ofApp.h"
#define	FILEPATH "../data/matrix.csv"

//--------------------------------------------------------------
void ofApp::setup(){
	ofToggleFullscreen();
	myGraph = new graph();
	gui_setup();

	globSet = { .start = 0, .goal = 48, .algo = DFS };

	myGraph->resetGraph(globSet.start, 
						globSet.goal, 
						globSet.algo);
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
    ofxUIRadio *radio = gui->addRadio("ALGO", vnames, OFX_UI_ORIENTATION_VERTICAL);
    radio->activateToggle("Depth-First Search");

    gui->addSpacer();
    gui->addLabel("Start"); 
    // gui->addTextInput("START INPUT", myGraph->getStart(), OFX_UI_FONT_MEDIUM);
    gui->addTextInput("START INPUT", "", OFX_UI_FONT_MEDIUM)->setAutoClear(false);

    gui->addSpacer();
    gui->addLabel("Goal"); 
    // gui->addTextInput("GOAL INPUT", myGraph->getGoal(), OFX_UI_FONT_MEDIUM);
    gui->addTextInput("GOAL INPUT", "", OFX_UI_FONT_MEDIUM)->setAutoClear(false);
        
    gui->addSpacer();
    gui->addLabelButton("RESET", false);

    gui->addSpacer();

    buffer = new float[256];     
    for(int i = 0; i < 256; i++) { buffer[i] = ofNoise(i/100.0); }
    
	// gui->addLabel("WAVEFORM GRAPH");     
	// gui->addWaveform("WAVEFORM", buffer, 256, 0.0, 1.0);

 //    gui->addLabel("SPECTRUM GRAPH");        
 //    gui->addSpectrum("SPECTRUM", buffer, 256, 0.0, 1.0);

    // gui->addSpacer();

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
    
	if(kind == OFX_UI_WIDGET_LABELBUTTON)
    {
        ofxUILabelButton *button = (ofxUILabelButton *) e.widget; 
        if(button->getValue() == 1)
		myGraph->resetGraph(globSet.start, 
							globSet.goal, 
							globSet.algo);
        // cout << name << "\t value: " << button->getValue() << endl;                 
    }
    else if(name == "START INPUT")
    {
        ofxUITextInput *ti = (ofxUITextInput *) e.widget;
        if(ti->getInputTriggerType() == OFX_UI_TEXTINPUT_ON_UNFOCUS
        	|| ti->getInputTriggerType() == OFX_UI_TEXTINPUT_ON_ENTER)
        {
	        string output = ti->getTextString();
	        globSet.start = atoi(output.c_str());
        }
    }
    else if(name == "GOAL INPUT")
    {
        ofxUITextInput *ti = (ofxUITextInput *) e.widget;
        if(ti->getInputTriggerType() == OFX_UI_TEXTINPUT_ON_UNFOCUS
        	|| ti->getInputTriggerType() == OFX_UI_TEXTINPUT_ON_ENTER)
        {
	        string output = ti->getTextString();
	        ti->setTextString(output);
	        globSet.goal = atoi(output.c_str());
        }
    }
    else if(name == "ALGO")
    {
        ofxUIRadio *radio = (ofxUIRadio *) e.widget;
        cout << radio->getName() << " value: " << radio->getValue() << " active name: " << radio->getActiveName() << endl;
        string n = radio->getActiveName();
        if(n == "Depth-First Search") 
        	globSet.algo = DFS;
		else if(n == "Non-Deterministic Search") 
			globSet.algo = NDS;
		else if(n == "Greedy Search")
			globSet.algo = GS;
		else if(n == "Estimate-Extended Uniform Cost")
			globSet.algo = EEUC;
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
		myGraph->resetGraph(globSet.start, 
							globSet.goal, 
							globSet.algo); 
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
