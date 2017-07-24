#include "Game.h"




Game::Game() {
	
}

Game::~Game() {

}

void Game::setName(std::string name) {
	this->_name = name;
}



Bitmap b;
POINT p;
void Game::InitializeGame(HWND hwnd) {


	this->Initialized = false;
	for (int k = 0; k < 8; k++) {
		if (this->drones[k].exist()) {
			this->drones[k].DestroyShip();
			this->DronesExp[k] = false;
		}
	}
	for (int k = 0; k < 26; k++) {
		this->_shots[k].DestroyShot();
		this->_shotsE[k].DestroyShot();
	}

	hwnd = this->_hwnd;
	this->Initialized = false;
	this->ShowHS = false;
	this->_hwnd = hwnd;
	this->EnemyShip = 11;
	this->type = 1;
	
	this->EnemyExp=false;
	this->ShipExp = false;
	
	this->lives = 3;
	this->player = 0;
	


	// Chose your Ship
	InitializeGraphics(this->_hwnd);
	DrawString("Choose your ship", 330, 200);
	LoadBitmapFromFile("ship1.bmp", b);
	DrawBitmap(b, 250, 300);
	LoadBitmapFromFile("ship2.bmp", b);
	DrawBitmap(b, 450, 300);
	FreeBitmap(b);
	EndGraphics();
	ShutdownGraphics();

	
	
	GetCursorPos(&p);
	if (GetKeyState(VK_LBUTTON) & 0x80) {
	if (ScreenToClient(this->_hwnd, &p)) {
		if (p.x > 250 && p.x < 300 && p.y>300 && p.y<400) {
			this->type = 1;
			this->_enemyShip.createShip(this->EnemyShip, ai.getDest(800), 30);
			this->Initialized = true;
			
		}
		if (p.x > 450 && p.x < 540 && p.y>300 && p.y<400) {
			this->type = 2;
			this->_enemyShip.createShip(this->EnemyShip, ai.getDest(800), 30);
			this->Initialized = true;
			
		}
	}

	}

	this->_ship1.createShip(this->type, ai.getDest(800), 600);
	
}

void Game::Splash(HWND hwnd, HINSTANCE hInstance) {
	this->_hwnd = hwnd;
	Bitmap b;
	
	
	for (int y = 700; y >= 200; y=y-2){
	InitializeGraphics(this->_hwnd);
	LoadBitmapFromFile("Splash.bmp", b);
	DrawBitmap(b, 100, y);
	EndGraphics();  
	FreeBitmap(b);
	ShutdownGraphics();

	}
	while (GetAsyncKeyState(VK_SPACE) == false) {
		InitializeGraphics(this->_hwnd);
		LoadBitmapFromFile("Splash.bmp", b);
		DrawBitmap(b, 100, 200);
		DrawString("Press space to start!", 330, 500);
		EndGraphics();
		Sleep(20);
		FreeBitmap(b);
		ShutdownGraphics();

	
	}
	for (int y = 200; y <= 750; y=y+3) {
		InitializeGraphics(this->_hwnd);
		LoadBitmapFromFile("Splash.bmp", b);
		DrawBitmap(b, 100, y);
		EndGraphics();
		FreeBitmap(b);
		ShutdownGraphics();
	}
	ShutdownGraphics(); 
	

	
}

void Game::GameOver() {
	
		this->_HS.loadfile();
		InitializeGraphics(this->_hwnd);
		DrawString("GAME OVER", 350, 150);
		char x[20];
		DrawString("Your score: ", 340, 200);
		sprintf(x, "%d", this->player);
		DrawString(x, 435, 200);
		this->_HS.print();
		EndGraphics();
		ShutdownGraphics();
	

		
}

void Game::UpdateInput() {
	if ((GetKeyState(VK_LEFT) & 0x80) && this->ShipExp == false)
	{
		
		this->_ship1.moveLeft();
		
	}
	if ((GetKeyState(VK_RIGHT) & 0x80 )&& this->ShipExp == false)
	{
	
		this->_ship1.moveRight();
	
	}

	if (GetKeyState(VK_SPACE) & 0x80)
	{
		this->_fire = true;
	}


}

bool _rtf = true;
bool _rtfE = true;
UINT TimerId, TimerIdE, TimerId3, TimerId4;
VOID CALLBACK TimerProc(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime)
{
	_rtf = true;
	KillTimer(NULL, TimerId);
}

