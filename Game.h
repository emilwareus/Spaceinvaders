#pragma once
#include <Windows.h>
#include "Graphics.h"
#include "Ship.h"
#include "Shot.h"
#include "Collision.h"
#include "AI.h"
#include "HighScore.h"

class Game {
private:
	HighScore highscore;
	std::string _name;
	HighScore _HS;
	bool Initialized= false;
	int lives=0, player=0;
	int type;
	int EnemyShip = 11;
	Ship _ship1, _enemyShip;
	Ship drones[8];
	int droneDest[8];
	int nrDrone = 0;
	bool DronesExp[8];
	bool ShowHS = false;
	HWND _hwnd;
	Collision col;
	AI ai;
	Shot _shots[26], _shotsE[26];
	int ns=0, nsE=0;// number of shots in air
	bool EnemyExploding = false, ShipExploding=false;	
	int EnemyRTF = 0, ShipRTF = 0;
	int EDest=350;
	bool _fire=false, EnemyExp=false,
		ShipExp=false;
public:
	Game();
	~Game();
	void Game::setName(std::string name);
	void Splash(HWND hwnd, HINSTANCE hInstance);
	void GameOver();
	void InitializeGame(HWND hwnd);
	void UpdateInput();
	void UpdateLogic();
	void RenderGame();
	void Highscore();
	void UpdateGame();
	void ShutdownGame();
	
};

