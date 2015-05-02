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

#define IMG_PATH "../data/images/"
#define IMG_EXT ".png"
#define IMG_SIZE 65


class Pawn
{

private:
	string style; // orval, jupiler, etc
	vertex * position;

	ofImage cap;

	bool selected;

public:
	Pawn();
	Pawn(string s);
	~Pawn();

	void draw(int x, int y);
	void update();

	vertex* getPosition();
	void setPosition(vertex* pos);

	void select(bool s);

};

#endif
