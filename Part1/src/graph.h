/**
 * @file graph.h
 * @brief 
 *
 * @author Marlier Maxime <marlier.maxime@gmail.com>
 *
 **/

#ifndef GRAPH		
#define GRAPH	

#include <vector>
#include <string>
#include <algorithm>
#include "ofMain.h"
#include "vertex.h"

#define MAP_SIZE 49
#define SQRT_SIZE 7
#define	FILEPATH "../data/matrix.csv"

 #define DFS 1
 #define NDS 2
 #define GS 3

class graph
{
private:
	vector < vertex * > map, path_found, path;
	vector < vector<vertex*> > file;

	vertex *start, *goal;

	bool goalReached;

	ofTrueTypeFont myfont;

	int algoSelected;


	// vector < path > file;

public:
	graph();
	~graph();

	// vector <vertex *> compute_hop_dfs();
	void next_hop();
	vector <vertex *> compute_hop_nds();

	void print_map_as_matrix();
	void print_matrix_as_csv();

	void set_points();

	void draw();

	void resetPositions(int w, int h);

};

#endif
