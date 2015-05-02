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
	vector<vertex *>::iterator selectedVertex;

public:
	GameDeck();
	~GameDeck();

	void draw(int x, int y);
	void nextPlace();
	vertex * getSelection();
	int getSelectionById();

	void initGameState(int* p);

	
};

#endif