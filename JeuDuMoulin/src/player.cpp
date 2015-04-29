#include "player.h"

Player::Player(){
}

Player::Player(int nb){
	for (int i = 0; i < nb; ++i)
	{
		pawns.push_back(new Pawn(this->name));
	}
}

Player::~Player(){

}

void Player::draw(){
	for (vector<Pawn*>::iterator i = this->pawns.begin(); i != this->pawns.end(); ++i)
	{
		(*i)->draw();
	}

}
