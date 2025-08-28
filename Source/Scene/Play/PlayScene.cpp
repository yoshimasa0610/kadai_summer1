#include "DxLib.h"
#include "../SceneManager.h"
#include "../../BackGround/BackGround.h"
#include "../../Player/Player.h"
#include "../../Input/Input.h"
#include "../../GameSetting/GameSetting.h"
#include "../../Bullet/BulletManager.h"
#include "../../Enemy/Enemy.h"
#include "../../Boss Enemy/BossEnemy.h"

// 背景のスピード
#define BACK_GROUND_SPEED (-1.5f)

void InitPlayScene()
{
	// 背景初期化
	InitBackGround();

	// プレイヤー初期化
	InitPlayer();

	// エネミー初期化
	InitEnemy();

	InitBossEnemy();

	// 弾を初期化
	InitBullet();

}

void LoadPlayScene()
{
	// プレイヤーロード
	LoadPlayer();

	// 弾ロード
	LoadBullet();

}

void StartPlayScene()
{
	// プレイヤー開始
	StartPlayer();

	StartBossEnemy();

}

void StepPlayScene()
{

	// プレイヤーステップ
	StepPlayer();

	// 弾ステップ
	StepBullet();

}

void UpdatePlayScene()
{
	// 背景更新
	UpdateBackGround();

	// プレイヤー更新
	UpdatePlayer();

	// エネミー更新
	UpdateEnemy();

	UpdateBossEnemy();

	// 弾更新
	UpdateBullet();

	if (!g_IsBossAlive && IsBossDefeated())
	{
		ChangeScene(SCENE_GAME_CLEAR);
	}

	
}

void DrawPlayScene()
{
	// 背景描画
	DrawBackGround();

	// 弾描画
	DrawBullet();

	// エネミー描画
	DrawEnemy();

	DrawBossEnemy();

	// プレイヤー描画
	DrawPlayer();


}

void FinPlayScene()
{
	// 背景終了
	FinBackGround();

	// プレイヤー終了
	FinPlayer();

	DeleteBossEnemy();

	// 弾終了
	FinBullet();
}
