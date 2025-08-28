#include "DxLib.h"
#include "TitleScene.h"
#include "../SceneManager.h"
#include "../../Input/Input.h"
#include "../../BackGround/BackGround.h"


// 画像ハンドル
int g_BGHandle = 0;
int g_TitleHandle = 0;

void InitTitleScene()
{
	g_BGHandle = 0;
	g_TitleHandle = 0;
	

	// 背景初期化
	InitBackGround();
}

void LoadTitleScene()
{

	// 各画像をロード
	g_BGHandle = LoadGraph("Data/Title/TitleBG.png");
	g_TitleHandle = LoadGraph("Data/Title/TitleText.png");

}

void StartTitleScene()
{
	
}


void StepTitleScene()
{

	// Zキーが押されたらプレイシーンへ
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
	// 背景描画
	DrawBackGround();

	// 背景を描画したい場合
	if (g_BGHandle != 0) DrawGraph(0, 0, g_BGHandle, TRUE);

	// タイトルテキスト
	if (g_TitleHandle != 0) DrawGraph(400, 200, g_TitleHandle, TRUE);
	
}

void FinTitleScene()
{
	// 背景終了
	FinBackGround();

	// 各画像を削除
	DeleteGraph(g_TitleHandle);

}
