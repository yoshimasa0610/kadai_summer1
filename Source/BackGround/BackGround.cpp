#include "DxLib.h"
#include "BackGround.h"

#define SCREEN_WIDTH    1600
#define SCREEN_HEIGHT   900
#define SCROLL_SPEED    200.0f   // px/秒

static int g_BackGroundHandle = -1;
static float g_BackGroundPosX = 0.0f;
static long long g_PrevTime = 0;

void InitBackGround()
{
    g_BackGroundHandle = LoadGraph("Data/BackGround/背景.png");
    g_BackGroundPosX = 0.0f;
    g_PrevTime = GetNowHiPerformanceCount();

    // 垂直同期ONでティアリング防止
    SetWaitVSyncFlag(TRUE);
}

void UpdateBackGround()
{
    // 経過時間を秒単位で取得
    long long now = GetNowHiPerformanceCount();
    double deltaTime = (now - g_PrevTime) / 1000000.0;
    g_PrevTime = now;

    // 経過時間に応じて移動
    g_BackGroundPosX -= (float)(SCROLL_SPEED * deltaTime);

    // ループ処理
    if (g_BackGroundPosX <= -SCREEN_WIDTH)
        g_BackGroundPosX += SCREEN_WIDTH;
    else if (g_BackGroundPosX >= SCREEN_WIDTH)
        g_BackGroundPosX -= SCREEN_WIDTH;
}

void DrawBackGround()
{
    float x = g_BackGroundPosX;

    // メイン
    DrawGraphF(x, 0.0f, g_BackGroundHandle, TRUE);

    // 右隣は反転描画
    DrawTurnGraphF(x + SCREEN_WIDTH, 0.0f, g_BackGroundHandle, TRUE);

    // 左隣も反転描画
    DrawTurnGraphF(x - SCREEN_WIDTH, 0.0f, g_BackGroundHandle, TRUE);
}

void FinBackGround()
{
    DeleteGraph(g_BackGroundHandle);
}
