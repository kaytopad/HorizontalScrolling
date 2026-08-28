#include <windows.h>

#include "DxLib.h"

#include "Config.h"
#include "Player.h"
#include "Map.h"


int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int)
{
    //====================================
    // DxLib
    //====================================

    ChangeWindowMode(TRUE);

    SetGraphMode(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT, Config::COLOR_BIT);

    if (DxLib_Init() == -1)
    {
        return -1;
    }


    //====================================
    // オブジェクト
    //====================================

    Player player;
    Map map;

    player.Init();
    map.Init();


    //====================================
    // 時間
    //====================================

    int previousTime = GetNowCount();


    //====================================
    // ゲームループ
    //====================================

    while (ProcessMessage() == 0 && !CheckHitKey(KEY_INPUT_ESCAPE))
    {
        int currentTime = GetNowCount();

        float deltaTime = (currentTime - previousTime) / 1000.0f;

        previousTime = currentTime;


        //================================
        // 更新
        //================================

        player.Update(deltaTime);


        // プレイヤー本体
        Collision playerCollision = player.GetCollision();

        if (map.CheckCollision(playerCollision))
        {
            player.FixCollision(playerCollision);
        }


        // 足元
        Collision foot = player.GetFootCollision();

        player.SetGround( map.CheckCollision(foot));


        // 頭
        Collision head = player.GetHeadCollision();

        player.SetHeadHit( map.CheckCollision(head));


        //================================
        // 描画
        //================================

        ClearDrawScreen();

        map.Draw();

        player.Draw();

        ScreenFlip();
    }


    //====================================
    // 終了
    //====================================

    player.Finalize();
    map.Finalize();

    DxLib_End();

    return 0;
}