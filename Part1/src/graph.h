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
 #define EEUC 4

class graph
{

struct path
{	
	vector < vertex * >	nodes;
	int cost;
};
private:
	vector < vertex * > map;
	path path_found;
	vector < path > file;

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
	void initGraph();
	void resetGraph();
	vector <vertex *> compute_hop_nds();

	void computeHeuristic();
	void computeCost(path *p);

	void print_map_as_matrix();
	void print_matrix_as_csv();

	void set_points();

	void draw();

	void resetPositions(int w, int h);

	bool isPresent(vertex * n, path v);
	void addFront(vector<path> vp) ;
	void addAtRandom(vector<path> vp);
	void addWithHeuristic(vector<path> vp);
	void addWithCost(vector<path> vp);


};

#endif
