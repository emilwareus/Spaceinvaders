#include "AI.h"


AI::AI() {
	srand(time(NULL));
}

void AI::createAI() {


}

int AI::getDest(int WindowSize) {
	
	WindowSize = WindowSize - 100;
	
	return rand() % WindowSize;
}

bool AI::shot() {
	if (this->counter > 50) {
		srand(time(NULL)*counter);
	}
	this->counter++;
	int NewR;
	NewR = rand() % 100;
	if (NewR < 5) {
		return true;
	}
	return false;
}