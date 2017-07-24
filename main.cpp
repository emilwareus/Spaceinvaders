#include "resource.h"
#include "Graphics.h"

#include "Game.h"
#include "Ship.h"
#include <fstream>
#include "HighScore.h"

char str[256] = { 0 };
Game game;
HighScore highscore;
const int MYEDIT_ID = 101;
const int MYBUTTON_ID = 102;
bool start = false;
std::string name;
HWND myEditBox;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps = { 0 };
		HDC hdc = BeginPaint(hwnd, &ps);
		EndPaint(hwnd, &ps);
		return 0; 
	}
	case WM_CLOSE:
		ShutdownGraphics();
		PostQuitMessage(0);
		return 0;
	
	case WM_CTLCOLOREDIT:
	{
		HDC hdc = (HDC)wParam;
		SetTextColor(hdc, RGB(255, 0, 0));  // yourColor is a WORD and it's format is 0x00BBGGRR
		return (LRESULT)GetStockObject(BLACK_BRUSH); // return a DC brush.
	}
	
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_FILE_NEW:
			game.InitializeGame(hwnd);
			return 0;

		case IDCLOSE:
			ShutdownGraphics();
			PostQuitMessage(0);
			return 0;

		case ID_HELP_ABOUT:
		
			MessageBox(hwnd, "This is a fun game", "About", MB_OK);


			return 0;

		case ID_FILE_HIGHSCORE:
			game.Highscore();

			return 0;

		case MYBUTTON_ID:
			start = true;
			GetWindowText(myEditBox, str, 256);
			name.clear();
			name.append(str);
			game.setName(name);
			return 0;

		}

		

	case WM_KEYDOWN:
		switch (LOWORD(wParam)) {
		case VK_RETURN:
			start = true;
		}
	

	
	}
	
	return DefWindowProc(hwnd, msg, wParam, lParam);
}



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	
	WNDCLASS wc = { 0 };
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = "MyWindowClass";
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);

	RegisterClass(&wc);
	HWND hwnd = CreateWindow(
		"MyWindowClass",
		"MyWindow",
		WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT,
		800, 800,
		0,
		0,
		hInstance, 0);



		 myEditBox = CreateWindow(
		"EDIT", // Fönsterklass
		" ", // Text i inmatningsrutan
		WS_CHILD | WS_VISIBLE | WS_BORDER, // Stil, OBS: WS_CHILD
		300, 300, // Position, relativt föräldern
		150, 20, // Storlek
		hwnd, // Förälderfönstrets handtag
		(HMENU)MYEDIT_ID, // Inmatningsrutans ID
		hInstance, // HINSTANCE som skickas med i WinMain
		0); // Avancerat, sätt till NULL


	HWND myBUTTON = CreateWindow(
		"BUTTON", // Fönsterklass
		"START", // Text i inmatningsrutan
		WS_CHILD | WS_VISIBLE | WS_BORDER, // Stil, OBS: WS_CHILD
		300, 350, // Position, relativt föräldern
		150, 40, // Storlek
		hwnd, // Förälderfönstrets handtag
		(HMENU)MYBUTTON_ID, // Inmatningsrutans ID
		hInstance, // HINSTANCE som skickas med i WinMain
		0); // Avancerat, sätt till NULL
	


	HFONT font = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
	UpdateWindow(hwnd);
	ShowWindow(hwnd, nCmdShow);
	
	
	//Startar spelet
	game.Splash(hwnd, hInstance);
	
	
	MSG msg = { 0 };
	
	while (GetMessage(&msg, 0, 0, 0) && start==false) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	
	DestroyWindow(myBUTTON);
	DestroyWindow(myEditBox);
	

	game.InitializeGame(hwnd);
	
	// Ny Gameloop
	for (;;)
	{
		MSG msg = { 0 };
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT){
				break;
			}
				
				

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Sleep(20);
			//game.UpdateGame();

		}
			
	}

	
	return 0;
}