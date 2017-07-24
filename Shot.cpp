#include "Shot.h"

Shot::Shot() {

}

Shot::~Shot() {
	
}
/*
This function creates a typ of shot. Enter an int (1-XX)
Y and X describes from with the shot is fired on the ship, not depending on its position. 
1. Rocket
2. Lazer
3. Dubblerocket
...
*/
void Shot::createShot(int type, int X, int Y) {
	this->_X = X;
	this->_Y = Y;
	this->_type = type;
	this->_fireRate = 1;
	if (type == 1) {
		

		this->_shot1 = "Missile_1.bmp";
		this->_speed = 20;
		this->width = 13;
		this->hight = 52;
		this->_fireRate = 2;
	} 
	else if (type == 2) { // Lazer
		
		
		this->_shot1 = "Lazer1.bmp";
		this->_speed = 40;
		this->width = 11;
		this->hight = 60;
		this->_fireRate = 1;

	}
	else if (type == 11) { // ENMYMISSILE
	

		this->_shot1 = "Missile2.bmp";
		this->_speed = 20;
		this->width = 13;
		this->hight = 52;
		this->_fireRate = 4;
		
	}
	else if (type == 12) { // ENMYLAZER
		
		this->_shot1 = "Lazer2.bmp";
		this->_speed = 30;
		this->width = 11;
		this->hight = 60;
		this->_fireRate = 7;

	}
}
/*
X and Y are the position of the ship
*/
void Shot::fire(int X, int Y) {
	this->xPos = X;
	this->yPos = Y;
	if(this->_type==1 || this->_type==11){
		PlaySound(TEXT("Missile.wav"), NULL, SND_FILENAME | SND_ASYNC);
	}else if (this->_type == 2 || this->_type == 12) {
		PlaySound(TEXT("Laser.wav"), NULL, SND_FILENAME | SND_ASYNC);
	}
}

void Shot::moveShot() {
	if(this->_type!=NULL){
	if (this->yPos > -50 && this->_type<10) {
		this->yPos = this->yPos - this->_speed;
	}
	else if(this->yPos < 850 && this->_type>10){
		this->yPos = this->yPos + this->_speed;
	}
	else {
		DestroyShot();
	}
	}
}
void Shot::drawShot() {
	
	if (this->_type!=NULL) {
		char *a = new char[this->_shot1.size() + 1];
		a[this->_shot1.size()] = 0;
		memcpy(a, this->_shot1.c_str(), this->_shot1.size());
		LoadBitmapFromFile(a, this->_bitmap);
		DrawBitmap(this->_bitmap, this->_X + this->xPos, this->_Y + this->yPos);
		FreeBitmap(this->_bitmap);
		delete[] a;
	}
	
}

std::array<int, 4> Shot::colData() {
	
	this->size[0] = this->xPos;
	this->size[1] = this->yPos;
	this->size[2] = this->xPos+this->width;
	this->size[3] = this->yPos+this->hight;
	return this->size;
}

int Shot::FR() {
	if (this->_fireRate == 0 || this->_fireRate == NULL) {
		this->_fireRate = 1;
	}
	return (1000 / this->_fireRate);
}

void Shot::DestroyShot() {
	
	this->_type = NULL;
	this->xPos = this->yPos = this->width = this->hight = -50;
}

