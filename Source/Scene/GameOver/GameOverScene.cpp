#include "DxLib.h"
#include "GameOverScene.h"
#include "../../BackGround/BackGround.h"
#include "../../Input/Input.h"
#include "../../Scene/SceneManager.h"

// �w�i�̃X�N���[�����x
#define BACK_GROUND_SPEED (-5.0f)

// �����J�ڂ܂ł̑ҋ@����
#define WAIT_TIMER		(300)

// �ҋ@���ԃ^�C�}�[
int g_WaitTimer = 0;
// GameOver�����摜�n���h��
int g_GameOverHandle = 0;

void InitGameOverScene()
{
	// �w�i������
	InitBackGround();

	// �^�C�}�[������
	g_WaitTimer = 0;
}

void LoadGameOverScene()
{
	// GameOver�����摜
	g_GameOverHandle = LoadGraph("Data/GameOver/GameOver.png");
}

void StartGameOverScene()
{
	// �ҋ@�^�C�}�[���Z�b�g
	g_WaitTimer = WAIT_TIMER;
	
}

void StepGameOverScene()
{
	
	// �^�C�}�[���J�E���g�_�E��
	g_WaitTimer--;
}

void UpdateGameOverScene()
{
	// �w�i�X�V
	UpdateBackGround();

	// �^�C�}�[��0��������Z�L�[�Ń^�C�g���ɖ߂�
	if (g_WaitTimer <= 0 || IsTriggerKey(KEY_SPACE))
	{
		ChangeScene(SCENE_TITLE);
	}
}

void DrawGameOverScene()
{
	// �w�i�`��
	DrawBackGround();

	// GameOver�����摜�`��
	DrawGraph(500, 350, g_GameOverHandle, TRUE);
}

void FinGameOverScene()
{
	// �w�i�I��
	FinBackGround();

	// �����摜�폜
	DeleteGraph(g_GameOverHandle);

}
