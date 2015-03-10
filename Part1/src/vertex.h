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
    vector<point> getNeighbours();

    void setPosition(int h, int w, int map_size, int sqrt_size);
    point getPosition();

    void draw();

};



#endif
