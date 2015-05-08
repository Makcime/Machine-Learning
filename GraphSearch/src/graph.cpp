#include "graph.h"

//--------------------------------------------------------------

graph::graph(){
	myfont.loadFont("arial.ttf", 9.5);

	for (int i = 0; i < MAP_SIZE; ++i)
		map.push_back(new vertex(i, ofGetHeight(), ofGetWidth(), MAP_SIZE, SQRT_SIZE));

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

	// print_map_as_matrix();

	start = map[6];
	goal = map[43];


	initGraph();

}

string graph::getStart(){
	stringstream ss;
	ss << start->getId();

	return ss.str();
}

string graph::getGoal(){
	stringstream ss;
	ss << goal->getId();

	return ss.str();
}



//--------------------------------------------------------------

graph::~graph(){

}

//--------------------------------------------------------------

void graph::draw(){
	for(int i = 0; i < MAP_SIZE; ++i)
	{
		vector<vertex*> v = map[i]->getNeighbours();
		// vector<point> v = map[i]->getNeighbours();
		
		point p = map[i]->getPosition();
		int x = p.x;
		int y = p.y;

		int id = map[i]->getId();
		if (map[i]->getConCnt()){
			stringstream ss;
			
			// drawing lines :
		   	int _x, _y; 
		    for (int j = 0; j < v.size(); ++j)
		    {
		    	_x = v[j]->getPosition().x;
		    	_y = v[j]->getPosition().y;
		    	ofLine(x, y, _x, _y);
		    	int c = map[i]->getCost(v[j]);
		    	if(c > 0 ){
			    	ss << c;
				    myfont.drawString(ss.str(), x + (_x - x)/2 , y  + (_y - y)/2);
			    	ss.str("");
					ss.clear();
		    	} 
		    }

			ofFill();
		    // ofSetColor(ofColor(ofRandom(0, 2510, ofRandom(0, 255),
	     //                ofRandom(0, 255)));
	    	if(map[i] == start || map[i] == goal){
		    	ofSetColor(ofColor::orange);
	    		ofCircle(x, y, 20);
	    	}

	    	ofSetColor(ofColor::black);
	    	if(map[i]->isChecked()){
		    	ofSetColor(ofColor::green);
	    	}
	    	ofCircle(x, y, 8);

	    	ofSetColor(ofColor::white);
	    	ss << map[i]->getHeuristic() << endl;
	    	ss << map[i]->getId();
		    myfont.drawString(ss.str(), x,y);
	    	ofSetColor(ofColor::black);
		}	

	}

	if(goalReached){
		for (int i = 0; i < path_found.nodes.size(); ++i){
			point p = path_found.nodes[i]->getPosition();
			int x = p.x;
			int y = p.y;
			ofFill();
	    	ofSetColor(ofColor::red);
	    	ofCircle(x, y, 8);
		}
	}else{
		for (int i = 0; i < file.back().nodes.size(); ++i){
			point p = file.back().nodes[i]->getPosition();
			int x = p.x;
			int y = p.y;
			ofFill();
	    	ofSetColor(ofColor::red);
	    	ofCircle(x, y, 8);
		}
	}	

}
//--------------------------------------------------------------

bool graph::isPresent(vertex * n, path v){
	for (int i = 0; i < v.nodes.size(); ++i)
		if(v.nodes[i] == n)
			return true;

	return false;
}

void graph::computeCost(path *p){
	int accuCost = 0;
	for (int i = 0; i < p->nodes.size()-1; ++i)
		accuCost += p->nodes[i]->getCost(p->nodes[i+1]);

	p->cost = accuCost + p->nodes.back()->getHeuristic();
}

void graph::addFront(vector<path> vp) {
	for (int i = vp.size(); i > 0; --i){
		file.push_back(vp[i-1]);
	}
}

void graph::addAtRandom(vector<path> vp){
	for (int i = 0; i < vp.size(); ++i){
		file.insert(file.begin() + ofRandom(0, file.size())
			, vp[i]);
	}
}

void graph::addWithHeuristic(vector<path> vp){
	int indice = 0; 
	int heur;
	for (int i = 0; i < vp.size(); ++i){
		heur = vp[i].nodes.back()->getHeuristic();
		indice = file.size();
		if(!file.empty()){
			while(file[indice-1].nodes.back()->getHeuristic() <= heur){
				indice--;
				if(indice == 0)
					break;
			}
		}
		file.insert(file.begin() + indice , vp[i]);
	}

}

void graph::addWithCost(vector<path> vp){
	int indice = 0; 
	int cost;
	for (int i = 0; i < vp.size(); ++i){
		cost = vp[i].cost;
		indice = file.size();
		if(!file.empty()){
			while(file[indice-1].cost <= cost){
				indice--;
				if(indice == 0)
					break;
			}
		}
		file.insert(file.begin() + indice , vp[i]);
	}
}

