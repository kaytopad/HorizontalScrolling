#include "Player.h"
#include "Map.h"
#include "DxLib.h"


namespace
{
    //========================================
    // アニメーション方向
    //========================================

    constexpr int ANIM_DOWN = 0;
    constexpr int ANIM_LEFT = 1;
    constexpr int ANIM_RIGHT = 2;
    constexpr int ANIM_UP = 3;
}


//========================================
// コンストラクタ
//========================================

Player::Player()
{
    x = 0.0f;
    y = 0.0f;

    velocityX = 0.0f;
    velocityY = 0.0f;

    animTimer = 0.0f;

    animNowType = ANIM_DOWN;
    animNowPattern = 1;
    animNowIndex = 1;

    drawOffsetX = 0;
    drawOffsetY = 0;


    for (int i = 0; i < Config::ANIM_PATTERN_NUM *Config::ANIM_TYPE_NUM;i++)
    {
        playerImg[i] = -1;
    }
}


//========================================
// デストラクタ
//========================================

Player::~Player()
{
    for (int i = 0; i < Config::ANIM_PATTERN_NUM *Config::ANIM_TYPE_NUM;i++)
    {
        if (playerImg[i] != -1)
        {
            DeleteGraph(playerImg[i]);

            playerImg[i] = -1;
        }
    }
}


//========================================
// 初期化
//========================================

bool Player::Init()
{
    //========================================
    // 初期座標
    //========================================

    x = Config::PLAYER_START_X;
    y = Config::PLAYER_START_Y;


    velocityX = 0.0f;
    velocityY = 0.0f;

    animTimer = 0.0f;


    animNowType = ANIM_DOWN;
    animNowPattern = 1;

    animNowIndex = animNowPattern + animNowType * Config::ANIM_PATTERN_NUM;


    //========================================
    // 画像読み込み
    //========================================

    int result = LoadDivGraph(Config::PLAYER_IMAGE_PATH, Config::ANIM_PATTERN_NUM *Config::ANIM_TYPE_NUM,
        Config::ANIM_PATTERN_NUM, Config::ANIM_TYPE_NUM, Config::PLAYER_IMAGE_SIZE_X,Config::PLAYER_IMAGE_SIZE_Y,playerImg);


    if (result != 0)
    {
        return false;
    }


    //========================================
    // 描画位置補正
    //========================================

    drawOffsetX =(Config::PLAYER_HIT_SIZE_X - Config::PLAYER_IMAGE_SIZE_X) / 2;


    drawOffsetY = Config::PLAYER_HIT_SIZE_Y - Config::PLAYER_IMAGE_SIZE_Y;


    return true;
}


//========================================
// 更新
//========================================

void Player::Update(float deltaTime,const Map& map)
{
    //========================================
    // 速度をリセット
    //========================================

    velocityX = 0.0f;
    velocityY = 0.0f;


    bool isMove = false;


    //========================================
    // キー入力
    //========================================

    if (CheckHitKey(KEY_INPUT_UP))
    {
        velocityY =-Config::PLAYER_MOVE_SPEED;

        animNowType = ANIM_UP;

        isMove = true;
    }


    if (CheckHitKey(KEY_INPUT_DOWN))
    {
        velocityY = Config::PLAYER_MOVE_SPEED;

        animNowType = ANIM_DOWN;

        isMove = true;
    }


    if (CheckHitKey(KEY_INPUT_LEFT))
    {
        velocityX = -Config::PLAYER_MOVE_SPEED;

        animNowType = ANIM_LEFT;

        isMove = true;
    }


    if (CheckHitKey(KEY_INPUT_RIGHT))
    {
        velocityX = Config::PLAYER_MOVE_SPEED;

        animNowType = ANIM_RIGHT;

        isMove = true;
    }


    //========================================
    // 移動量
    //========================================

    float moveX = velocityX * deltaTime;

    float moveY = velocityY * deltaTime;


    //========================================
    // X方向移動
    //========================================

    x += moveX;


    map.ResolveHorizontalCollision(x,y,Config::PLAYER_HIT_SIZE_X,Config::PLAYER_HIT_SIZE_Y,moveX);


    //========================================
    // Y方向移動
    //========================================

    y += moveY;


    map.ResolveVerticalCollision(x,y,Config::PLAYER_HIT_SIZE_X, Config::PLAYER_HIT_SIZE_Y,moveY);


    //========================================
    // アニメーション
    //========================================

    if (isMove)
    {
        animTimer += deltaTime;


        if (animTimer >= 1.0f / Config::ANIMATION_FPS)
        {
            animTimer = 0.0f;

            animNowPattern++;

            animNowPattern %= Config::ANIM_PATTERN_NUM;
        }
    }
    else
    {
        // 静止時
        animNowPattern = 1;
    }


    //========================================
    // 描画する画像番号
    //========================================

    animNowIndex = animNowPattern + animNowType * Config::ANIM_PATTERN_NUM;
}


//========================================
// 描画
//========================================

void Player::Draw()
{
    DrawGraph(static_cast<int>(x) + drawOffsetX, static_cast<int>(y) + drawOffsetY, playerImg[animNowIndex], TRUE);


    //========================================
    // 当たり判定表示
    //========================================

    DrawBox( static_cast<int>(x), static_cast<int>(y), static_cast<int>( x + Config::PLAYER_HIT_SIZE_X -1),
        static_cast<int>(y + Config::PLAYER_HIT_SIZE_Y - 1),GetColor(255, 0, 0),FALSE);
}