#include "DxLib.h"
#include "Player.h"
#include "../Input/Input.h"	
#include "../Bullet/Bullet.h"
#include "../Bullet/BulletManager.h"




// プレイヤー設定関連
#define PLAYER_DEFAULT_POS_X (200.0f)
#define PLAYER_DEFAULT_POS_Y (250.0f)
#define PLAYER_MOVE_SPEED (3.0f)

// 弾関連
#define PLAYER_NORMAL_SHOT_SPEED	(32.0f)
#define PLAYER_NORMAL_SHOT_LIFE		(600)
#define PLAYER_NORMAL_SHOT_OFFSET_X	(50.0f)
#define PLAYER_NORMAL_SHOT_OFFSET_Y	(10.0f)
#define PLAYER_NORMAL_SHOT_INTERVAL (15)



// 移動可能エリア
#define PLAYER_MOVE_AREA_LEFT (0.0f)
#define PLAYER_MOVE_AREA_RIGHT (1536.0f)
#define PLAYER_MOVE_AREA_TOP (0.0f)
#define PLAYER_MOVE_AREA_BOTTOM (743.0f)

// プレイヤーの残機
#define PLAYER_DEFAULT_LIFE (2)

// リスポーンまでの待機時間
#define PLAYER_RESPAWN_WAIT (180)

// リスポーン時の無敵時間
#define PLAYER_RESPAWN_INVISIBLE_TIME (180)

// プレイヤー死亡エフェクトインターバル
#define PLAYER_DEAD_EFFECT_INTERVAL (2)

PlayerData g_PlayerData = { 0 };

void InitPlayer()
{
	g_PlayerData.life = 0;
	g_PlayerData.posX = PLAYER_DEFAULT_POS_X;
	g_PlayerData.posY = PLAYER_DEFAULT_POS_Y;
	g_PlayerData.moveX = 0.0f;
	g_PlayerData.moveY = 0.0f;
	g_PlayerData.bulletIntervalTimer = 0;
	g_PlayerData.respawnTimer = 0;
	g_PlayerData.active = false;
	g_PlayerData.invisible = false;
}

void LoadPlayer()
{
	g_PlayerData.handle = LoadGraph("Data/Player/クラゲ.png");
	
}

void StartPlayer()
{
	// 生存フラグを立てる
	g_PlayerData.active = true;

	// 残機の初期値設定
	g_PlayerData.life = PLAYER_DEFAULT_LIFE;

}

void StepPlayer()
{
	

	// 移動量は毎回リセットする
	g_PlayerData.moveX = 0.0f;
	g_PlayerData.moveY = 0.0f;

	// 通常弾のインターバル時間を減らす
	if (g_PlayerData.bulletIntervalTimer > 0)
	{
		g_PlayerData.bulletIntervalTimer--;
	}
	
	// 上入力
	if (IsInputKey(KEY_UP))
	{
		g_PlayerData.moveY = -PLAYER_MOVE_SPEED;
	}
	// 下入力
	if (IsInputKey(KEY_DOWN))
	{
		g_PlayerData.moveY = PLAYER_MOVE_SPEED;
	}
	// 左入力
	if (IsInputKey(KEY_LEFT))
	{
		g_PlayerData.moveX = -PLAYER_MOVE_SPEED;
	}
	// 右入力
	if (IsInputKey(KEY_RIGHT))
	{
		g_PlayerData.moveX = PLAYER_MOVE_SPEED;
	}

	// Z入力
	if (IsInputKey(KEY_Z))
	{
		// インターバル時間がすぎてから撃つ
		if (g_PlayerData.bulletIntervalTimer <= 0)
		{
			// 弾発射情報を設定
			const FireBulletData FIRE_DATA =
			{
				PLAYER_NORMAL_SHOT_LIFE,
				g_PlayerData.posX + PLAYER_NORMAL_SHOT_OFFSET_X,
				g_PlayerData.posY + PLAYER_NORMAL_SHOT_OFFSET_Y,
				PLAYER_NORMAL_SHOT_SPEED,
				0.0f,
			};
			FireBullet(BULLET_CATEGORY_STRAIGHT, STRAIGHT_BULLET_TYPE_PLAYER_NORMAL, FIRE_DATA, BULLET_COLLISION_TAG_PLAYER);

			
			// インターバル設定
			g_PlayerData.bulletIntervalTimer = PLAYER_NORMAL_SHOT_INTERVAL;
		}
	}
	
}

void UpdatePlayer()
{

	// 移動処理
	g_PlayerData.posX += g_PlayerData.moveX;
	g_PlayerData.posY += g_PlayerData.moveY;

	// 画面外に出ないように移動制限
	if (g_PlayerData.posX < PLAYER_MOVE_AREA_LEFT) g_PlayerData.posX = PLAYER_MOVE_AREA_LEFT;
	if (g_PlayerData.posX > PLAYER_MOVE_AREA_RIGHT) g_PlayerData.posX = PLAYER_MOVE_AREA_RIGHT;
	if (g_PlayerData.posY < PLAYER_MOVE_AREA_TOP) g_PlayerData.posY = PLAYER_MOVE_AREA_TOP;
	if (g_PlayerData.posY > PLAYER_MOVE_AREA_BOTTOM) g_PlayerData.posY = PLAYER_MOVE_AREA_BOTTOM;

}

void DrawPlayer()
{
	// 通常描画
	DrawGraph((int)g_PlayerData.posX, (int)g_PlayerData.posY, g_PlayerData.handle, TRUE);

}

void FinPlayer()
{
	DeleteGraph(g_PlayerData.handle);
}

PlayerData* GetPlayer()
{
	return &g_PlayerData;
}


