#include "DxLib.h"
#include "Map.h"

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int)
{
    ChangeWindowMode(TRUE);

    if (DxLib_Init() == -1){ return -1; }

    SetDrawScreen(DX_SCREEN_BACK);

    Map map;

    if (!map.Init())
    { DxLib_End(); return -1;}

    float cameraX = 0.0f;
    float cameraY = 0.0f;

    while (ProcessMessage() == 0 &&CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {
        ClearDrawScreen();

        // マップを描画
        map.Draw(cameraX, cameraY);

        // 地形の確認例
        if (map.IsSolidAt(100.0f, 250.0f))
        {
            DrawString( 20, 20,"Solid!",GetColor(255, 0, 0));
        }

        ScreenFlip();
    }

    DxLib_End();

    return 0;
}