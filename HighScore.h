#pragma once
#include <Windows.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "Graphics.h"

struct HighScore {
private:
	int _scores[5];
	std::string _names[5];

public:
	HighScore();
	void print();
	void loadfile();
	void add(std::string name, int score);
	void clear();
	void SaveToFile();

};