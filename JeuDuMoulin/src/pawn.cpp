#include "pawn.h"

Pawn::Pawn(){
}

Pawn::Pawn(string s){
	this->style = s;
	this->position = NULL;
	cap.loadImage(IMG_PATH + this->style + IMG_EXT);
	cap.resize(IMG_SIZE, IMG_SIZE);
}

Pawn::~Pawn(){

}

void Pawn::draw(int x, int y){
	ofSetColor(255);
	cap.draw(x - IMG_SIZE/2, y - IMG_SIZE/2);
}

vertex* Pawn::getPosition(){
	return this->position;
}

void Pawn::setPosition(vertex* pos){
	this->position = pos;
}


