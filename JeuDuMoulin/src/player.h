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

class Player
{

private:

	std::vector<Pawn *> pawns;
	string name; // orval, jupiler, etc

public:
	Player();
	Player(int nb);
	~Player();

	void draw();
	void update();

};

#endif
