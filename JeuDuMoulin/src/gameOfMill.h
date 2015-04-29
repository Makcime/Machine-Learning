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

class GameOfMill
{

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
