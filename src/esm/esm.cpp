// esm.cpp

#include "..\..\include\hge.h"

HGE* hge = 0;

int ScreenWidth = 1080;
int ScreenHeight = 720;

hgeQuad BackgroundQuad;

bool FrameFunc()
{
	// Get the time elapsed since last call of FrameFunc().
	// This will help us to synchronize on different
	// machines and video modes.
	float dt=hge->Timer_GetDelta();

	// Continue execution
	return false;
}

// This function will be called by HGE when
// the application window should be redrawn.
// Put your rendering code here.
bool RenderFunc()
{
	hge->Gfx_BeginScene();

	// Clear screen with black color
	hge->Gfx_Clear(0);

        hge->Gfx_RenderQuad(&BackgroundQuad);

	// End rendering and update the screen
	hge->Gfx_EndScene();

	// RenderFunc should always return false
	return false;
}


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// Get HGE interface
	hge = hgeCreate(HGE_VERSION);

	// Set up log file, frame function, render function and window title
	hge->System_SetState(HGE_LOGFILE, "esm.log");
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
	hge->System_SetState(HGE_TITLE, "ESM");

	// Set up video mode
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_SCREENWIDTH, ScreenWidth);
	hge->System_SetState(HGE_SCREENHEIGHT, ScreenHeight);
	hge->System_SetState(HGE_SCREENBPP, 32);

        // Setup the background quad
        BackgroundQuad.v[1].x = ScreenWidth;
        BackgroundQuad.v[2].x = ScreenWidth;
        BackgroundQuad.v[2].y = ScreenHeight;
        BackgroundQuad.v[3].y = ScreenHeight;

        for (int i = 0; i < 4; i++)
        {
          BackgroundQuad.v[i].col = 0xFF0000FF;
        }

        BackgroundQuad.blend = (hgeBlendMode)(BLEND_DEFAULT);

	if(hge->System_Initiate())
	{
		hge->System_Start();
	}
	else MessageBox(NULL, hge->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);

	// Clean up and shutdown
	hge->System_Shutdown();
	hge->Release();
	return 0;
}

// EOF
