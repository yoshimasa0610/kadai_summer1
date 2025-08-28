#include "DxLib.h"
#include "TitleScene.h"
#include "../SceneManager.h"
#include "../../Input/Input.h"
#include "../../BackGround/BackGround.h"


// �摜�n���h��
int g_BGHandle = 0;
int g_TitleHandle = 0;

void InitTitleScene()
{
	g_BGHandle = 0;
	g_TitleHandle = 0;
	

	// �w�i������
	InitBackGround();
}

void LoadTitleScene()
{

	// �e�摜�����[�h
	g_BGHandle = LoadGraph("Data/Title/TitleBG.png");
	g_TitleHandle = LoadGraph("Data/Title/TitleText.png");

}

void StartTitleScene()
{
	
}


void StepTitleScene()
{

	// Z�L�[�������ꂽ��v���C�V�[����
	if (IsTriggerKey(KEY_SPACE))
	{
		ChangeScene(SCENE_PLAY);
	}

}

void UpdateTitleScene()
{

}

void DrawTitleScene()
{
	// �w�i�`��
	DrawBackGround();

	// �w�i��`�悵�����ꍇ
	if (g_BGHandle != 0) DrawGraph(0, 0, g_BGHandle, TRUE);

	// �^�C�g���e�L�X�g
	if (g_TitleHandle != 0) DrawGraph(400, 200, g_TitleHandle, TRUE);
	
}

void FinTitleScene()
{
	// �w�i�I��
	FinBackGround();

	// �e�摜���폜
	DeleteGraph(g_TitleHandle);

}
