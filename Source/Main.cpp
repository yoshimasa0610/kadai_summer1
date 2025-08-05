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
    // �E�B���h�E���[�h�E��ʃT�C�Y�ݒ�
    ChangeWindowMode(TRUE);
    SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_COLOR_DEPTH);
    if (DxLib_Init() == -1) return -1;
    SetDrawScreen(DX_SCREEN_BACK);

    // �e�평����
    InitBackGround();
    InitPlayer();
    LoadPlayer();
    StartPlayer();
    InitInput();
    InitBullet();
    LoadBullet();
    InitEnemy();         // �G�̏������i�o���^�C�}�[�܂ށj

    // ���C�����[�v
    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {
        // ��ʃN���A
        ClearDrawScreen();

        // ���͍X�V
        UpdateInput();

        // �w�i�E�v���C���[�X�V
        UpdateBackGround();
        StepPlayer();
        UpdatePlayer();

        // �G�̏o���E�ړ��E�e����
        UpdateEnemy();

        // �e�i�v���C���[���˂̊Ǘ��j
        StepBullet();
        UpdateBullet();

        // === �`�� ===
        DrawBackGround();
        DrawPlayer();
        DrawBullet();
        DrawEnemy();  // �G�ƓG�̒e���܂߂ĕ`��

        // ��ʔ��f
        ScreenFlip();
    }

    // �I������
    FinBackGround();
    FinPlayer();
    FinInput();
    FinBullet();
    DeleteEnemy();  // �G�E�G�e�̉��

    DxLib_End();
    return 0;
}