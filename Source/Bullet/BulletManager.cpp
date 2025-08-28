#include "Bullet.h"
#include "../Collision/BulletCollision.h"
#include "../Bullet/BulletManager.h"

void InitBullet()
{
	// �e�e��������
	// �����e
	InitStraightBullet();
}

void LoadBullet()
{
	// �e�e�����[�h
	// �����e
	LoadStraightBullet();
}

void StepBullet()
{
	// �e�e���X�e�b�v
	// �����e
	StepStraightBullet();
}

void UpdateBullet()
{
	// �e�e���X�V
	// �����e
	UpdateStraightBullet();
}

void DrawBullet()
{
	// �e�e��`��
	// �����e
	DrawStraightBullet();
}

void FinBullet()
{
	// �e�e���I��
	// �����e
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