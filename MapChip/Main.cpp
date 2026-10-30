#include "DxLib.h"

#include "Config.h"
#include "Map.h"

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow)
{
    ChangeWindowMode(TRUE);

    if (DxLib_Init() == -1)
    {
        return -1;
    }

    SetDrawScreen(DX_SCREEN_BACK);

    // マップを管理するオブジェクト
    Map map;

    if (!map.Init())
    {
        // DxLib_End()より前に、読み込み済みの画像を解放する
        map.Finalize();
        DxLib_End();
        return -1;
    }

    // ゲームループ
    while (ProcessMessage() == 0)
    {
        if (CheckHitKey(KEY_INPUT_ESCAPE))
        {
            break;
        }

        ClearDrawScreen();

        // マップの描画はMapクラスに任せる
        map.Draw();

        ScreenFlip();
    }

    // DxLibを終了する前に、Mapが使用した画像を解放する
    map.Finalize();
    DxLib_End();

    return 0;
}
