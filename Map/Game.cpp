#include "Game.h"

#include <DxLib.h>


Game::Game()
{
    nowCount = 0;
    prevCount = 0;
}


Game::~Game()
{
    DxLib_End();
}


//========================================
// 初期化
//========================================

bool Game::Init()
{
    ChangeWindowMode(TRUE);


    SetGraphMode(Config::WINDOW_WIDTH,Config::WINDOW_HEIGHT,Config::COLOR_BIT);


    if (DxLib_Init() == -1)
    {
        return false;
    }


    //========================================
    // Player初期化
    //========================================

    if (!player.Init())
    {
        return false;
    }


    //========================================
    // Map初期化
    //========================================

    if (!map.Init())
    {
        return false;
    }


    //========================================
    // タイマー初期化
    //========================================

    nowCount = GetNowCount();
    prevCount = nowCount;


    return true;
}


//========================================
// ゲームループ
//========================================

void Game::Run()
{
    while (ProcessMessage() == 0 &&CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {
        //====================================
        // DeltaTime
        //====================================

        nowCount = GetNowCount();


        float deltaTime =(nowCount - prevCount)/ 1000.0f;


        //====================================
        // 更新
        //====================================

        Update(deltaTime);


        //====================================
        // 描画
        //====================================

        ClearDrawScreen();


        Draw();


        ScreenFlip();


        prevCount = nowCount;
    }
}


//========================================
// 更新
//========================================

void Game::Update(float deltaTime)
{
    player.Update(deltaTime,map);
}


//========================================
// 描画
//========================================

void Game::Draw()
{
    map.Draw();

    player.Draw();
}