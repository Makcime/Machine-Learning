#include "gameOfMill.h"

GameOfMill::GameOfMill(){

	deck = new GameDeck();
	playerOne = new Player(PAWN_NUMBER);
	playerTwo = new Player(PAWN_NUMBER);

}

GameOfMill::~GameOfMill(){

}

void GameOfMill::draw(){
	playerOne->draw();
	playerTwo->draw();

	deck->draw();

}