// vector <vertex *> graph::compute_hop_dfs(){
void graph::next_hop(){
	static int cnt = 0;
	static int max_queue_zise = 0;
	cnt++;
	
	if(this->file.size()>max_queue_zise)
		max_queue_zise = this->file.size();


	// printf("cnt = %d\n", cnt);
	// printf("max_queue_zise = %d\n", max_queue_zise);
	
	path new_path, last_path, eeuc_last_path;
	vector<path> new_path_list;
	vertex * last_node;
	vector<vertex *> neighborhood;

	if(!file.empty() && !goalReached){
		last_path = file.back(); // remove the first path from the QUEUE (FILE);
		file.pop_back();

		// printf("\npath : [");
		// for (int j = 0; j < last_path.nodes.size(); ++j)
		// 	printf("%d,", last_path.nodes[j]->getId());
		// 	printf("] -> cost : %d\n", last_path.cost);
		
		last_node = last_path.nodes.back();

		neighborhood = last_node->getNeighbours();

		for (int i = 0; i < neighborhood.size(); ++i){
			neighborhood[i]->setCheck(true);
			if(!isPresent(neighborhood[i], last_path)){
				new_path = last_path;
				new_path.nodes.push_back(neighborhood[i]);
				computeCost(&new_path);
				new_path_list.push_back(new_path);

				// printf("\tNEW path : [");
				// for (int j = 0; j < new_path.nodes.size(); ++j)
				// 	printf("%d,", new_path.nodes[j]->getId() );
				// printf("] -> cost : %d\n", new_path.cost);
			}
		}

		// for (int i = 0; i < new_path_list.size(); ++i){
		switch(algoSelected){
			case DFS:
				addFront(new_path_list);
				break;
			case NDS:
				addAtRandom(new_path_list);
				break;
			case GS:
				addWithHeuristic(new_path_list);	
				break;
			case EEUC:
				addWithCost(new_path_list);
				break;
		}
		// }

		if(algoSelected == EEUC){
			eeuc_last_path = file.back();
			if(eeuc_last_path.nodes.back() == goal){
				goalReached = true;
				// printf("\n!! -- Goal reached -- !!\n");
				path_found = eeuc_last_path;
			}
		}else{
			for (int i = 0; i < new_path_list.size(); ++i)
				if(new_path_list[i].nodes.back() == goal){
					goalReached = true;
					// printf("\n!! -- Goal reached -- !!\n");
					path_found = new_path_list[i];
				}
		}

		// printf("\nFile : [\n");
		// for (int i = 0; i < file.size(); ++i){
		// 	printf("  Cost : %6d |", file[i].cost);
		// 	printf(" Path :[");
		// 	for (int j = 0; j < file[i].nodes.size(); ++j)
		// 		printf("%d,", file[i].nodes[j]->getId() );
		// 		printf("]\n");
		// }
		// printf("]\n");

		if(goalReached == true){
			// for (int i = 0; i < path_found.nodes.size(); ++i)
			// 	printf("%d - ", path_found.nodes[i]->getId());
			// printf("\n");
			result rs;
			rs.algo = algoSelected;
			rs.speed = cnt;
			cnt = 0;
			rs.memory = max_queue_zise;
			rs.pth = path_found.nodes.size();
			rs.cst = path_found.cost;
			rs.goal = goal->getId();
			rs.start = start->getId();

			resultSet.push_back(rs);

		}
	}
}

void graph::testing(){
	for (int ALGO = 1; ALGO < 5; ++ALGO)
		for (int i = 0; i < MAP_SIZE; ++i)
			for (int j = 0; j < MAP_SIZE; ++j){
				if(i!=j)
					if(map[i]->getConCnt() && map[j]->getConCnt()){
						resetGraph(i, j, ALGO);
						while(!goalReached)
							next_hop();
					}
			}
	printResults();
}

void graph::printResults(){
	printf("algo; speed; memory; pth; cst; start; goal\n");
	for (int i = 0; i < resultSet.size(); ++i)
	{
		printf("%d;%d;%d;%d;%d;%d;%d \n", 
			resultSet[i].algo, resultSet[i].speed, 
			resultSet[i].memory, resultSet[i].pth, resultSet[i].cst, 
			resultSet[i].start, resultSet[i].goal);
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

void graph::resetPositions(int w, int h){
	for (int i = 0; i < map.size(); ++i)
		map[i]->setPosition(h, w, MAP_SIZE, SQRT_SIZE);

	computeHeuristic();

	for (int i = 0; i < map.size(); ++i)
		map[i]->computeWeights();
}

void graph::resetGraph(){
	for (int i = 0; i < MAP_SIZE; ++i){
		map[i]->setCheck(false);
	}
	goalReached = false;
	path_found.nodes.clear();
	file.clear();

	start = map[0];
	goal = map[48];

	initGraph();

	// algoSelected = NDS;
};

void graph::resetGraph(int s, int g, int algo){
	for (int i = 0; i < MAP_SIZE; ++i){
		map[i]->setCheck(false);
	}
	goalReached = false;
	path_found.nodes.clear();
	file.clear();

	start = map[s];
	goal = map[g];

	initGraph();

	algoSelected = algo;

};


void graph::computeHeuristic(){
	point p1, p2;
	int heuristic;
	for (int i = 0; i < MAP_SIZE; ++i){
		p1 = map[i]->getPosition();
		p2 = goal->getPosition();
		heuristic = (int) sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
		map[i]->setHeuristic(heuristic);
	}
}

void graph::initGraph(){
	path p; 
	p.nodes.push_back(start);
	computeCost(&p);
	file.push_back(p);
	start->setCheck(true);
	goalReached = false;

	algoSelected = DFS;

	computeHeuristic();

}