//=========================================================================================================|
// Desc:
//	A little graphics library based on old skool Microsoft's DirectX - IDirectDraw7 intefrace. This will act
//	as the graphics engine for my little emulator NEST (reBorne).
//
// Program Author:
//	Aethiopis II ben Zahab
//
// Date Created:
//	24th of November 2022, Thursday
//
// Last Update:
//	24th of Novemeber 2022, Thursday
//
// Compiled On:
//	HP Pavallion (Areselaliyur) running on Intel Core I7 16GB RAM on Microsoft's Windows 11. 
//	Microsoft's Visual Studio 2022 Community IDE
//=========================================================================================================|
#ifndef XGRAPHICS_H
#define XGRAPHICS_H


//=========================================================================================================|
// INCLUDES
//=========================================================================================================|
#include <Windows.h>
#include <objbase.h>
#include <ddraw.h>



//=========================================================================================================|
// DEFINES
//=========================================================================================================|
/**
 * initializes ddraw structures
 */
#define DDRAW_INIT_STRUCT(ddsd) { memset(&ddsd, 0, sizeof(ddsd)); ddsd.dwSize=sizeof(ddsd);}


/**
 * Forms a 32-bit color in argb 8.8.8.8 mode
 */
#define RGB32BIT(a,r,g,b)	((a << 24) | ( r << 16) | (g << 8) | b)

//=========================================================================================================|
// EXTERNS
//=========================================================================================================|
extern HINSTANCE main_instance;
extern HWND main_window_handle;

extern LPDIRECTDRAW7 lpdd;
extern LPDIRECTDRAWSURFACE7 lpddsprimary;			// a primary drawing surface
extern LPDIRECTDRAWSURFACE7 lpddsback;				// a backsurface for smooth animation
extern DDSURFACEDESC2 ddsd;							// surface description struct




//=========================================================================================================|
// TYPES
//=========================================================================================================|




//=========================================================================================================|
// PROTOTYPES
//=========================================================================================================|
int Init_DDraw(int width, int height, int bpp = 32, bool bfullscreen = true);
void Shutdown_DDraw();
int Lock_Surface(LPDIRECTDRAWSURFACE7 lpdds=lpddsprimary);
int Unlock_Surface(LPDIRECTDRAWSURFACE7 lpdds=lpddsprimary);

void Plot_Pixel(int x, int y, UINT* video, UINT lpitch, UINT color);


#endif
//=========================================================================================================|
//			THE END
//=========================================================================================================|