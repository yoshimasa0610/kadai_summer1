#include "DxLib.h"
#include "GameSetting/GameSetting.h"
#include "Input/Input.h"
#include "Scene/SceneManager.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	// �E�B���h�E���[�hON
	ChangeWindowMode(TRUE);

	// ��ʉ𑜓x�̐ݒ�
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_COLOR_DEPTH);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	// �E�B���h�E�T�C�Y�ݒ�
	SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	// ���ߐF�̐ݒ�
	SetTransColor(TRANS_COLOR_R, TRANS_COLOR_G, TRANS_COLOR_B);

	// �`���𗠉�ʂɂ���
	SetDrawScreen(DX_SCREEN_BACK);

	// ���̓V�X�e����������
	InitInput();

	float m_Time = 0.0f;
	// �Q�[���̃��C�����[�v
	while (ProcessMessage() >= 0)
	{
		//StartFrame
		{
			m_Time = GetNowCount();
		}

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
		{

		}

		//WaitFrame()
		{
			int before = m_Time;
			int after = GetNowCount();
			int interval = (int)((1000 / 1000) - (after - before));
			if (interval > 0) { WaitTimer(interval); }
		}

		// ��ʃt���b�v
		ScreenFlip();
	}

	// ���̓V�X�e���̏I��
	FinInput();


	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}
