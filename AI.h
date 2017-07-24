#pragma once
#include <Windows.h>
#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */ 
#include <ctime>       /* time */

class AI {

private:
	int counter = 0;

public:
	AI();
	void createAI();
	int  getDest(int WindowSize);
	bool shot();


};