#include "DxLib.h"
#include "GameClearScene.h"
#include "../../BackGround/BackGround.h"
#include "../../Input/Input.h"
#include "../../Scene/SceneManager.h"
#include <stdio.h>

// ”wŒi‚ÌƒXƒNƒ[ƒ‹‘¬“x
#define BACK_GROUND_SPEED (-1.5)

// GameClear•¶š‰æ‘œ
int g_GameClearHandle = 0;

void InitGameClearScene()
{
	// ”wŒi‰Šú‰»
	InitBackGround();

	// •¶š‰æ‘œƒnƒ“ƒhƒ‹‰Šú‰»
	g_GameClearHandle = 0;
}

void LoadGameClearScene()
{
	// GameClear•¶š‰æ‘œ
	g_GameClearHandle = LoadGraph("Data/GameClear/GameClear.png");
}

void StartGameClearScene()
{
	
}

void StepGameClearScene()
{
	

	// ZƒL[‚Åƒ^ƒCƒgƒ‹‚É–ß‚é
	if (IsTriggerKey(KEY_SPACE))
	{
		ChangeScene(SCENE_TITLE);
	}
}

void UpdateGameClearScene()
{
	// ”wŒiXV
	UpdateBackGround();
}

void DrawGameClearScene()
{
	// ”wŒi•`‰æ
	DrawBackGround();

	// •¶š‰æ‘œ•`‰æ
	DrawGraph(560, 110, g_GameClearHandle, TRUE);

}

void FinGameClearScene()
{
	// ”wŒiI—¹
	FinBackGround();

	// •¶š‰æ‘œíœ
	DeleteGraph(g_GameClearHandle);

}
