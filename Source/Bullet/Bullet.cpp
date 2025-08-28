
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


// 初期化処理
void InitStraightBullet()
{
	for (int i = 0; i < STRAIGHT_BULLET_MAX; i++)
	{
		StraightBulletData& bullet = g_StraightBulletData[i];
		bullet.handle = 0;
		bullet.life = 0;
		bullet.posX = 0.0f;
		bullet.posY = 0.0f;
		bullet.moveX = 0.0f;
		bullet.moveY = 0.0f;
		bullet.width = 0.0f;
		bullet.height = 0.0f;
		bullet.radius = 0.0f;
		bullet.active = false;
		bullet.tag = BULLET_COLLISION_TAG_PLAYER; // デフォルトはプレイヤー弾
	}

	for (int i = 0; i < STRAIGHT_BULLET_TYPE_MAX; i++)
	{
		g_BulletHandle[i] = 0;
	}
}

// 画像ロード処理
void LoadStraightBullet()
{
	int width, height;

	// プレイヤー通常弾の画像ロード
	int handle = LoadGraph("Data/Bullet/マグロ.png");
	g_BulletHandle[STRAIGHT_BULLET_TYPE_PLAYER_NORMAL] = handle;
	GetGraphSize(handle, &width, &height);
	g_BulletRadius[STRAIGHT_BULLET_TYPE_PLAYER_NORMAL] = width / 3.0f;
	// 敵通常弾の画像ロード（例）
	handle = LoadGraph("Data/Bullet/EnemyBullet.png");
	g_BulletHandle[STRAIGHT_BULLET_TYPE_ENEMY_NORMAL] = handle;
	GetGraphSize(handle, &width, &height);
	g_BulletRadius[STRAIGHT_BULLET_TYPE_ENEMY_NORMAL] = width / 3.0f;
	// ボス弾
	handle = LoadGraph("Data/Bullet/BossBullet.png");
	g_BulletHandle[STRAIGHT_BULLET_TYPE_BOSS] = handle;
	GetGraphSize(handle, &width, &height);
	g_BulletRadius[STRAIGHT_BULLET_TYPE_BOSS] = width / 6.0f;

}

// ステップ処理（寿命減少）
void StepStraightBullet()
{
	for (int i = 0; i < STRAIGHT_BULLET_MAX; i++)
	{
		StraightBulletData& bullet = g_StraightBulletData[i];
		if (!bullet.active) continue;

		bullet.life--;
		if (bullet.life <= 0)
		{
			bullet.active = false;
		}
	}
}

// 更新処理（移動処理）
void UpdateStraightBullet()
{
	for (int i = 0; i < STRAIGHT_BULLET_MAX; i++)
	{
		StraightBulletData& bullet = g_StraightBulletData[i];
		if (!bullet.active) continue;

		bullet.posX += bullet.moveX;
		bullet.posY += bullet.moveY;
	}
}

void DrawStraightBullet()
{
	for (int i = 0; i < STRAIGHT_BULLET_MAX; i++)
	{
		StraightBulletData& bullet = g_StraightBulletData[i];
		if (!bullet.active) continue;

		// 弾の画像を描画
		DrawGraph((int)bullet.posX, (int)bullet.posY, bullet.handle, TRUE);

		// === 当たり判定の可視化（デバッグ用） ===
		int centerX = (int)(bullet.posX + bullet.width / 2.0f);
		int centerY = (int)(bullet.posY + bullet.height / 2.0f);
		int radius = (int)bullet.radius;

		// 赤い円で描画（塗りつぶしなし）
		DrawCircle(centerX, centerY, radius, GetColor(255, 0, 0), FALSE);
	}
}


// 終了処理（画像解放）
void FinStraightBullet()
{
	for (int i = 0; i < STRAIGHT_BULLET_TYPE_MAX; i++)
	{
		if (g_BulletHandle[i] != 0)
		{
			DeleteGraph(g_BulletHandle[i]);
			g_BulletHandle[i] = 0;
		}
	}
}

// 弾発射処理
void FireStraightBullet(StraightBulletType type, FireBulletData fireData, BulletCollisionTag tag)
{
	for (int i = 0; i < STRAIGHT_BULLET_MAX; i++)
	{
		StraightBulletData& bullet = g_StraightBulletData[i];
		if (!bullet.active)
		{
			bullet.active = true;
			bullet.life = fireData.life;
			bullet.handle = g_BulletHandle[type];
			bullet.posX = fireData.posX;
			bullet.posY = fireData.posY;
			bullet.moveX = fireData.moveX;
			bullet.moveY = fireData.moveY;

			// 画像サイズ取得（キャッシュしてもいいが念のため）
			int w, h;
			GetGraphSize(bullet.handle, &w, &h);
			bullet.width = (float)w;
			bullet.height = (float)h;
			bullet.radius = g_BulletRadius[type];

			bullet.tag = tag;

			break;
		}
	}
}

// 配列アクセス用のポインタ返却
StraightBulletData* GetStraightBullet()
{
	return g_StraightBulletData;
}

// プレイヤーに当たった時の処理
void StraightBulletHitPlayer(int index)
{
	if (index < 0 || index >= STRAIGHT_BULLET_MAX) return;

	StraightBulletData& bullet = g_StraightBulletData[index];
	bullet.active = false;

	// ここにプレイヤー被弾時のエフェクトや処理を追加してもよい
}

// 敵に当たった時の処理
void StraightBulletHitEnemy(int index)
{
	if (index < 0 || index >= STRAIGHT_BULLET_MAX) return;

	StraightBulletData& bullet = g_StraightBulletData[index];
	bullet.active = false;

	// ここに敵被弾時のエフェクトや処理を追加してもよい
}


void ClearAllStraightBullets() 
{
	for (int i = 0; i < STRAIGHT_BULLET_MAX; i++) {
		g_StraightBulletData[i].active = false;
	}
}