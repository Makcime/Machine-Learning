 /**
 * @file gameDeck.h
 * @brief 
 *
 * @author Marlier Maxime <marlier.maxime@gmail.com>
 *
 **/

#ifndef GAMEFECK		
#define GAMEFECK

#include "graph.h"

#define DECK_IMG "../data/images/board.jpg"

class GameDeck : public graph
{
private:
	// graph* gameGraph;
	ofImage background;

public:
	GameDeck();
	~GameDeck();

	void draw(int x, int y);
	
};

#endif