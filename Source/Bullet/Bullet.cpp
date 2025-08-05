
#include "DxLib.h"
#include "../Collision/BulletCollision.h"


#define HIT_EFFECT_INTERVAL (1)
#define HIT_EFFECT_OFFSET_X (-10.0f)
#define HIT_EFFECT_OFFSET_Y (-10.0f)

StraightBulletData g_StraightBulletData[STRAIGHT_BULLET_MAX] = { 0 };

// 各弾丸の画像ハンドル
int g_BulletHandle[STRAIGHT_BULLET_TYPE_MAX] = { 0 };

// 各弾丸の半径データ
float g_BulletRadius[STRAIGHT_BULLET_TYPE_MAX] = { 0 };

void InitStraightBullet()
{
	// 処理高速化のためポインタを使う
	StraightBulletData* bullet = g_StraightBulletData;
	for (int i = 0; i < STRAIGHT_BULLET_MAX; i++)
	{
		bullet->handle = 0;
		bullet->life = 0;
		bullet->posX = 0.0f;
		bullet->posY = 0.0f;
		bullet->moveX = 0.0f;
		bullet->moveY = 0.0f;
		bullet->radius = 0.0f;
		bullet->active = false;
	}

	for (int i = 0; i < STRAIGHT_BULLET_TYPE_MAX; i++)
	{
		g_BulletHandle[i] = 0;
	}
}

void LoadStraightBullet()
{
	int handle = 0;
	int width, height;

	// 各バレットの画像をロード
	// プレイヤー通常弾
	handle = LoadGraph("Data/Bullet/マグロ.png");
	g_BulletHandle[STRAIGHT_BULLET_TYPE_PLAYER_NORMAL] = handle;

	// 画像からサイズを取得 画像は正方形が前提
	GetGraphSize(handle, &width, &height);
	g_BulletRadius[STRAIGHT_BULLET_TYPE_PLAYER_NORMAL] = (float)width / 2.0f;



}

void StepStraightBullet()
{
	// 処理高速化のためポインタを使う
	StraightBulletData* bullet = g_StraightBulletData;
	for (int i = 0; i < STRAIGHT_BULLET_MAX; i++, bullet++)
	{
		// 生きている弾だけ処理をする
		if (!bullet->active)continue;

		// 寿命を減らす
		bullet->life--;
	}
}

void UpdateStraightBullet()
{
	// 処理高速化のためポインタを使う
	StraightBulletData* bullet = g_StraightBulletData;
	for (int i = 0; i < STRAIGHT_BULLET_MAX; i++, bullet++)
	{
		// 生きている弾だけ処理する
		if (!bullet->active)continue;

		// 移動
		bullet->posX += bullet->moveX;
		bullet->posY += bullet->moveY;

		// 寿命処理
		if (bullet->life <= 0)
		{
			// 寿命が過ぎたら生存フラグを折る
			bullet->active = false;
		}
	}
}

void DrawStraightBullet()
{
	// 処理高速化のためポインタを使う
	StraightBulletData* bullet = g_StraightBulletData;
	for (int i = 0; i < STRAIGHT_BULLET_MAX; i++, bullet++)
	{
		// 生きている弾だけ描画する
		if (!bullet->active) continue;

		DrawGraph((int)bullet->posX, (int)bullet->posY, bullet->handle, TRUE);
	}
}

void FinStraightBullet()
{
	// ロードした分だけ削除
	for (int i = 0; i < STRAIGHT_BULLET_TYPE_MAX; i++)
	{
		DeleteGraph(g_BulletHandle[i]);
	}
}

void FireStraightBullet(StraightBulletType type, FireBulletData fireData, BulletCollisionTag tag)
{
	// 処理高速化のためポインタを使う
	StraightBulletData* bullet = g_StraightBulletData;
	for (int i = 0; i < STRAIGHT_BULLET_MAX; i++, bullet++)
	{
		// 配列内で使われていないところを探す
		if (!bullet->active)
		{
			// 発射処理
			bullet->active = true;

			// 寿命設定
			bullet->life = fireData.life;

			// 画像設定
			bullet->handle = g_BulletHandle[type];

			// 座標設定
			bullet->posX = fireData.posX;
			bullet->posY = fireData.posY;

			// 移動量設定
			bullet->moveX = fireData.moveX;
			bullet->moveY = fireData.moveY;

			// 画像から幅と高さを取得
			int w, h;
			GetGraphSize(bullet->handle, &w, &h);
			bullet->width = (float)w;
			bullet->height = (float)h;

			// 画像が正方形の前提で半径を設定
			bullet->radius = bullet->width / 2;

			// 当たり判定タグ設定
			bullet->tag = tag;

			// 1発発射したら抜ける
			break;
		}
	}
}

StraightBulletData* GetStraightBullet()
{
	return g_StraightBulletData;
}

void StraightBulletHitEnemy(int index)
{
	StraightBulletData* bullet = &g_StraightBulletData[index];

	// 衝突したら死亡
	bullet->active = false;

	
}

void StraightBulletHitPlayer(int index)
{
	StraightBulletData* bullet = &g_StraightBulletData[index];

	// 衝突したら死亡
	bullet->active = false;
}
