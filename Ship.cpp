#include "Ship.h"


Ship::Ship() {
	
}
Ship::~Ship() {

}
/*
This will create a ship of model type
type is a number from 1 to Y
*/
void Ship::createShip(int type, int xStart, int yStart) {
	this->_X = xStart; // Middle =350
	
	this->ShipExist = true;
	this->ShipExist2 = true;

	//Your ships
	if (type == 1) {

		this->_Y = yStart;
		this->ship = "ship1.bmp";
		this->width = 57;
		this->hight = 98;
		this->_speed = 6;
	}
	if (type == 2) {

		this->_Y = yStart;
		this->ship = "ship2.bmp";
		this->width = 90;
		this->hight = 100;
		this->_speed = 8;
	}
	//Enemy Ships
	if (type == 11) {

		this->_Y = -100; // Bottom =600
		this->_Ygoal = yStart;

		this->ship = "Enemy.bmp";
		this->width = 101;
		this->hight = 101;
		this->_speed = 6;
	}

	if (type == 12) {

		this->_Y = -100; // Bottom =600
		this->_Ygoal = yStart;

		this->ship = "EnemyShip2.bmp";
		this->width = 124;
		this->hight = 104;
		this->_speed = 9;
	}
	if (type == 13) {

		this->_Y = -100; // Bottom =600
		this->_Ygoal = yStart;

		this->ship = "EnemyShip3.bmp";
		this->width = 40;
		this->hight = 40;
		this->_speed = 5;
	}
}


void Ship::drawShip() {
	if (this->_Ygoal > this->_Y) {
		this->_Y = this->_Y+3;
	}

	if (this->ShipExist == true) {
		char *a = new char[this->ship.size() + 1];
		a[this->ship.size()] = 0;
		memcpy(a, this->ship.c_str(), this->ship.size());

		LoadBitmapFromFile(a, this->_bitmapS);
		DrawBitmap(this->_bitmapS, this->_X, this->_Y);
		FreeBitmap(this->_bitmapS);
		delete[] a;
	}
	
}

void Ship::moveRight() {
	if (this->_X < 720) {
		this->_X = this->_X + this->_speed;
	}
}

void Ship::moveLeft() {
	if(this->_X>0){
	this->_X = this->_X - this->_speed;
	}
}

int Ship::getX() {
	return this->_X;
}

int Ship::getY() {
	return this->_Y;
}

std::array<int, 4> Ship::colData() {
	if (this->ShipExist == true) {
		this->size[0] = this->_X-30; //Skotten skjuter igenom skäppen ibland, därför är det -30 här. 
		this->size[1] = this->_Y;
		this->size[2] = this->_X + this->width;
		this->size[3] = this->_Y + this->hight;
	}
	return size;
}
int ExpVar = 0;
bool isOK = true;
UINT TimerIdExp;
VOID CALLBACK TimerProcExp(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime)
{
	ExpVar++;
	isOK = true;
	KillTimer(NULL, TimerIdExp);
}

bool Ship::ExplodeShip() {
	if(isOK==true){
	if (ExpVar==0){
		PlaySound("Explosion.wav", NULL, SND_FILENAME | SND_ASYNC);
		this->ship = "Explode1.bmp";
		this->width = 0;
		this->hight = 0;
		isOK = false;
		TimerIdExp = SetTimer(NULL, 0, 50, (TIMERPROC)&TimerProcExp);
	}else if (ExpVar == 1) {
		this->ship = "Explode2.bmp";
		isOK = false;
		TimerIdExp = SetTimer(NULL, 0, 50, (TIMERPROC)&TimerProcExp);
	}
	else if (ExpVar == 2) {
		this->ship = "Explode3.bmp";
		isOK = false;
		TimerIdExp = SetTimer(NULL, 0, 50, (TIMERPROC)&TimerProcExp);
	}
	else if (ExpVar == 3) {
		this->ship = "Explode4.bmp";
		isOK = false;
		TimerIdExp = SetTimer(NULL, 0, 50, (TIMERPROC)&TimerProcExp);
	}
	else {
		 this->ShipExist = false;
		 this->ShipExist2 = false;
		 isOK = true;
		 ExpVar = 0;
		 return true;
	}}
	return false;
}

bool Ship::exist() {
	return this->ShipExist2;
}
void Ship::DestroyShip() {
	
	this->ShipExist = false;
	this->ShipExist2 = false;
	FreeBitmap(this->_bitmapS);
}