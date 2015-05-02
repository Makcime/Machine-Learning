#include "gameDeck.h"

GameDeck::GameDeck(){
	// gameGraph = new graph();
	background.loadImage(DECK_IMG);
	selectedVertex = this->map.begin();
	(*selectedVertex)->select(true);
	// nextPlace();
}

GameDeck::~GameDeck(){

}

void GameDeck::draw(int x, int y){

	int a = ofGetWidth()/2 ;
	background.resize(a, a);
	ofSetColor(255);
	background.draw(x, y);

	// graph::draw();

	point p = (*selectedVertex)->getPosition();
	ofSetColor(ofColor::green);
	ofFill();
	ofCircle(p.x, p.y, 15);

}

void GameDeck::nextPlace(){
	(*selectedVertex)->select(false);
	do{
		advance(selectedVertex, 1);
		if(selectedVertex == map.end())
			selectedVertex = map.begin();
	}while(!((*selectedVertex)->getConCnt()));

	(*selectedVertex)->select(true);
}

vertex * GameDeck::getSelection(){
	return (*selectedVertex);
}
