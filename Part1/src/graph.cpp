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

}
//--------------------------------------------------------------

vector <vertex *> graph::compute_hop_dfs(){
	vector <vertex *> path, new_path;
	return path;
}

//--------------------------------------------------------------

vector <vertex *> graph::compute_hop_nds(){
	vector <vertex *> path, new_path;
	return path;
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
