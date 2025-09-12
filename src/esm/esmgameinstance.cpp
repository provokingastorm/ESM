#include "esmgameinstance.h"
#include "esmrenderables.h"
#include "curlyengine.h"
#include "sharedrenderables.h"
#include <cmath>

ESMVolleyballGameInstance::ESMVolleyballGameInstance()
    : bIsRunning(false)
{
    FloorQuad = {};
    NetQuad = {};
}

ESMVolleyballGameInstance::~ESMVolleyballGameInstance()
{
    if (FloorRenderable != NULL)
    {
        delete FloorRenderable;
        FloorRenderable = NULL;
    }

    if (NetRenderable != NULL)
    {
        delete NetRenderable;
        NetRenderable = NULL;
    }
}

void ESMVolleyballGameInstance::Initialize(const hgeQuad& PlayableAreaQuad)
{
    const int ScreenWidth = CurlyEngine::Instance().GetScreenWidth();
    const int ScreenHeight = CurlyEngine::Instance().GetScreenHeight();
    const float PlayableAreaWidth = PlayableAreaQuad.v[1].x - PlayableAreaQuad.v[0].x;
    const float PlayableAreaHeight = PlayableAreaQuad.v[3].y - PlayableAreaQuad.v[0].y;

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

    FloorRenderable = new RenderedQuad();
    FloorRenderable->SetContent(FloorQuad);

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

    NetRenderable = new RenderedQuad();
    NetRenderable->SetContent(NetQuad);
}

void ESMVolleyballGameInstance::StartGame()
{
    if (!IsRunning())
    {
        bIsRunning = true;
    }
}

void ESMVolleyballGameInstance::StopGame()
{
    if (IsRunning())
    {
        bIsRunning = false;
    }
}

void ESMVolleyballGameInstance::Tick(float DeltaTime)
{
    if (IsRunning())
    {
        if (FloorRenderable != NULL)
        {
            CurlyEngine::Instance().AddToRenderQueue(*FloorRenderable);
        }

        if (NetRenderable != NULL)
        {
            CurlyEngine::Instance().AddToRenderQueue(*NetRenderable);
        }
    }
}

bool ESMVolleyballGameInstance::IsRunning()
{
    return bIsRunning;
}

// EOF
