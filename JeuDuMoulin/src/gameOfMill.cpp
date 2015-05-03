#include "gameOfMill.h"

GameOfMill::GameOfMill(){

	deck = new GameDeck();

	bg.loadImage(BG);


	// generate 2 different random numbers
	int p1 = ofRandom(BEERS);
	int p2 = p1;

	while(p2 == p1)
		p2 = ofRandom(BEERS);

	playerOne = new Player(PAWN_NUMBER, beers[p1]);
	playerTwo = new Player(PAWN_NUMBER, beers[p2]);

	playerCnt = 1;
	currentPlayer = playerOne;

	deck->initGameState(gameState);

}

GameOfMill::~GameOfMill(){

}

void GameOfMill::draw(){

	// Draw players informations
	int screenH = ofGetHeight();;
	int screenW = ofGetWidth();
	int delta = (screenH - (screenW/2)) / 2;

	bg.resize(screenW, screenH);
	ofSetColor(255);
	bg.draw(0, 0);

	// Draw the game
	deck->draw((screenW / 2) - delta, delta);

	ofTrueTypeFont myfont;
	myfont.loadFont("arial.ttf", 40);


	ofSetColor(0);
	if(currentPlayer == playerOne)
		ofSetColor(ofColor::red);
	myfont.drawString("Player One :", 100 , 75 );
	playerOne->draw(100, 130);

	ofSetColor(0);
	ofLine(0, screenH/2, (screenW/2) - (2*delta), screenH/2);

	ofSetColor(0);
	if(currentPlayer == playerTwo)
		ofSetColor(ofColor::red);
	myfont.drawString("Player Two :", 100,  (screenH/2)+75);
	playerTwo->draw(100, (screenH/2)+130);

	ofSetColor(0);
	ofLine((screenW/2) - (2*delta), 0, (screenW/2) - (2*delta) , screenH);


}


void GameOfMill::selectPawn(){
	this->currentPlayer->nextPawn();
}

void GameOfMill::selectPlace(){
	this->deck->nextPlace(gameState);
}

void GameOfMill::Play(){

	int oldId = currentPlayer->getSelected()->getPositionById();
	if(currentPlayer->play(deck->getSelection())){
		gameState[oldId] = 0;
		gameState[deck->getSelectionById()] = (playerCnt-1)%2+1; 
		if((playerCnt++)%2)
			currentPlayer = playerTwo;
		else
			currentPlayer = playerOne;
	}
	CheckMills();
	selectPlace();
	printf("\n|----------------------------|\n|");
	for (int i = 0; i < MAP_SIZE; ++i)
	{
		if((!(i%7)) & i!=0)
			printf("|\n|");
		if(gameState[i]>=0)
			printf(" %02d ", gameState[i]);
		else
			printf("    ");
	}
	puts("|\n|----------------------------|");
}

void GameOfMill::CheckMills(){
	int p = 0;
	while (p<2){
		++p;
		for (int i = 0; i < MILLS; ++i){
			if(gameState[Mills[i][0]] == p & 
				gameState[Mills[i][1]] == p &
				gameState[Mills[i][2]] == p){
				printf("Mill for player %d\n", p);
				printf("%d-%d-%d\n", Mills[i][0],Mills[i][1],Mills[i][2]);
			}
		}
	}

}
