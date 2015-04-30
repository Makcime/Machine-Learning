#include "player.h"

Player::Player(){
}

Player::Player(int pawnsNb, string name){
	this->name = name;
	for (int i = 0; i < pawnsNb; ++i)
		pawns.push_back(new Pawn(this->name));
}

Player::~Player(){

}

void Player::draw(int x, int y){
	// draw my name
	ofTrueTypeFont myfont;
	myfont.loadFont("arial.ttf", 40);

	ofSetColor(ofColor::black);
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

void Player::play(int p, vertex* v){
	this->pawns[p]->setPosition(v);
}



