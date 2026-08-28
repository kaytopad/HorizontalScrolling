#pragma once

namespace Config
{
    // ウィンドウ
    constexpr int WINDOW_WIDTH = 1440;
    constexpr int WINDOW_HEIGHT = 900;
    constexpr int COLOR_BIT = 16;

    // マップ
    constexpr int MAP_CHIP_SIZE = 64;
    constexpr int MAP_X_NUM = 16;
    constexpr int MAP_Y_NUM = 12;
    constexpr int MAP_IMG_X_NUM = 2;
    constexpr int MAP_IMG_Y_NUM = 1;

    // プレイヤー画像
    constexpr int PLAYER_IMAGE_WIDTH = 64;
    constexpr int PLAYER_IMAGE_HEIGHT = 96;
    constexpr int PLAYER_ANIM_PATTERN_NUM = 3;
    constexpr int PLAYER_ANIM_TYPE_NUM = 4;
    constexpr float PLAYER_ANIMATION_FPS = 6.0f;

    // プレイヤー
    constexpr float PLAYER_START_X = 100.0f;
    constexpr float PLAYER_START_Y = 100.0f;

    constexpr float PLAYER_WIDTH = 40.0f;
    constexpr float PLAYER_HEIGHT = 60.0f;

    constexpr float PLAYER_MAX_SPEED = 300.0f;
    constexpr float PLAYER_ACCEL = 150.0f;
    constexpr float PLAYER_FRICTION = 0.98f;

    // ジャンプ
    constexpr float JUMP_POWER = 550.0f;
    constexpr float GRAVITY = 1500.0f;
    constexpr float MAX_FALL_SPEED = 800.0f;

    // 足・頭の判定
    constexpr float COLLIDER_OFFSET = 10.0f;
}