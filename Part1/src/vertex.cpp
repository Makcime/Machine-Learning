#include "vertex.h"

vertex::vertex(){
	
}

vertex::vertex(int i, int h, int w, int map_size, int sqrt_size){
	indice = i;
	setPosition(h, w, map_size, sqrt_size);
}


void vertex::add_connection(vertex * v, int w){
	struct connection con;
	con.node = v;
	con.weight = w;
	connected.push_back(con);
	check = false;
}

void vertex::add_connection(vertex * v){
	struct connection con;
	con.node = v;
	con.weight = 1;
	connected.push_back(con);
	check = false;
}

int vertex::is_connected(vertex * con){
	for (int i = 0; i<connected.size(); ++i)
	{
		if (con == connected[i].node)
		{
			return connected[i].weight;
		}
	}

	return 0;
}

void vertex::setCheck(bool state){
	check = state;
}

bool vertex::isChecked(){
	return check;
}

vertex* vertex::nextCon(){
	for (int i = 0; i < connected.size(); ++i)
		if (!connected[i].node->isChecked()){
			// connected[i].node->setCheck(true);
			return connected[i].node;
		}

	return NULL;
}

vertex* vertex::nextCon_reverse(){
	for (int i = connected.size(); i > 0; --i)
		if (!connected[i-1].node->isChecked()){
			// connected[i].node->setCheck(true);
			return connected[i-1].node;
		}

	return NULL;
}


int vertex::getId(){
	return indice;
}

int vertex::getConCnt(){
	return (int) connected.size();
}

vector<int> vertex::getIds(){
	vector<int> v;
	for (int i = 0; i < connected.size(); ++i)
		v.push_back(connected[i].node->getId());

	return v;
}

void vertex::setPosition(int h, int w, int map_size, int sqrt_size){
	int pitch = h/ (sqrt_size+1);
	int delatax = pitch ;

	int delatay = (w - h) /2 + pitch;

	position.x = (indice%sqrt_size) * pitch + delatay;
	position.y = (indice/sqrt_size) * pitch + delatax;
}

point vertex::getPosition(){
	return position;
}

vector<point> vertex::getNeighbours(){
	vector<point> v;
	for (int i = 0; i < connected.size(); ++i)
		v.push_back(connected[i].node->getPosition());

	return v;	
}



