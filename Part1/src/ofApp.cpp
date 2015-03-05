#include "ofApp.h"
#define	FILEPATH "../data/matrix.csv"

//--------------------------------------------------------------
void ofApp::setup(){
	// creation de tout les noeuds sur la carte
	ofToggleFullscreen();
	gui.setup();
	gui.add(filled.setup("fill", true));

	myfont.loadFont("arial.ttf", 11);

	for (int i = 0; i < MAP_SIZE; ++i)
		map.push_back(new vertex(i));

	ofFile csv = ofFile(FILEPATH);
	cout << csv.getEnclosingDirectory() << endl;
	ofBuffer csvBuffer = csv.readToBuffer();  
	string currentLine;

	int k = 0; 
	vector<string> splitItems;
	currentLine = csvBuffer.getNextLine();
	while (!csvBuffer.isLastLine()) {  
		currentLine = csvBuffer.getNextLine();
		splitItems = ofSplitString(currentLine, ",");
		for (int i = 0; i < MAP_SIZE; ++i){
			int weight = atoi(splitItems[i+1].c_str());
			if(weight > 0)
				map[k]->add_connection(map[i], weight);
		}
		k++;
	}   

	vertex * start = map[4];
	vertex * next;
	
		next = start->nextCon();
		printf("%d - ", next->getId() );
		printf("%d - ", &start);
		getchar();

	vertex * goal = map[15];

	// dfs2(start, goal);
	nds(start, goal);
	// dfs(start, goal);
	// print_matrix();
	// print_matrix_as_csv();

}

//--------------------------------------------------------------

void ofApp::dfs(vertex * start, vertex * goal){
	stack <vertex * > path;
	path.push(start);
	// start->setCheck(true);
	vertex* next = start;

	bool * marked;
	marked = new bool[map.size()];

	for (int i = 0; i < map.size(); ++i)
	{
		marked[i] = false;
	}

	vertex * edgeTo;
	edgeTo = new vertex [map.size()];
	
	marked[next->getId()] = true;
	next->setCheck(true);
	
	while(!path.empty() && next != goal){
		next = path.top()->nextCon();
		// cout << next->getId();
		// getchar();
		if(next){
			int p = path.top()->getId();
			int n = next->getId();
			if (!marked[n]){			
				path.push(next);
				edgeTo[p] = n;
				marked[n] = true;
				next->setCheck(true);
			}
		}else{
			path.pop();
		}
	}

	int size = path.size();
	int * result;
	result = new int[size];

	for (int i = size-1; i >=0 ; --i)
	{
		// cout << path.top()->getId() << endl;
		result[i] = path.top()->getId();
		path.pop();
	}

	for (int i = 0; i < size; ++i)
	{
		printf("%d - ", result[i] );
	}
	printf("\n");

}

//--------------------------------------------------------------

void ofApp::dfs2(vertex * start, vertex * goal){
	stack < vector<vertex*> > dfs_stack;
	bool goal_reached = false;

	vector <vertex *> path, new_path;
	path.push_back(start);
	start->setCheck(true);
	dfs_stack.push(path);


	while(!dfs_stack.empty() && !goal_reached){
		path = dfs_stack.top(); // remove the first path from the QUEUE (FILE);
		dfs_stack.pop();

		printf("\npath : [");
		for (int j = 0; j < path.size(); ++j)
			printf("%d,", path[j]->getId() );
			printf("]");getchar();
			// printf("]\n");
		
		vertex * plop ;
		plop = path.back();

		vertex * next = NULL;
		next = plop->nextCon_reverse();
		
		while(next!=NULL && !goal_reached){
		/* create new paths (to all children); */
			new_path =  path;
			next = plop->nextCon_reverse();
			if(next != NULL){

				next->setCheck(true);
				new_path.push_back(next);
		/*add the new paths to front of QUEUE (FILE);*/
				dfs_stack.push(new_path);
				printf("\tNEW path : [");
				for (int j = 0; j < new_path.size(); ++j)
					printf("%d,", new_path[j]->getId() );
				printf("]");getchar();
				// printf("]\n");
				
				if(next->getId() == goal->getId()){
					goal_reached = true;
					printf("\ngoal_reached !!!!!\n");
				}
			}
		}
	}

	if(goal_reached == true){
		path = dfs_stack.top(); // remove the first path from the QUEUE (FILE);
		for (vector<vertex *>::iterator i = path.begin(); i != path.end(); ++i){
			vertex * plop;		
			plop = *i;
			printf("%d - ", plop->getId() );
		}
		printf("\n");
	}
}

