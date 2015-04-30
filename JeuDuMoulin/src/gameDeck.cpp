#include "gameDeck.h"

GameDeck::GameDeck(){
	// gameGraph = new graph();
	background.loadImage(DECK_IMG);
}

GameDeck::~GameDeck(){

}

void GameDeck::draw(int x, int y){

	int a = ofGetWidth()/2 ;
	background.resize(a, a);
	ofSetColor(255);
	background.draw(x, y);

	// graph::draw();
}
