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

void GameDeck::nextNeighbours(vertex* p, int* g){
	(*selectedVertex)->select(false);

	vector <vertex*> ngbrs = p->getNeighbours();

	bool plop = false;
	int pika = 0;
	vector<vertex *>::iterator j;

	puts("");
	printf("id %d\n", p->getId());
	printf("selectedVertex : %d \n", (*selectedVertex)->getId());
	for (std::vector<vertex *>::iterator i = ngbrs.begin(); i != ngbrs.end(); ++i){
		printf("ngbrs : %d \n", (*i)->getId());
		if((*i)->getId() == (*selectedVertex)->getId()){
			if(i != ngbrs.end()-1)
				j = i+1;
			else
				j = ngbrs.begin();
			while(j != i && plop == false){
				if (j == ngbrs.end())
					j = ngbrs.begin();
				if(!(*(g+(*j)->getId()))){
					pika = (*j)->getId();
					plop = true;
				}
				j++;
			}
			printf("Pika : %d \n", pika);
		}
	}

	if(!plop)
		for (std::vector<vertex *>::iterator i = ngbrs.begin(); i != ngbrs.end(); ++i){
			if(!(*(g+(*i)->getId()))){
				plop = true;
				pika = (*i)->getId();
				break;
			}
		}

	if(plop)
		selectedVertex = map.begin() + pika;
	else
		while(*(g+(*selectedVertex)->getId())){
			advance(selectedVertex, 1);
			if(selectedVertex == map.end())
				selectedVertex = map.begin();
		}

	printf("Pika : %d \n", pika);
	printf("selectedVertex : %d \n", (*selectedVertex)->getId());
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
