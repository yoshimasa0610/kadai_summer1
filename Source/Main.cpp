#include "DxLib.h"
#include "GameSetting/GameSetting.h"
#include "Input/Input.h"
#include "Scene/SceneManager.h"

// �^�[�Q�b�gFPS
const int TARGET_FPS = 120;
const double FRAME_TIME = 1000.0 / TARGET_FPS; // 1�t���[���̎��� (ms)

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
    // �E�B���h�E���[�hON
    ChangeWindowMode(TRUE);

    // ��ʉ𑜓x�̐ݒ�
    SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_COLOR_DEPTH);

    if (DxLib_Init() == -1) // �c�w���C�u��������������
    {
        return -1; // �G���[���N�����璼���ɏI��
    }

    // �E�B���h�E�T�C�Y�ݒ�
    SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);

    // ���ߐF�̐ݒ�
    SetTransColor(TRANS_COLOR_R, TRANS_COLOR_G, TRANS_COLOR_B);

    // �`���𗠉�ʂɂ���
    SetDrawScreen(DX_SCREEN_BACK);

    // ���̓V�X�e����������
    InitInput();

    // �����x�^�C�}�[�����l
    LONGLONG prevTime = GetNowHiPerformanceCount();

    // �Q�[���̃��C�����[�v
    while (ProcessMessage() >= 0)
    {
        // === StartFrame ===
        LONGLONG now = GetNowHiPerformanceCount();
        double delta = (now - prevTime) / 1000.0; // �o�ߎ��� (ms)
        if (delta < FRAME_TIME)
        {
            // �܂��t���[�����Ԃɖ����Ȃ��̂őҋ@
            WaitTimer((int)(FRAME_TIME - delta));
            continue;
        }
        prevTime = now;

        // === Update���� ===
        // ��ʂ��N���A
        ClearDrawScreen();

        // ���͂��X�V
        UpdateInput();

        // �V�[���Ǘ��̍X�V
        SceneManagerUpdate();

        // ���̓V�X�e���̕`��
        DrawInput();

        // �G�X�P�[�v�L�[�ŏI��
        if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

        // === EndFrame ===
        ScreenFlip();
    }

    // ���̓V�X�e���̏I��
    FinInput();

    DxLib_End(); // �c�w���C�u�����g�p�̏I������

    return 0; // �\�t�g�̏I��
}
