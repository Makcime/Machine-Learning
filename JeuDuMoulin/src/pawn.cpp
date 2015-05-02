#include "pawn.h"

Pawn::Pawn(){
}

Pawn::Pawn(string s){
	this->style = s;
	this->position = NULL;
	cap.loadImage(IMG_PATH + this->style + IMG_EXT);
	cap.resize(IMG_SIZE, IMG_SIZE);

	this->selected = false;
}

Pawn::~Pawn(){

}

void Pawn::draw(int x, int y){
	if(this->selected){
		ofSetColor(ofColor::red);
		ofCircle(x, y, (IMG_SIZE/2) + 5);
	}
	
	ofSetColor(255);
	cap.draw(x - IMG_SIZE/2, y - IMG_SIZE/2);
}

vertex* Pawn::getPosition(){
	return this->position;
}

void Pawn::setPosition(vertex* pos){
	this->position = pos;
}

void Pawn::select(bool s){
	this->selected = s;
}