VOID CALLBACK TimerProc2(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime)
{
	_rtfE = true;
	KillTimer(NULL, TimerIdE);
}

bool newEShip = false;
VOID CALLBACK TimerProc3(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime)
{
	newEShip = true;
	KillTimer(NULL, TimerId3);
}

bool newShip = false;
VOID CALLBACK TimerProc4(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime)
{
	newShip = true;
	KillTimer(NULL, TimerId4);
}

bool tempVar = false;
void Game::UpdateLogic() {

	if (newEShip == true){  //Makes a new EnemyShip after it has exploded
		if((this->player) > 2){
			this->EnemyShip=12;
		}
		
		if (this->player > 5) { //Makes drones after score > 5
			this->drones[this->nrDrone].createShip(13, ai.getDest(800), 150);
			this->nrDrone++;
			if (this->nrDrone >= 8) {
				this->nrDrone = 0;
			}
		}
		

		this->_enemyShip.createShip(this->EnemyShip, ai.getDest(800), 30);
		newEShip = false;
		this->EnemyExp = false;
	}


	if (newShip == true) {	//Makes a new Ship after it has exploded
		this->lives--;
		if(this->lives>0){
		this->_ship1.createShip(this->type, ai.getDest(800), 600);
		this->ShipExp = false;
		}
		newShip = false;
		
		
	}

	// Move fired shots
		for (int k = 0; k < 26; k++) {
		this->_shots[k].moveShot();
		if (this->col.ColTest(this->_enemyShip.colData(), this->_shots[k].colData()) == true) {
			this->EnemyExp = true;
			this->EnemyExploding = true;
			this->_shots[k].DestroyShot();
			KillTimer(NULL, TimerId3);
			TimerId3 = SetTimer(NULL, 0, 2000, (TIMERPROC)&TimerProc3);
			this->player++;	
		}
		for (int f = 0; f < 8; f++) {
			if (this->drones[f].exist() && this->col.ColTest(this->drones[f].colData(), this->_shots[k].colData()) == true) {
				this->drones[f].ExplodeShip();
				this->_shots[k].DestroyShot();
				this->DronesExp[f] = true;
			}
		}
		}
	
	//Explodes Drones
		for (int k = 0; k < 8; k++) {
			if (this->DronesExp[k] == true) {
				this->DronesExp[k] =! this->drones[k].ExplodeShip();
			}
		}

		
	//Explodes Enemyship
		if(this->EnemyExploding==true){
			this->EnemyExploding =! this->_enemyShip.ExplodeShip();
		}

	// Fire a shot
	if(this->_fire==true && _rtf==true && this->ShipExp == false){
		if (this->ns > 25) {
			this->ns = 0;
		}
		this->_shots[this->ns].DestroyShot();
		
		if (this->type == 1) {
			this->_shots[this->ns].createShot(1, 19, 0);
		}
		else if (this->type == 2) {
			this->_shots[this->ns].createShot(2, 40, 0);
		}
		
		this->_shots[this->ns].fire(this->_ship1.getX(), this->_ship1.getY());
		this->ShipRTF = this->_shots[this->ns].FR();
		this->ns = this->ns + 1;
		TimerId = SetTimer(NULL, 0, this->ShipRTF, (TIMERPROC)&TimerProc);
		_rtf = false;
	}

	// ENEMY LOGIC =========================================================================
	

	if ((this->_enemyShip.getX() - this->EDest)< 5 && (this->_enemyShip.getX() - this->EDest) > -5 && this->EnemyExp == false) {
		this->EDest = ai.getDest(800);
	}
	else if (this->_enemyShip.getX() < this->EDest && this->EnemyExp == false) {
		this->_enemyShip.moveRight();
	}
	else if(this->_enemyShip.getX() > this->EDest && this->EnemyExp == false) {
		this->_enemyShip.moveLeft();
	}

	// DRONE LOGIC
	for (int k = 0; k < 8; k++) {
		if (this->drones[k].exist() == true) {
		if ((this->drones[k].getX() - this->droneDest[k])< 5 && (this->drones[k].getX() - this->droneDest[k]) > -5) {
			this->droneDest[k] = ai.getDest(850);
		}
		else if (this->drones[k].getX() < this->droneDest[k]) {
			this->drones[k].moveRight();
		}
		else if (this->drones[k].getX() > this->droneDest[k]) {
			this->drones[k].moveLeft();
		}
		
	}
	}
	
		// Move fired shots and test Collision
		for (int k = 0; k < 26; k++) {
			this->_shotsE[k].moveShot();
			if (this->col.ColTest(this->_ship1.colData(), this->_shotsE[k].colData())==true) {
				 this->ShipExp = true;
				 this->_shotsE[k].DestroyShot();
				 this->ShipExploding = true;
				 KillTimer(NULL, TimerId4);
				 TimerId4 = SetTimer(NULL, 0, 2000, (TIMERPROC)&TimerProc4);
			}
			
		}

	//Explode ship
		if (this->ShipExploding == true) {
			this->ShipExploding = !this->_ship1.ExplodeShip();
		}

	if (ai.shot() && _rtfE == true && this->EnemyExp == false) { // Enemy Fire
		if (this->nsE > 25) {
			this->ns = 0;
		}
		this->_shotsE[this->nsE].DestroyShot();
		this->_shotsE[this->nsE].createShot(11, 45, 30);
		this->_shotsE[this->nsE].fire(this->_enemyShip.getX(), this->_enemyShip.getY());
		this->EnemyRTF=this->_shotsE[this->nsE].FR();
		this->nsE = this->nsE + 1;
		KillTimer(NULL, TimerIdE);
		TimerIdE = SetTimer(NULL, 0, this->EnemyRTF, (TIMERPROC)&TimerProc2);
		_rtfE = false;
	}
	
	//DRONE FIRE
	for (int k = 0; k < 8; k++){
		if (this->drones[k].exist() && ai.shot()) {
			if (this->nsE > 25) {
				this->ns = 0;
			}
			this->_shotsE[this->nsE].DestroyShot();
			this->_shotsE[this->nsE].createShot(12, 20, 5);
			this->_shotsE[this->nsE].fire(this->drones[k].getX(), this->drones[k].getY());
			this->EnemyRTF = this->_shotsE[this->nsE].FR();
			this->nsE = this->nsE + 1;
		}
	}
	
	if(this->lives<=0){
	this->_HS.loadfile();
    this->_HS.add(this->_name, this->player);
	this->_HS.SaveToFile();
	}
	
	this->_fire = false;
	

}



