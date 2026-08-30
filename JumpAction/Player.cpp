#include "Player.h"
#include "Config.h"
#include "DxLib.h"


void Player::Init()
{
    x = Config::PLAYER_START_X;
    y = Config::PLAYER_START_Y;

    velocityX = 0.0f;
    velocityY = 0.0f;

    jumpFlag = false;
    groundFlag = false;
    headHitFlag = false;

    previousJump = false;

    animationTimer = 0.0f;
    animationType = 0;
    animationPattern = 0;


    // 当たり判定
    collision.Init(Config::PLAYER_WIDTH,Config::PLAYER_HEIGHT);

    footCollision.Init(Config::PLAYER_WIDTH - Config::COLLIDER_OFFSET,1.0f);

    headCollision.Init(Config::PLAYER_WIDTH - Config::COLLIDER_OFFSET,1.0f);


    // プレイヤー画像読み込み
    LoadDivGraph( "img/chara.png", Config::PLAYER_ANIM_PATTERN_NUM * Config::PLAYER_ANIM_TYPE_NUM,
        Config::PLAYER_ANIM_PATTERN_NUM, Config::PLAYER_ANIM_TYPE_NUM,
        Config::PLAYER_IMAGE_WIDTH, Config::PLAYER_IMAGE_HEIGHT, playerImg);
}


void Player::Update(float deltaTime)
{
    // 接地している
    if (groundFlag)
    {
        jumpFlag = false;
        velocityY = 0.0f;
    }
    else
    {
        jumpFlag = true;
    }


    Move(deltaTime);


    // コライダー位置更新
    collision.SetPosition(x, y);

    footCollision.SetPosition( x + Config::COLLIDER_OFFSET / 2.0f,y + Config::PLAYER_HEIGHT );

    headCollision.SetPosition( x + Config::COLLIDER_OFFSET / 2.0f, y - 1.0f);


    // アニメーション
    if (velocityX != 0.0f)
    {
        animationTimer += deltaTime;

        if (animationTimer > 1.0f / Config::PLAYER_ANIMATION_FPS)
        {
            animationTimer = 0.0f;

            animationPattern++;

            animationPattern %= Config::PLAYER_ANIM_PATTERN_NUM;
        }
    }
    else
    {
        animationPattern = 1;
    }
}


void Player::Move(float deltaTime)
{
    //====================================
    // 左右移動
    //====================================

    if (CheckHitKey(KEY_INPUT_LEFT))
    {
        velocityX -=
            Config::PLAYER_ACCEL * deltaTime;

        animationType = 1;
    }

    if (CheckHitKey(KEY_INPUT_RIGHT))
    {
        velocityX +=
            Config::PLAYER_ACCEL * deltaTime;

        animationType = 2;
    }


    //====================================
    // 速度制限
    //====================================

    if (velocityX >
        Config::PLAYER_MAX_SPEED)
    {
        velocityX =
            Config::PLAYER_MAX_SPEED;
    }

    if (velocityX <
        -Config::PLAYER_MAX_SPEED)
    {
        velocityX =
            -Config::PLAYER_MAX_SPEED;
    }


    //====================================
    // 摩擦
    //====================================

    if (!CheckHitKey(KEY_INPUT_LEFT) &&!CheckHitKey(KEY_INPUT_RIGHT))
    {
        velocityX *=
            Config::PLAYER_FRICTION;
    }


    //====================================
    // ジャンプ
    //====================================

    bool jumpButton =
        CheckHitKey(KEY_INPUT_SPACE);


    if (jumpButton &&
        !previousJump &&
        groundFlag)
    {
        velocityY =
            -Config::JUMP_POWER;

        jumpFlag = true;
        groundFlag = false;
    }


    previousJump = jumpButton;


    //====================================
    // 重力
    //====================================

    if (jumpFlag)
    {
        velocityY += Config::GRAVITY * deltaTime;
    }


    //====================================
    // 頭をぶつけた
    //====================================

    if (headHitFlag && velocityY < 0.0f)
    {
        velocityY = 0.0f;
    }


    //====================================
    // 落下速度制限
    //====================================

    if (velocityY > Config::MAX_FALL_SPEED)
    {
        velocityY = Config::MAX_FALL_SPEED;
    }


    //====================================
    // 座標更新
    //====================================

    x += velocityX * deltaTime;
    y += velocityY * deltaTime;
}


void Player::Draw()
{
    int index = animationPattern +  animationType * Config::PLAYER_ANIM_PATTERN_NUM;

    // 当たり判定を基準に画像を配置
    int drawX = static_cast<int>(x) -(Config::PLAYER_IMAGE_WIDTH - Config::PLAYER_WIDTH) / 2;

    int drawY = static_cast<int>(y) + Config::PLAYER_HEIGHT - Config::PLAYER_IMAGE_HEIGHT;


    DrawGraph( drawX, drawY, playerImg[index], TRUE );


    // 当たり判定表示
    collision.Draw();
}


void Player::Finalize()
{
    for (int i = 0; i < Config::PLAYER_ANIM_PATTERN_NUM * Config::PLAYER_ANIM_TYPE_NUM; i++)
    {
        DeleteGraph(playerImg[i]);
    }
}

//動いてどこが当たっているかを判定
Collision Player::GetCollision() const
{
    return collision;
}


Collision Player::GetFootCollision() const
{
    return footCollision;
}


Collision Player::GetHeadCollision() const
{
    return headCollision;
}


void Player::FixCollision( const Collision& newCollision)
{
    x = newCollision.GetLeft();
    y = newCollision.GetTop();

    collision = newCollision;
}


void Player::SetGround(bool ground)
{
    groundFlag = ground;
}


void Player::SetHeadHit(bool hit)
{
    headHitFlag = hit;
}