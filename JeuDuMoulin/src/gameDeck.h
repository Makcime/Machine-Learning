 /**
 * @file gameDeck.h
 * @brief 
 *
 * @author Marlier Maxime <marlier.maxime@gmail.com>
 *
 **/

 #include "graph.h"

#ifndef GAMEFECK		
#define GAMEFECK

class GameDeck
{
private:
	graph* gameGraph;


public:
	GameDeck();
	~GameDeck();

	void draw();
	
};

#endif