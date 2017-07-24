#pragma once
#include <Windows.h>
#include "Graphics.h"
#include "Ship.h"
#include "Shot.h"
#include <array>

class Collision {
private: 

public:
	Collision();
	bool ColTest(std::array<int, 4> obj1, std::array<int, 4> obj2);
	void ShowObj(int obj[4]);
};