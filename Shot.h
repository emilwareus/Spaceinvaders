#pragma once
#include <Windows.h>
#include "Graphics.h"
#include "Ship.h"
#include <array>
#include <string>
#include <MMSystem.h>

struct Shot {
private:
	int _speed;
	int _type;
	int _fireRate=1; // Shots / sec
	std::string _shot1;
	Bitmap _bitmap;
	std::array<int, 4> size;
	int width, hight;
	int _X, _Y, xPos, yPos;
public:
	Shot();
	~Shot();
	void createShot(int type, int X, int Y);
	void fire(int X, int Y);
	void moveShot();
	void drawShot();
	std::array<int, 4> colData();
	int FR();
	void DestroyShot();

};