#include "SceneManager.h"
#include "Title/TitleScene.h"
#include "Play/PlayScene.h"
#include "GameClear/GameClearScene.h"
#include "GameOver/GameOverScene.h"

// �ŏ��ɊJ�����V�[���������l�ɂ���
Scene g_NowScene = SCENE_TITLE;

// ���ɑJ�ڂ���V�[��
Scene g_NextScene = SCENE_TITLE;

// �V�[���̏��
SceneState g_SceneState = SCENE_STATE_INIT;

// ���[�v���I�����邩
bool g_IsLoopEnd = false;

void SceneManagerUpdate()
{
	// �V�[���̏�Ԃ��ƂɊe�V�[���̏������Ă�
	switch (g_SceneState)
	{
	case SCENE_STATE_INIT:	// ������
		InitScene();

		// ���[�h��
		g_SceneState = SCENE_STATE_LOAD;
		break;

	case SCENE_STATE_LOAD:	// ���[�h
		LoadScene();

		// ���[�v�I���t���O��܂��Ă���
		g_IsLoopEnd = false;

		// �J�n��
		g_SceneState = SCENE_STATE_START;
		break;

	case SCENE_STATE_START:	// �J�n�i���[�v�J�n�O��1�񂾂��j
		// �J�n����
		StartScene();

		// �J�n��
		g_SceneState = SCENE_STATE_LOOP;
		break;

	case SCENE_STATE_LOOP:	// ���[�v�i�X�e�b�v���X�V���`��j
		StepScene();
		UpdateScene();
		DrawScene();

		// ���[�v�I���t���O����������I��������
		if (g_IsLoopEnd)
		{
			g_SceneState = SCENE_STATE_FIN;
		}
		break;

	case SCENE_STATE_FIN:	// �I��
		FinScene();

		// ���̃V�[���ɐ؂�ւ���
		g_NowScene = g_NextScene;
		// �V�[���͏���������
		g_SceneState = SCENE_STATE_INIT;
		break;
	}
}

void InitScene()
{
	// �J���Ă���V�[���̏������������Ă�
	switch (g_NowScene)
	{
	case SCENE_TITLE:	// �^�C�g��
		InitTitleScene();
		break;

	case SCENE_PLAY:	// �v���C
		InitPlayScene();
		break;

	case SCENE_GAME_CLEAR:	// �Q�[���N���A
		InitGameClearScene();
		break;

	case SCENE_GAME_OVER:	// �Q�[���I�[�o�[
		InitGameOverScene();
		break;
	}
}

void LoadScene()
{
	// �J���Ă���V�[���̃��[�h�������Ă�
	switch (g_NowScene)
	{
	case SCENE_TITLE:	// �^�C�g��
		LoadTitleScene();
		break;

	case SCENE_PLAY:	// �v���C
		LoadPlayScene();
		break;

	case SCENE_GAME_CLEAR:	// �Q�[���N���A
		LoadGameClearScene();
		break;

	case SCENE_GAME_OVER:	// �Q�[���I�[�o�[
		LoadGameOverScene();
		break;
	}
}

void StartScene()
{
	// �J���Ă���V�[���̃��[�h�������Ă�
	switch (g_NowScene)
	{
	case SCENE_TITLE:	// �^�C�g��
		StartTitleScene();
		break;

	case SCENE_PLAY:	// �v���C
		StartPlayScene();
		break;

	case SCENE_GAME_CLEAR:	// �Q�[���N���A
		StartGameClearScene();
		break;

	case SCENE_GAME_OVER:	// �Q�[���I�[�o�[
		StartGameOverScene();
		break;
	}
}

void StepScene()
{
	// �J���Ă���V�[���̃X�e�b�v�������Ă�
	switch (g_NowScene)
	{
	case SCENE_TITLE:	// �^�C�g��
		StepTitleScene();
		break;

	case SCENE_PLAY:	// �v���C
		StepPlayScene();
		break;

	case SCENE_GAME_CLEAR:	// �Q�[���N���A
		StepGameClearScene();
		break;

	case SCENE_GAME_OVER:	// �Q�[���I�[�o�[
		StepGameOverScene();
		break;
	}
}

void UpdateScene()
{
	// �J���Ă���V�[���̍X�V�������Ă�
	switch (g_NowScene)
	{
	case SCENE_TITLE:	// �^�C�g��
		UpdateTitleScene();
		break;

	case SCENE_PLAY:	// �v���C
		UpdatePlayScene();
		break;

	case SCENE_GAME_CLEAR:	// �Q�[���N���A
		UpdateGameClearScene();
		break;

	case SCENE_GAME_OVER:	// �Q�[���I�[�o�[
		UpdateGameOverScene();
		break;
	}
}

void DrawScene()
{
	// �J���Ă���V�[���̕`�揈�����Ă�
	switch (g_NowScene)
	{
	case SCENE_TITLE:	// �^�C�g��
		DrawTitleScene();
		break;

	case SCENE_PLAY:	// �v���C
		DrawPlayScene();
		break;

	case SCENE_GAME_CLEAR:	// �Q�[���N���A
		DrawGameClearScene();
		break;

	case SCENE_GAME_OVER:	// �Q�[���I�[�o�[
		DrawGameOverScene();
		break;
	}
}

void FinScene()
{
	// �J���Ă���V�[���̏I���������Ă�
	switch (g_NowScene)
	{
	case SCENE_TITLE:	// �^�C�g��
		FinTitleScene();
		break;

	case SCENE_PLAY:	// �v���C
		FinPlayScene();
		break;

	case SCENE_GAME_CLEAR:	// �Q�[���N���A
		FinGameClearScene();
		break;

	case SCENE_GAME_OVER:	// �Q�[���I�[�o�[
		FinGameOverScene();
		break;
	}
}

void ChangeScene(Scene scene)
{
	// ���ɑJ�ڂ���V�[����ݒ�
	g_NextScene = scene;

	// �V�[���̃��[�v���I��������
	g_IsLoopEnd = true;
}
