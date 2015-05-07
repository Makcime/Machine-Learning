#include "player.h"

Player::Player(){
}

Player::Player(int pawnsNb, string name){
	this->name = name;
	for (int i = 0; i < pawnsNb; ++i)
		this->pawns.push_back(new Pawn(this->name));
	selectedPawn = this->pawns.begin();
	(*selectedPawn)->select(true);

	this->miller = false;
}

Player::~Player(){

}

void Player::draw(int x, int y){
	// draw my name
	ofTrueTypeFont myfont;
	myfont.loadFont("arial.ttf", 40);

	ofSetColor(ofColor::black);
	transform(this->name.begin(), this->name.begin()+1,this->name.begin(), ::toupper);
	myfont.drawString(this->name, x , y );


	// draw my pawns
	int n;
	for (vector<Pawn*>::iterator i = this->pawns.end() -1; i != this->pawns.begin() -1; --i)
	{
		if((*i)->getPosition())
			(*i)->draw((*i)->getPosition()->getPosition().x , 
				(*i)->getPosition()->getPosition().y);
		else
			(*i)->draw((x + 20 *n) , y + 60);
		n++;
	}
}

bool Player::play(vertex* v){
	if((*selectedPawn)->getPosition()){
		vector<vertex *> ngbrs = (*selectedPawn)->getPosition()->getNeighbours();
		for (std::vector<vertex *>::iterator i = ngbrs.begin(); i != ngbrs.end(); ++i){
			if(v == (*i)){
				(*selectedPawn)->setPosition(v);
				// nextPawn();
				return true;
			}	
		}
	}else{
		(*selectedPawn)->setPosition(v);
		// nextPawn();
		return true;
	}
	return false;
}

void Player::nextPawn(){
	(*selectedPawn)->select(false);
	advance(selectedPawn, 1);
	if(selectedPawn == pawns.end())
		selectedPawn = pawns.begin();
	(*selectedPawn)->select(true);
}

void Player::nextFreePawn(){
	(*selectedPawn)->select(false);
	for (std::vector<Pawn*>::iterator i = pawns.begin();
		i != pawns.end(); ++i)
		if(!(*i)->getPosition())
			selectedPawn = i;
	(*selectedPawn)->select(true);
}


void Player::nextMovablePawn(){
	(*selectedPawn)->select(false);
	do{
		advance(selectedPawn, 1);
		if(selectedPawn == pawns.end())
		selectedPawn = pawns.begin();
	}while(!(*selectedPawn)->canMove());

	(*selectedPawn)->select(true);
}

Pawn* Player::getSelected(){
	return (*selectedPawn);
}

void Player::rmPawn(){
	pawns.erase(selectedPawn);
	selectedPawn = pawns.begin();
}

string Player::getName(){
	transform(this->name.begin(), this->name.begin()+1,this->name.begin(), ::toupper);
	return this->name;
}

bool Player::isMilling(){
	return this->miller;
}

void Player::setMiller(bool s){
	this->miller = s;
}

int Player::getPawnsCnt(){
	return this->pawns.size();
}

void Player::selectPawn(Pawn* p){
	for (vector<Pawn*>::iterator iter = pawns.begin(); 
		iter != pawns.end(); ++iter){
		if((*iter) == p)
			this->selectedPawn = iter;
	}	
}

void Player::selectPawn(int p){
	for (vector<Pawn*>::iterator iter = pawns.begin(); 
		iter != pawns.end(); ++iter){
		if((*iter)->getPositionById() == p)
			this->selectedPawn = iter;
	}	
}
