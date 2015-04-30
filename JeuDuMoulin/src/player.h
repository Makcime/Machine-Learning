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

class Player
{

private:

	std::vector<Pawn *> pawns;
	string name; // orval, jupiler, etc

public:
	Player();
	Player(int pawnsNb, string name);
	~Player();

	void draw(int x, int y);
	void update();

	void play(int p, vertex* v);

};

#endif
