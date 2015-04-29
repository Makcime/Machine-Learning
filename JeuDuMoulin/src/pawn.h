 /**
 * @file pawn.h
 * @brief 
 *
 * @author Marlier Maxime <marlier.maxime@gmail.com>
 *
 **/

#ifndef PAWN		
#define PAWN	

#include <vector>
#include <string>
#include <algorithm>
#include "ofMain.h"
#include "vertex.h"

class Pawn
{

private:
	string style; // orval, jupiler, etc
	vertex * position;

public:
	Pawn();
	Pawn(string s);
	~Pawn();

	void draw();
	void update();

};

#endif
