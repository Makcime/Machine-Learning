/**
 * @file station.h
 * @brief 
 *
 * @author Marlier Maxime <marlier.maxime@gmail.com>
 *
 **/

#ifndef VERTEX		
#define VERTEX	

using namespace std;

#include <vector>
#include <string>
#include <algorithm>
// #include "ofApp.h"

struct point
{
    int x, y;
};

class vertex    
{

struct connection
{
	vertex * node;
	int weight;
};


private:
    // string name;
	// vector < vertex * > connected;
	vector < connection > connected;
	bool check;
	int indice;
    connection con;
    point position;

    int heuristic;

public:
    vertex();
    vertex(int i, int h, int w, int map_size, int sqrt_size);
    void add_connection(vertex * con, int weight);
    void add_connection(vertex * con);
    int is_connected(vertex * con);


	int getId();
    int getConCnt();

    void setCheck(bool state);
    bool isChecked();

    vertex* nextCon();
    vertex* nextCon_reverse();
    vector<int> getIds();
    vector<point> getNeighboursPos();
    vector<vertex *> getNeighbours();

    void setHeuristic(int val);
    int getHeuristic();

    void computeWeights();

    void setPosition(int h, int w, int map_size, int sqrt_size);
    void setPosition(int x, int y);
    point getPosition();

    void draw();

    int getCost(vertex *v);

};



#endif