void Game::RenderGame() {
	
	InitializeGraphics(this->_hwnd);

	
	for (int k = 0; k < 26; k++) {
		this->_shots[k].drawShot();
		this->_shotsE[k].drawShot();
	}

	if (this->player > 5) {
		for (int k = 0; k < 8;k++){
		this->drones[k].drawShip();
		}
	}


	this->_enemyShip.drawShip();
	this->_ship1.drawShip();
	
	char x[20];

	DrawString("Lives: ", 10, 10);
	sprintf(x, "%d", this->lives);
	DrawString(x, 55 , 10);

	DrawString("Captain: ", 10, 30);
	char *a = new char[this->_name.size() + 1];
		a[this->_name.size()] = 0;
	memcpy(a, this->_name.c_str(), this->_name.size());
	DrawString(a, 70, 30);
	delete a;

	DrawString("Score: ", 100, 10);
	sprintf(x, "%d", this->player);
	DrawString(x, 150, 10);
	
	EndGraphics();
	ShutdownGraphics();

	
}

void Game::Highscore() {
	this->ShowHS = true;
	
}

void Game::UpdateGame() {
	if (this->Initialized == false) {
		InitializeGame(this->_hwnd);
	}else{

	if(this->lives>0 && this->ShowHS == false){
	UpdateInput();
	UpdateLogic();
	RenderGame();
	}
	else if( this->ShowHS == false && this->lives <=0 ) {
		GameOver();
		
	}
	else if (this->ShowHS == true) {
		this->highscore.loadfile();
		InitializeGraphics(this->_hwnd);
		this->highscore.print();
		DrawString("Press space to continue", 340, 500);
		EndGraphics();
		ShutdownGraphics();

		if (GetKeyState(VK_SPACE) & 0x80)
		{
			this->ShowHS = false;;
		}
	}
	}
}

void Game::ShutdownGame() {
	
}