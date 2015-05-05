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
	opponentPlayer = playerTwo;

	deck->initGameState(gameState);

	// gamePhase = PLACEMENT;
	newPhase();


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
	myfont.drawString("Player I :", 100 , 75 );
	playerOne->draw(100, 130);

	ofSetColor(0);
	ofLine(0, screenH/3, (screenW/2) - (2*delta), screenH/3);

	ofSetColor(0);
	if(currentPlayer == playerTwo)
		ofSetColor(ofColor::red);
	myfont.drawString("Player II :", 100,  (screenH/3)+75);
	playerTwo->draw(100, (screenH/3)+130);

	ofSetColor(0);
	ofLine(0, 2*screenH/3, (screenW/2) - (2*delta), 2*screenH/3);

	ofSetColor(0);
	ofLine((screenW/2) - (2*delta), 0, (screenW/2) - (2*delta) , screenH);

	string msg, mov;
	switch(gamePhase){
		case PLACEMENT:
			msg = "Le joueur " + currentPlayer->getName() + "\npeut poser une capsule";
			break;
		case MOUVEMENT:
			msg = "Le joueur " + currentPlayer->getName() + "\npeut déplacer une capsule";
			break;
		case REMOVING:
			msg = "Le joueur " + currentPlayer->getName() + "\npeut boire une " + opponentPlayer->getName();
			break;
		case EOG:
			msg = "Le joueur " + currentPlayer->getName() + "\ngagne la partie !";
			break;
	}

	myfont.loadFont("arial.ttf", 20);
	ofSetColor(0);
	myfont.drawString(msg, 100,  2*(screenH/3)+75);


}


void GameOfMill::selectPawn(){
	this->currentPlayer->nextPawn();
}

void GameOfMill::selectPawnToRm(){
	this->opponentPlayer->nextPawn();
}


void GameOfMill::selectPlace(){
	this->deck->nextPlace(gameState);
}

void GameOfMill::Play(){

	int oldId = currentPlayer->getSelected()->getPositionById();
	if(currentPlayer->play(deck->getSelection())){
		gameState[oldId] = 0;
		gameState[deck->getSelectionById()] = (playerCnt-1)%2+1;
		playerCnt++;
	}
	CheckMills(currentPlayer);
	if(!currentPlayer->isMilling()){
		currentPlayer->nextPawn();
		if(!((playerCnt)%2)){
			currentPlayer = playerTwo;
			opponentPlayer = playerOne;
		}
		else{
			currentPlayer = playerOne;
			opponentPlayer = playerTwo;
		}
		newPhase();
	}else
		gamePhase = REMOVING;
	
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

void GameOfMill::CheckMills(Player* pl){
	int p = 0;
	int playedPawn = pl->getSelected()->getPositionById();
	if(pl == playerOne) p=1;
	else if(pl == playerTwo) p=2;
	for (int i = 0; i < MILLS; ++i){
		if(gameState[Mills[i][0]] == p & 
			gameState[Mills[i][1]] == p &
			gameState[Mills[i][2]] == p){
			if(playedPawn == Mills[i][0] 
				|| playedPawn == Mills[i][1] 
				|| playedPawn == Mills[i][2]){
				printf("Mill for player %s\n", pl->getName().c_str());
				printf("%d-%d-%d\n", Mills[i][0],Mills[i][1],Mills[i][2]);
				pl->setMiller(true);
			} 
		}
	}
}

void GameOfMill::pawnCapture(){
	gameState[opponentPlayer->getSelected()->getPositionById()] = 0;
	opponentPlayer->rmPawn();
	currentPlayer->setMiller(false);

	if(!(playerCnt%2)){
		currentPlayer = playerTwo;
		opponentPlayer = playerOne;
	}
	else{
		currentPlayer = playerOne;
		opponentPlayer = playerTwo;
	}
	newPhase();
}

void GameOfMill::Go(){
	switch(gamePhase){
		case PLACEMENT:
			Play();
			break;
		case MOUVEMENT:
			Play();
			break;
		case REMOVING:
			pawnCapture();
			break;
	}
}

void GameOfMill::select(){
	switch(gamePhase){
		case PLACEMENT:
			selectPawn();
			break;
		case MOUVEMENT:
			selectPawn();
			break;
		case REMOVING:
			selectPawnToRm();
			break;
	}
}

void GameOfMill::newPhase(){

	if(opponentPlayer->getPawnsCnt() < 3)
		gamePhase = EOG;
	else if (playerCnt > 18)
		gamePhase = MOUVEMENT;
	else
		gamePhase = PLACEMENT;
}
