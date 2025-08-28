#include "DxLib.h"
#include "GameClearScene.h"
#include "../../BackGround/BackGround.h"
#include "../../Input/Input.h"
#include "../../Scene/SceneManager.h"
#include <stdio.h>

// �w�i�̃X�N���[�����x
#define BACK_GROUND_SPEED (-1.5)

// GameClear�����摜
int g_GameClearHandle = 0;

void InitGameClearScene()
{
	// �w�i������
	InitBackGround();

	// �����摜�n���h��������
	g_GameClearHandle = 0;
}

void LoadGameClearScene()
{
	// GameClear�����摜
	g_GameClearHandle = LoadGraph("Data/GameClear/GameClear.png");
}

void StartGameClearScene()
{
	
}

void StepGameClearScene()
{
	

	// Z�L�[�Ń^�C�g���ɖ߂�
	if (IsTriggerKey(KEY_SPACE))
	{
		ChangeScene(SCENE_TITLE);
	}
}

void UpdateGameClearScene()
{
	// �w�i�X�V
	UpdateBackGround();
}

void DrawGameClearScene()
{
	// �w�i�`��
	DrawBackGround();

	// �����摜�`��
	DrawGraph(560, 110, g_GameClearHandle, TRUE);

}

void FinGameClearScene()
{
	// �w�i�I��
	FinBackGround();

	// �����摜�폜
	DeleteGraph(g_GameClearHandle);

}
