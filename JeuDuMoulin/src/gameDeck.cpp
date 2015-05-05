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


	point p = (*selectedVertex)->getPosition();
	ofSetColor(ofColor::green);
	ofFill();
	ofCircle(p.x, p.y, 15);
	
	// graph::draw();

}

void GameDeck::nextPlace(int* p){
	(*selectedVertex)->select(false);
	do{
		advance(selectedVertex, 1);
		if(selectedVertex == map.end())
			selectedVertex = map.begin();
	// }while(!((*selectedVertex)->getConCnt()));
	}while(*(p+(*selectedVertex)->getId()));

	(*selectedVertex)->select(true);
}

vertex * GameDeck::getSelection(){
	return (*selectedVertex);
}

int GameDeck::getSelectionById(){
	if((*selectedVertex))
		return (*selectedVertex)->getId();
	else
		return -1;
}

void GameDeck::initGameState(int* p){
		// gameState = {0};
	for (int i = 0; i < MAP_SIZE; ++i)
		if(map[i]->getConCnt() == 0)
			*(p+i) = -1;
}
