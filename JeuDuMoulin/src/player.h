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

protected:
	vector<Pawn *> pawns;
	vector<Pawn *>::iterator selectedPawn;
	string name; // orval, jupiler, etc

	bool miller;

public:
	Player();
	Player(int pawnsNb, string name);
	~Player();

	void draw(int x, int y);
	void update();

	bool play(vertex* v);

	Pawn* getSelected();
	void selectPawn(Pawn* p);
	void selectPawn(int p);

	void nextPawn();
	void nextFreePawn();
	void rmPawn();

	string getName();

	bool isMilling();
	void setMiller(bool s);

	int getPawnsCnt();

	void nextMovablePawn();

};

#endif
