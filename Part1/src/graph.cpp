#include "graph.h"

//--------------------------------------------------------------

graph::graph(){
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

	print_map_as_matrix();

	start = map[0];
	goal = map[48];

	path.push_back(start);
	file.push_back(path);
	start->setCheck(true);
	goalReached = false;

	algoSelected = DFS;

}

//--------------------------------------------------------------

graph::~graph(){

}

//--------------------------------------------------------------

void graph::draw(){
	int pitch = ofGetHeight()/ (SQRT_SIZE+1);
	int delatax = pitch ;
	int delatay = (ofGetWidth() - ofGetHeight()) /2 + pitch;

	for(int i = 0; i < MAP_SIZE; ++i)
	{
		int id = map[i]->getId();
		if (map[i]->getConCnt()){
			stringstream ss;

			int x = (id%SQRT_SIZE) * pitch + delatay;
			int y = (id/SQRT_SIZE) * pitch + delatax;

			ofFill();
		    // ofSetColor(ofColor(ofRandom(0, 255), ofRandom(0, 255),
	     //                ofRandom(0, 255)));
	    	if(map[i] == start || map[i] ==goal){
		    	ofSetColor(ofColor::orange);
	    		ofCircle(x, y, 20);
	    	}

	    	ofSetColor(ofColor::black);
	    	if(map[i]->isChecked()){
		    	ofSetColor(ofColor::green);
	    	}
	    	ofCircle(x, y, 5);

	    	ofSetColor(ofColor::black);
	    	ss << id;
		    myfont.drawString(ss.str(), x,y);
	    // ss.str("");
	    // ss.clear();
		}	

	}

	if(goalReached){
		for (int i = 0; i < path_found.size(); ++i){
			int id = path_found[i]->getId();
			int x = (id%SQRT_SIZE) * pitch + delatay;
			int y = (id/SQRT_SIZE) * pitch + delatax;
			ofFill();
	    	ofSetColor(ofColor::red);
	    	ofCircle(x, y, 5);
		}
	}

}
//--------------------------------------------------------------

// vector <vertex *> graph::compute_hop_dfs(){
void graph::next_hop(){
	vector < vertex * > new_path;
	int place = 0;
	if(!file.empty() && !goalReached){
		path = file.back(); // remove the first path from the QUEUE (FILE);
		file.pop_back();

		printf("\npath : [");
		for (int j = 0; j < path.size(); ++j)
			printf("%d,", path[j]->getId() );
			// printf("]");getchar();
			printf("]\n");
		
		vertex * plop ;
		plop = path.back();

		vertex * next = NULL;
		next = plop->nextCon_reverse();

		while(next != NULL && !goalReached){
		/* create new paths (to all children); */
			new_path =  path;
			next = plop->nextCon_reverse();
			if(next != NULL){
				next->setCheck(true);
				new_path.push_back(next);
				printf("\tNEW path : [");
				for (int j = 0; j < new_path.size(); ++j)
					printf("%d,", new_path[j]->getId() );
					// printf("]");getchar();
				printf("]\n");
			/*add the new paths to front of QUEUE (FILE);*/
				if(next->getId() == goal->getId()){
					goalReached = true;
					printf("\ngoalReached !!!!!\n");
					place = file.size();
				}
				if(!goalReached)
					switch(algoSelected){
						case DFS:
							place = file.size();
							break;
						case NDS:
							place = ofRandom(0, file.size());
							break;
						case GS:
							break;
						default:
							break;
					}
				file.insert(file.begin() + place, new_path);
			}
		}
		if(goalReached == true){
			path = file.back(); // remove the first path from the QUEUE (FILE);
			path_found = path;
			for (vector<vertex *>::iterator i = path.begin(); i != path.end(); ++i){
				vertex * plop;		
				plop = *i;
				printf("%d - ", plop->getId());
			}
			printf("\n");
		}
	}

}

//--------------------------------------------------------------

void graph::print_map_as_matrix(){
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

//--------------------------------------------------------------

void graph::print_matrix_as_csv(){
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
