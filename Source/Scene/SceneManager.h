#pragma once

// �V�[���̎��
enum Scene
{
	SCENE_TITLE,
	SCENE_PLAY,
	SCENE_GAME_CLEAR,
	SCENE_GAME_OVER,
};

// �V�[���̏��
enum SceneState
{
	SCENE_STATE_INIT,
	SCENE_STATE_LOAD,
	SCENE_STATE_START,
	SCENE_STATE_LOOP,
	SCENE_STATE_FIN,
};

// �֐��̃v���g�^�C�v�錾

// �V�[���Ǘ��̍X�V����
void SceneManagerUpdate();

// �e�V�[���̏�ԕʏ���
void InitScene();
void LoadScene();
void StartScene();
void StepScene();
void UpdateScene();
void DrawScene();
void FinScene();

// �V�[���؂�ւ�
void ChangeScene(Scene scene);
