/**
 * @file player.h
 * @brief 
 *
 * @author Marlier Maxime <marlier.maxime@gmail.com>
 *
 **/

#ifndef PLAYER		
#define PLAYER	

#include <vector>
#include <string>
#include <algorithm>
#include "pawn.h"
#include "ofMain.h"
#include "vertex.h"
#include <iterator>

class Player
{

private:

	vector<Pawn *> pawns;
	vector<Pawn *>::iterator selectedPawn;
	string name; // orval, jupiler, etc

public:
	Player();
	Player(int pawnsNb, string name);
	~Player();

	void draw(int x, int y);
	void update();

	bool play(vertex* v);

	Pawn* getSelected();

	void nextPawn();

};

#endif
