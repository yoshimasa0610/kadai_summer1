#include "Bullet.h"
#include "../Collision/BulletCollision.h"
#include "../Bullet/BulletManager.h"

void InitBullet()
{
	// 各弾を初期化
	// 直線弾
	InitStraightBullet();
}

void LoadBullet()
{
	// 各弾をロード
	// 直線弾
	LoadStraightBullet();
}

void StepBullet()
{
	// 各弾をステップ
	// 直線弾
	StepStraightBullet();
}

void UpdateBullet()
{
	// 各弾を更新
	// 直線弾
	UpdateStraightBullet();
}

void DrawBullet()
{
	// 各弾を描画
	// 直線弾
	DrawStraightBullet();
}

void FinBullet()
{
	// 各弾を終了
	// 直線弾
	FinStraightBullet();
}

void FireBullet(BulletCategory category, int typeID, FireBulletData fireData, BulletCollisionTag tag)
{
	switch (category)
	{
	case BULLET_CATEGORY_STRAIGHT:
		StraightBulletType type = (StraightBulletType)typeID;
		FireStraightBullet(type, fireData, tag);
		break;
	}
}