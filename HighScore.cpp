#include "HighScore.h"
#include <fstream> 
using namespace std;

HighScore::HighScore() {
	
}

void HighScore::print() {
	
	for (int k = 0; k < 5; k++)	 {
		if (this->_scores[k] > 0) {
		const char * c = this->_names[k].c_str();
		DrawString(c, 350, 300 + k * 30);
		char fa[20];
		sprintf(fa, "%d", this->_scores[k]);
		DrawString(fa, 450, 300 + k * 30);
		}
	}
	
}

void HighScore::loadfile() {
	ifstream takedata;
	takedata.open("highscore.txt");
	if (takedata.is_open()) {
		for (int k = 0; k < 5; k++){
			takedata >> this->_names[k] >> this->_scores[k];
		}
		takedata.close();
	}
}

void HighScore::add(std::string name, int score) {

	int counter = 0;
	while (counter < 5) {
		if (score >= this->_scores[counter]) {
			int temp = 0;
			while((3-temp)>=counter){
			this->_scores[4 - temp] = this->_scores[3 - temp];
			this->_names[4 - temp] = this->_names[3 - temp];
			temp++;
			}
			this->_scores[counter] = score;
			this->_names[counter] = name;
			counter = 10;
			
		}
		counter++;
	}
	


}


void HighScore::clear() {
	ofstream cleardata;
	string s = " ";
	cleardata.open("highscore.txt");
	if (cleardata.is_open()) {
		cleardata << s;
		cleardata.close();
	}
}


void HighScore::SaveToFile() {
	 
	ofstream givedata;
	givedata.open("highscore.txt");
	if (givedata.is_open()) {
		for (int k = 0; k < 5; k++) {
			givedata << this->_names[k] << '\t' << this->_scores[k] << endl;
		}
		givedata.close();
	}
	
}

