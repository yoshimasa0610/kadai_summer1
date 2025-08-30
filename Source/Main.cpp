#include "DxLib.h"
#include "GameSetting/GameSetting.h"
#include "Input/Input.h"
#include "Scene/SceneManager.h"

// ターゲットFPS
const int TARGET_FPS = 120;
const double FRAME_TIME = 1000.0 / TARGET_FPS; // 1フレームの時間 (ms)

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
    // ウィンドウモードON
    ChangeWindowMode(TRUE);

    // 画面解像度の設定
    SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_COLOR_DEPTH);

    if (DxLib_Init() == -1) // ＤＸライブラリ初期化処理
    {
        return -1; // エラーが起きたら直ちに終了
    }

    // ウィンドウサイズ設定
    SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);

    // 透過色の設定
    SetTransColor(TRANS_COLOR_R, TRANS_COLOR_G, TRANS_COLOR_B);

    // 描画先を裏画面にする
    SetDrawScreen(DX_SCREEN_BACK);

    // 入力システムを初期化
    InitInput();

    // 高精度タイマー初期値
    LONGLONG prevTime = GetNowHiPerformanceCount();

    // ゲームのメインループ
    while (ProcessMessage() >= 0)
    {
        // === StartFrame ===
        LONGLONG now = GetNowHiPerformanceCount();
        double delta = (now - prevTime) / 1000.0; // 経過時間 (ms)
        if (delta < FRAME_TIME)
        {
            // まだフレーム時間に満たないので待機
            WaitTimer((int)(FRAME_TIME - delta));
            continue;
        }
        prevTime = now;

        // === Update処理 ===
        // 画面をクリア
        ClearDrawScreen();

        // 入力を更新
        UpdateInput();

        // シーン管理の更新
        SceneManagerUpdate();

        // 入力システムの描画
        DrawInput();

        // エスケープキーで終了
        if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

        // === EndFrame ===
        ScreenFlip();
    }

    // 入力システムの終了
    FinInput();

    DxLib_End(); // ＤＸライブラリ使用の終了処理

    return 0; // ソフトの終了
}