//--------------------------------------------------------------

void ofApp::nds(vertex * start, vertex * goal){
	vector < vector<vertex*> > rdm_stack;
	bool goal_reached = false;

	vector <vertex *> path, new_path;
	path.push_back(start);
	start->setCheck(true);
	rdm_stack.push_back(path);


	while(!rdm_stack.empty() && !goal_reached){
		path = rdm_stack.back(); // remove the first path from the QUEUE (FILE);
		rdm_stack.pop_back();

		printf("\npath : [");
		for (int j = 0; j < path.size(); ++j)
			printf("%d,", path[j]->getId() );
			printf("]");getchar();
			// printf("]\n");
		
		vertex * plop ;
		plop = path.back();

		vertex * next = NULL;
		next = plop->nextCon_reverse();
		
		while(next!=NULL && !goal_reached){
		/* create new paths (to all children); */
			new_path =  path;
			next = plop->nextCon_reverse();
			if(next != NULL){

				next->setCheck(true);
				new_path.push_back(next);
		/*add the new paths to front of QUEUE (FILE);*/
				int rdm = ofRandom(0, rdm_stack.size());
				rdm_stack.insert(rdm_stack.begin() + rdm, new_path);
				// rdm_stack.emplace(rdm_stack.begin() + rdm, new_path);
				
				printf("\tNEW path : [");
				for (int j = 0; j < new_path.size(); ++j)
					printf("%d,", new_path[j]->getId() );
				printf("]");getchar();
				// printf("]\n");
				
				if(next->getId() == goal->getId()){
					goal_reached = true;
					printf("\ngoal_reached !!!!!\n");
				}
			}
		}
	}

	if(goal_reached == true){
		path = rdm_stack.back(); // remove the first path from the QUEUE (FILE);
		for (vector<vertex *>::iterator i = path.begin(); i != path.end(); ++i){
			vertex * plop;		
			plop = *i;
			printf("%d - ", plop->getId() );
		}
		printf("\n");
	}
}

//--------------------------------------------------------------
void ofApp::print_matrix(){
	printf("   |");
	for (int i = 0; i < MAP_SIZE; ++i)
	{
		printf("%2d |", i);
	}
	printf("\n");

	printf("___|");
	for (int i = 0; i < MAP_SIZE; ++i)
	{
		printf("___|");
	}
	printf("\n");

	for (int i = 0; i < MAP_SIZE; ++i)
	{
		printf("%2d |", i);
		for (int j = 0; j < MAP_SIZE; ++j)
		{
			int w = map[i]->is_connected(map[j]);
			if(w)
				printf("%2d |", w);
			else if(i == j)
				printf(" x |");
			else
				printf("   |");
		}
		printf("\n");
	}


}

void ofApp::print_matrix_as_csv(){
	printf(";");
	for (int i = 0; i < MAP_SIZE; ++i)
	{
		printf("%d;", i);
	}
	printf("\n");

	for (int i = 0; i < MAP_SIZE; ++i)
	{
		printf("%d;", i);
		for (int j = 0; j < MAP_SIZE; ++j)
		{
			int w = map[i]->is_connected(map[j]);
			if(w)
				printf("%d;", w);
			else if(i == j)
				printf("x;");
			else
				printf(";");
		}
		printf("\n");
	}


}


//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
		// gui.draw();

	int pitch = ofGetHeight()/ (SQRT_SIZE+1)	;

	int delatax = pitch ;
	int delatay = (ofGetWidth() - ofGetHeight()) /2 + pitch;



	for (int i = 0; i < MAP_SIZE; ++i)
	{
		stringstream ss;
		int id = map[i]->getId();

		int x = (id%SQRT_SIZE) * pitch + delatay;
		int y = (id/SQRT_SIZE) * pitch + delatax;

		ofFill();
    	ofSetColor(ofColor::black);
	    // ofSetColor(ofColor(ofRandom(0, 255), ofRandom(0, 255),
     //                ofRandom(0, 255)));

    	ofCircle(x, y, 5);

    	ss << id;
	    myfont.drawString(ss.str(), x,y);
	    // ss.str("");
	    // ss.clear();

	}



}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key)
    {
    case 'f':
        ofToggleFullscreen();
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
