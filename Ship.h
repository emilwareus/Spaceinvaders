#pragma once
#include <Windows.h>
#include <iostream>
#include "Graphics.h"
#include <string>
#include <array>
#include <MMSystem.h>

struct Ship {
private:
	Bitmap _bitmapS;
	HWND _hwnd;
	int _X, _Y, _Ygoal;
	std::string ship;
	std::array<int, 4> size; 
	int width, hight;
	int _speed;
	bool ShipExist = false, ShipExist2=false;


public:
	Ship();
	~Ship();
	void createShip(int type, int yStart, int xStart);
	void drawShip();
	void moveRight();
	void moveLeft();
	int getX();
	int getY();
	std::array<int, 4> colData();
	bool ExplodeShip();
	bool exist();
	void DestroyShip();
};
