//=========================================================================================================|
// Project:
//	NEST - an acronynm for Nintendo Entertainment System Emulator that emulates guess what NES console 
//	features from back in 70/80's. This is version 2 a complete re-write of my lost NEST v1 code (RIP). 
//
// Inspired By:
//	One Lone Coder projects, courtesy of Javidx9.
//
// Program Author:
//	Aethiopis II ben Zahab
//
// Date Created:
//	14th of November 2022, Monday
//
// Last Update:
//	15th of Novemeber 2022, Tuesday
//
// Compiled On:
//	HP Pavallion (Areselaliyur) running on Intel Core I7 16GB RAM on Microsoft's Windows 11. 
//	Microsoft's Visual Studio 2022 Community IDE
//=========================================================================================================|

//=========================================================================================================|
// DEFINES
//=========================================================================================================|
#define WINDOW_NAME		"Rediet Worku's NEST"
#define CLASS_NAME		"RW_NEST"
#define WINDOW_WIDTH	1024
#define WINDOW_HEIGHT	768
#define WINDOW_BPP		32




//=========================================================================================================|
// INCLUDES
//=========================================================================================================|
#include <Windows.h>
#include <stdio.h>

#include "OldX.h"
#include "Bus.h"

//=========================================================================================================|
// MACROS
//=========================================================================================================|
// center the window at start, I like it that way
#define WINDOW_X		((GetSystemMetrics(SM_CXSCREEN) >> 1) - (WINDOW_WIDTH >> 1))
#define WINDOW_Y		((GetSystemMetrics(SM_CYSCREEN) >> 1) - (WINDOW_HEIGHT >> 1))
#define WINDOW_STYLE	WS_OVERLAPPEDWINDOW

#define WIN_ERR(m, c)	{snprintf(text, MAX_PATH, "Error: %s - %d", m, c); \
						 MessageBoxA(NULL, text, "Err Box", MB_ICONERROR);}


// read keyboard in async mode; pull me a fast one on Windows
#define KEY_DOWN(vkcode)	(GetAsyncKeyState(vkcode) & 0x80) ? 1 : 0


// virtual key code constants
#define VK_F	0x46



//=========================================================================================================|
// GLOBALS
//=========================================================================================================|
HINSTANCE main_instance = NULL;
HWND main_window_handle = NULL;

char text[MAX_PATH];		// gen text buffer
bool bfullscreen = true;	// tracks the state of screen
Bus bus;




//=========================================================================================================|
// PROTOTYPES
//=========================================================================================================|
LRESULT CALLBACK Main_Window_Proc(HWND, UINT, WPARAM, LPARAM);
int Init();
int Run();
int Shutdown();



//=========================================================================================================|
// FUNCTIONS
//=========================================================================================================|
// main window envent handler, as it is called ...
LRESULT CALLBACK Main_Window_Proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	// what's the message?
	switch (msg)
	{
	case WM_CREATE:
	{

	} break;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		EndPaint(hwnd, &ps);
	} break;

	case WM_DESTROY:
	{
		DestroyWindow(hwnd);
		PostQuitMessage(0);
	} break;

	default:
		return (DefWindowProcA(hwnd, msg, wparam, lparam));
	} // end switch

	return 0;
} // end Main_Window_Proc


//=========================================================================================================|
// program entry point
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEXA win;
	MSG msg;

	// as usual fill up the window class
	win.cbClsExtra = 0;
	win.cbSize = sizeof(win);
	win.cbWndExtra = 0;
	win.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	win.hCursor = LoadCursorA(NULL, MAKEINTRESOURCEA(32512));
	win.hIcon = LoadIconA(NULL, MAKEINTRESOURCEA(32512));
	win.hIconSm = LoadIconA(NULL, MAKEINTRESOURCEA(32512));
	win.hInstance = hInstance;
	win.lpfnWndProc = Main_Window_Proc;
	win.lpszClassName = CLASS_NAME;
	win.lpszMenuName = NULL;
	win.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS | CS_OWNDC;
	main_instance = hInstance;


	if (!RegisterClassExA(&win))
	{
		WIN_ERR("RegisterClassEx", GetLastError());
		return 0;
	} // end if somethin bad

	if (!(main_window_handle = CreateWindowExA(0, CLASS_NAME, WINDOW_NAME,
		WINDOW_STYLE,
		WINDOW_X, WINDOW_Y,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		NULL, NULL, hInstance, NULL)))
	{
		WIN_ERR("CreateWindowEx", GetLastError());
		return 0;
	} // end if

	ShowWindow(main_window_handle, nCmdShow);
	UpdateWindow(main_window_handle);

	Init();
	while (1)
	{
		if (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		} // end if peek

		Run();
	} // end while

	Shutdown();
	return ((int)msg.wParam);
} // end WinMain


//=========================================================================================================|
// Initalizes the Emulator; graphics engine and sound (this is old skool DirectX library)
int Init()
{
	// initalize graphics
	if (Init_DDraw(WINDOW_WIDTH, WINDOW_HEIGHT) < 0)
		return -1;

	bus.cpu6502.Reset();
	return 0;
} // end Init


//=========================================================================================================|
// Runs the emulator locked at 16 fps just like good old NES does; I never had NES (though I played it one
//	too many times, however, I had a fake console that is pretty much NES rip-off in a cheap way, it was
//	called Terminator 2 yah, just like the terminator, had six buttons that I never got to figure why since
//	only two were used on these games ...).
int Run()
{
	// test user key's first at every iteration
	if (KEY_DOWN(VK_ESCAPE))
	{
		PostQuitMessage(0);
		return;
	} // end if


	if (KEY_DOWN(VK_F))
	{
		Shutdown_DDraw();
		bfullscreen = !bfullscreen;
		Init_DDraw(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_BPP, bfullscreen);
	} // en if toggle fullscreen


	bus.cpu6502.Clock();
	return 0;
} // end Run


//=========================================================================================================|
// Shutdown and clean the resources once we done with this baby; mainly handles DirectX directdraw and 
//	direct sound stuff.
int Shutdown()
{
	Shutdown_DDraw();
	return 0;
} // end shutdown


//=========================================================================================================|
//			THE END
//=========================================================================================================|