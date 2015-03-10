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

class graph
{
private:
	vector < vertex * > map, path_found, new_path;
	vector < vector<vertex*> > file;

	vertex *start, *goal;

	bool goalReached;

	ofTrueTypeFont myfont;


	// vector < path > file;

public:
	graph();
	~graph();

	vector <vertex *> compute_hop_dfs();
	vector <vertex *> compute_hop_nds();

	void print_map_as_matrix();
	void print_matrix_as_csv();

	void set_points();

	void draw();

};

#endif
