#include "DxLib.h"
#include "BackGround.h"

#define SCREEN_WIDTH    1600
#define SCREEN_HEIGHT   900
#define SCROLL_SPEED    200.0f   // px/�b

static int g_BackGroundHandle = -1;
static float g_BackGroundPosX = 0.0f;
static long long g_PrevTime = 0;

void InitBackGround()
{
    g_BackGroundHandle = LoadGraph("Data/BackGround/�w�i.png");
    g_BackGroundPosX = 0.0f;
    g_PrevTime = GetNowHiPerformanceCount();

    // ��������ON�Ńe�B�A�����O�h�~
    SetWaitVSyncFlag(TRUE);
}

void UpdateBackGround()
{
    // �o�ߎ��Ԃ�b�P�ʂŎ擾
    long long now = GetNowHiPerformanceCount();
    double deltaTime = (now - g_PrevTime) / 1000000.0;
    g_PrevTime = now;

    // �o�ߎ��Ԃɉ����Ĉړ�
    g_BackGroundPosX -= (float)(SCROLL_SPEED * deltaTime);

    // ���[�v����
    if (g_BackGroundPosX <= -SCREEN_WIDTH)
        g_BackGroundPosX += SCREEN_WIDTH;
    else if (g_BackGroundPosX >= SCREEN_WIDTH)
        g_BackGroundPosX -= SCREEN_WIDTH;
}

void DrawBackGround()
{
    float x = g_BackGroundPosX;

    // ���C��
    DrawGraphF(x, 0.0f, g_BackGroundHandle, TRUE);

    // �E�ׂ͔��]�`��
    DrawTurnGraphF(x + SCREEN_WIDTH, 0.0f, g_BackGroundHandle, TRUE);

    // ���ׂ����]�`��
    DrawTurnGraphF(x - SCREEN_WIDTH, 0.0f, g_BackGroundHandle, TRUE);
}

void FinBackGround()
{
    DeleteGraph(g_BackGroundHandle);
}
