#include "Collision.h"

Collision::Collision() {

}
/*
Tests if objects colide. Input is a vector with four objects, left, top, right, botom in that order. 
*/
bool Collision::ColTest(std::array<int, 4> obj1, std::array<int, 4> obj2) {
	

	if ((obj1[0] > obj2[2]) ||
		(obj1[1] > obj2[3]) ||
		(obj1[2] < obj2[0]) ||
		(obj1[3] < obj2[1])) {
		return false;
	}
	return true;
}

void Collision::ShowObj(int obj[4]) {
	// Ska visa objekt??
}