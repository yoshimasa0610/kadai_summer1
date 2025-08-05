#include "DxLib.h"
#include "BackGround.h"

#define SCREEN_WIDTH    1600
#define SCREEN_HEIGHT   900
#define SCROLL_SPEED    2

static int g_BackGroundHandle = -1;
static float g_BackGroundPosX = 0.0f;

void InitBackGround()
{
    g_BackGroundHandle = LoadGraph("Data/BackGround/�w�i.png");
    g_BackGroundPosX = 0.0f;
}

void UpdateBackGround()
{
    g_BackGroundPosX -= SCROLL_SPEED;

    if (g_BackGroundPosX <= -SCREEN_WIDTH)
    {
        g_BackGroundPosX += SCREEN_WIDTH;
    }
}

void DrawBackGround()
{
    // ���C��
    DrawGraph((int)g_BackGroundPosX, 0, g_BackGroundHandle, TRUE);

    // �E�ɑ����w�i��`��i�Ȃ��ځj
    DrawGraph((int)g_BackGroundPosX + SCREEN_WIDTH, 0, g_BackGroundHandle, TRUE);
}

void FinBackGround()
{
    DeleteGraph(g_BackGroundHandle);
}