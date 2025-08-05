#include "DxLib.h"
#include "BackGround/BackGround.h"
#include "Player/Player.h"
#include "Input/Input.h"
#include "GameSetting/GameSetting.h"
#include "Bullet/BulletManager.h"
#include "Enemy/Enemy.h"

#define SCREEN_WIDTH        (1600)
#define SCREEN_HEIGHT       (900)
#define SCREEN_COLOR_DEPTH  (32)

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) 
{
    // ウィンドウモード・画面サイズ設定
    ChangeWindowMode(TRUE);
    SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_COLOR_DEPTH);
    if (DxLib_Init() == -1) return -1;
    SetDrawScreen(DX_SCREEN_BACK);

    // 各種初期化
    InitBackGround();
    InitPlayer();
    LoadPlayer();
    StartPlayer();
    InitInput();
    InitBullet();
    LoadBullet();
    InitEnemy();         // 敵の初期化（出現タイマー含む）

    // メインループ
    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {
        // 画面クリア
        ClearDrawScreen();

        // 入力更新
        UpdateInput();

        // 背景・プレイヤー更新
        UpdateBackGround();
        StepPlayer();
        UpdatePlayer();

        // 敵の出現・移動・弾発射
        UpdateEnemy();

        // 弾（プレイヤー発射の管理）
        StepBullet();
        UpdateBullet();

        // === 描画 ===
        DrawBackGround();
        DrawPlayer();
        DrawBullet();
        DrawEnemy();  // 敵と敵の弾を含めて描画

        // 画面反映
        ScreenFlip();
    }

    // 終了処理
    FinBackGround();
    FinPlayer();
    FinInput();
    FinBullet();
    DeleteEnemy();  // 敵・敵弾の解放

    DxLib_End();
    return 0;
}