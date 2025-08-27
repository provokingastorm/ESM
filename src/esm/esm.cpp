// esm.cpp

#include "..\..\include\hge.h"
#include <cmath>

HGE* hge = 0;

int ScreenWidth = 1080;
int ScreenHeight = 720;

hgeQuad PlayableAreaQuad;
hgeQuad FloorQuad;
hgeQuad NetQuad;

void SetupWorldGraphics();

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

    hge->Gfx_RenderQuad(&PlayableAreaQuad);
    hge->Gfx_RenderQuad(&FloorQuad);
    hge->Gfx_RenderQuad(&NetQuad);

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

    SetupWorldGraphics();

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

void SetupWorldGraphics()
{
    const float PlayableAreaWidth = 750.0f;
    const float PlayableAreaHeight = 375.0f;
    const float HalfPlayableWidth = PlayableAreaWidth * 0.5f;
    const float HalfPlayableHeight = PlayableAreaHeight * 0.5f;
    const float HalfScreenWidth = ScreenWidth * 0.5f;
    const float HalfScreenHeight = ScreenHeight * 0.5f;

    // Setup the playable area quad
    PlayableAreaQuad.v[0].x = HalfScreenWidth - HalfPlayableWidth;
    PlayableAreaQuad.v[0].y = HalfScreenHeight - HalfPlayableHeight;
    PlayableAreaQuad.v[1].x = HalfScreenWidth + HalfPlayableWidth;
    PlayableAreaQuad.v[1].y = PlayableAreaQuad.v[0].y;
    PlayableAreaQuad.v[2].x = PlayableAreaQuad.v[1].x;
    PlayableAreaQuad.v[2].y = HalfScreenHeight + HalfPlayableHeight;
    PlayableAreaQuad.v[3].x = PlayableAreaQuad.v[0].x;
    PlayableAreaQuad.v[3].y = PlayableAreaQuad.v[2].y;

    // Setup the engine to render the playable area in blue
    for (int i = 0; i < 4; i++)
    {
        PlayableAreaQuad.v[i].col = 0xFF0000FF;
    }

    PlayableAreaQuad.blend = (hgeBlendMode)(BLEND_DEFAULT);
  
    // Setup the floor quad
    const float FloorTopY = PlayableAreaQuad.v[3].y - (PlayableAreaHeight * 0.2f);
    FloorQuad.v[0].x = PlayableAreaQuad.v[0].x;
    FloorQuad.v[0].y = FloorTopY;
    FloorQuad.v[1].x = PlayableAreaQuad.v[1].x;
    FloorQuad.v[1].y = FloorTopY;
    FloorQuad.v[2].x = PlayableAreaQuad.v[2].x;
    FloorQuad.v[2].y = PlayableAreaQuad.v[2].y;
    FloorQuad.v[3].x = PlayableAreaQuad.v[3].x;
    FloorQuad.v[3].y = PlayableAreaQuad.v[3].y;

    // Setup the engine to render the floor in gray
    for (int i = 0; i < 4; i++)
    {
        FloorQuad.v[i].col = 0xFF808080;
    }

    FloorQuad.blend = (hgeBlendMode)(BLEND_DEFAULT);

    // Setup the net
    const float NetWidth = 4.0f;
    const float NetHeight = 40.0f;
    float NetBottomLeftX = std::abs(ScreenWidth * 0.5);
    float NetBottomLeftY = FloorTopY + 10.0f; // Add pixels to push the net down visually from the floor to mimic the original
    float NetTopLeftY = NetBottomLeftY - NetHeight;

    NetQuad.v[0].x = NetBottomLeftX;
    NetQuad.v[0].y = NetTopLeftY;
    NetQuad.v[1].x = NetBottomLeftX + NetWidth;
    NetQuad.v[1].y = NetTopLeftY;
    NetQuad.v[2].x = NetBottomLeftX + NetWidth;
    NetQuad.v[2].y = NetBottomLeftY;
    NetQuad.v[3].x = NetBottomLeftX;
    NetQuad.v[3].y = NetBottomLeftY;

    for (int i = 0; i < 4; i++)
    {
        NetQuad.v[i].col = 0xFFFFFFFF;
    }

    NetQuad.blend = (hgeBlendMode)(BLEND_DEFAULT);
}

// EOF
