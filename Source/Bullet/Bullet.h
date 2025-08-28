#pragma once

#define STRAIGHT_BULLET_MAX (1024)

// 発射する弾丸のカテゴリ
enum BulletCategory
{
	BULLET_CATEGORY_STRAIGHT,
};

// 弾の当たり判定で区別をつけるためのタグ
enum BulletCollisionTag
{
	BULLET_COLLISION_TAG_PLAYER,	// プレイヤーが撃った弾
	BULLET_COLLISION_TAG_ENEMY,		// 敵が撃った弾
};

// 直線弾の種類
enum StraightBulletType
{
	STRAIGHT_BULLET_TYPE_PLAYER_NORMAL, // プレイヤーの通常弾
	STRAIGHT_BULLET_TYPE_ENEMY_NORMAL,  // 敵の通常弾
	STRAIGHT_BULLET_TYPE_BOSS,          // ボス専用弾を追加
	STRAIGHT_BULLET_TYPE_MAX
};

// 直線弾のデータ
struct StraightBulletData
{
	int handle;              // 画像ハンドル
	int life;                // 弾の寿命
	float posX;
	float posY;
	float moveX;
	float moveY;
	float width;
	float height;
	float radius;
	bool active;
	BulletCollisionTag tag;  // 当たり判定用タグ
};

// 発射に必要なデータ
struct FireBulletData
{
	int life;
	float posX;
	float posY;
	float moveX;
	float moveY;
};

extern StraightBulletData g_StraightBulletData[STRAIGHT_BULLET_MAX];
