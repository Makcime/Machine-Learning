#include "gameDeck.h"

GameDeck::GameDeck(){
	gameGraph = new graph();
}

GameDeck::~GameDeck(){

}


void GameDeck::draw(){
	gameGraph->draw();
}
