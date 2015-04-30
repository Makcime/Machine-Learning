 /**
 * @file gameOfMill.h
 * @brief 
 *
 * @author Marlier Maxime <marlier.maxime@gmail.com>
 *
 **/

#ifndef GAMEOFFMILL		
#define GAMEOFFMILL

#include "gameDeck.h"
#include "player.h"

#define PAWN_NUMBER 9
#define BEERS 10

class GameOfMill
{

	string beers[BEERS] = {
	"barbar",
	"carapils",
	"chimay",
	"duff",
	"jupiler",
	"karmeliet",
	"kwak",
	"leffe",
	"orval",
	"westmalle"		
};

private:

	GameDeck* deck;
	Player* playerOne;
	Player* playerTwo;


public:
	GameOfMill();
	~GameOfMill();

	void draw();
	
};

#endif
