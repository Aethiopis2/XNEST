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
#define WIN32_LEAN_AND_MEAN
#define INITGUID


//=========================================================================================================|
// INCLUDES
//=========================================================================================================|
#include "OldX.h"


//=========================================================================================================|
// GLOBALS
//=========================================================================================================|
LPDIRECTDRAW7 lpdd = nullptr;							// main graphics hardware abstraction
LPDIRECTDRAWSURFACE7 lpddsprimary = nullptr;			// a primary drawing surface
LPDIRECTDRAWSURFACE7 lpddsback = nullptr;				// a backsurface for smooth animation

DDSURFACEDESC2 ddsd;		// surface description struct


//=========================================================================================================|
// FUNCTIONS
//=========================================================================================================|
/**
 * Initalizes a directdraw7 surface on 32 bit pixel (default); with the specified dimensions.
 */
int Init_DDraw(int width, int height, int bpp, bool bfullscreen)
{
	// Initalize COM, we're gonna do it the COM way, DDraw is depreciated...
	if (FAILED(CoInitialize(NULL)))
		return -1;	// the linux system call error that has grown in me...

	if (FAILED(CoCreateInstance(CLSID_DirectDraw, NULL, CLSCTX_ALL, IID_IDirectDraw7, (void **)&lpdd)))
		return -1;

	if (FAILED(lpdd->Initialize(NULL)))
		return -1;

	// kill COM, we wont be needing it
	CoUninitialize();

	if (!bfullscreen)
	{
		// we're doin it Windowed style ...
		if (FAILED(lpdd->SetCooperativeLevel(main_window_handle, DDSCL_NORMAL)))
			return -1;
	} // end if windows ddraw
	else
	{
		// get me the full screen
		if (FAILED(lpdd->SetCooperativeLevel(main_window_handle, DDSCL_ALLOWMODEX | DDSCL_ALLOWREBOOT |
			DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN)))
			return -1;
	} // end else

	if (FAILED(lpdd->SetDisplayMode(width, height, bpp, 0, 0)))
		return -1;

	DDRAW_INIT_STRUCT(ddsd);
	ddsd.dwFlags = DDSD_CAPS;
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

	if (FAILED(lpdd->CreateSurface(&ddsd, &lpddsprimary, NULL)))
		return -1;

	return 0;
} // end Init_DDraw


//=========================================================================================================|
/**
 * Terminates resources; house cleaning
 */
void Shutdown_DDraw()
{
	if (lpddsback)
	{
		lpddsback->Release();
		lpddsback = NULL;
	} // end if lppdsback

	if (lpddsprimary)
	{
		lpddsprimary->Release();
		lpddsprimary = NULL;
	} // end if lpddsprimary

	if (lpdd)
	{
		lpdd->Release();
		lpdd = NULL;		// double-tap
	} // end if lpdd
} // end Shutdown_DDraw


//=========================================================================================================|
/**
 * draw's a pixel at x,y using the color provided at the provided video surface (primary,back,offscreen,etc)
 */
void Plot_Pixel(int x, int y, UINT* video, UINT lpitch, UINT color)
{
	video[x + y * lpitch] = color;
} // end Plot_Pixel


//=========================================================================================================|
/**
 * lock's a surface for drawing and pixel plotting; i.e. DDSURFACEDESC2 members lpitch and lpSurface
 *	become valid
 */
int Lock_Surface(LPDIRECTDRAWSURFACE7 lpdds)
{
	DDRAW_INIT_STRUCT(ddsd);

	if (FAILED(lpdds->Lock(NULL, &ddsd,
		DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT, NULL)))
		return -1;

	return 0;
} // end Lock Primary


//=========================================================================================================|
/**
 * unlocks a locked surface.
 */
int Unlock_Surface(LPDIRECTDRAWSURFACE7 lpdds)
{
	if (FAILED(lpdds->Unlock(NULL)))
		return -1;

	return 0;
} // end Unlock


//=========================================================================================================|
//			THE END
//=========================================================================================================|