#include "gameOfMill.h"

GameOfMill::GameOfMill(){

	deck = new GameDeck();

	// generate 2 different random numbers
	int p1 = ofRandom(BEERS);
	int p2 = p1;

	while(p2 == p1)
		p2 = ofRandom(BEERS);

	playerOne = new Player(PAWN_NUMBER, beers[p1]);
	playerTwo = new Player(PAWN_NUMBER, beers[p2]);

	
	for (int i = 0; i < 5; ++i)
	{
		int j = ofRandom(48);
		if(deck->getMap()[j]->getConCnt())
			playerOne->play(ofRandom(PAWN_NUMBER) ,deck->getMap()[j]);
	}
	for (int i = 0; i < 5; ++i)
	{
		int j = ofRandom(48);
		if(deck->getMap()[j]->getConCnt())
			playerTwo->play(ofRandom(PAWN_NUMBER) ,deck->getMap()[j]);
	}

}

GameOfMill::~GameOfMill(){

}

void GameOfMill::draw(){

	// Draw players informations
	int screenH = ofGetHeight();;
	int screenW = ofGetWidth();
	int delta = (screenH - (screenW/2)) / 2;

	// Draw the game
	deck->draw((screenW / 2) - delta, delta);

	ofTrueTypeFont myfont;
	myfont.loadFont("arial.ttf", 40);

	ofSetColor(0);
	myfont.drawString("Player One :", 100 , 75 );
	playerOne->draw(100, 120);

	ofSetColor(0);
	ofLine(0, screenH/2, (screenW/2) - (2*delta), screenH/2);

	ofSetColor(0);
	myfont.drawString("Player Two :", 100,  (screenH/2)+75);
	playerTwo->draw(100, (screenH/2)+120);

	ofSetColor(0);
	ofLine((screenW/2) - (2*delta), 0, (screenW/2) - (2*delta) , screenH);

}
