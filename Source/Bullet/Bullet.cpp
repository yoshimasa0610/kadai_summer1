
#include "DxLib.h"
#include "../Collision/BulletCollision.h"


#define HIT_EFFECT_INTERVAL (1)
#define HIT_EFFECT_OFFSET_X (-10.0f)
#define HIT_EFFECT_OFFSET_Y (-10.0f)

StraightBulletData g_StraightBulletData[STRAIGHT_BULLET_MAX] = { 0 };

// �e�e�ۂ̉摜�n���h��
int g_BulletHandle[STRAIGHT_BULLET_TYPE_MAX] = { 0 };

// �e�e�ۂ̔��a�f�[�^
float g_BulletRadius[STRAIGHT_BULLET_TYPE_MAX] = { 0 };

void InitStraightBullet()
{
	// �����������̂��߃|�C���^���g��
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

	// �e�o���b�g�̉摜�����[�h
	// �v���C���[�ʏ�e
	handle = LoadGraph("Data/Bullet/�}�O��.png");
	g_BulletHandle[STRAIGHT_BULLET_TYPE_PLAYER_NORMAL] = handle;

	// �摜����T�C�Y���擾 �摜�͐����`���O��
	GetGraphSize(handle, &width, &height);
	g_BulletRadius[STRAIGHT_BULLET_TYPE_PLAYER_NORMAL] = (float)width / 2.0f;



}

void StepStraightBullet()
{
	// �����������̂��߃|�C���^���g��
	StraightBulletData* bullet = g_StraightBulletData;
	for (int i = 0; i < STRAIGHT_BULLET_MAX; i++, bullet++)
	{
		// �����Ă���e��������������
		if (!bullet->active)continue;

		// ���������炷
		bullet->life--;
	}
}

void UpdateStraightBullet()
{
	// �����������̂��߃|�C���^���g��
	StraightBulletData* bullet = g_StraightBulletData;
	for (int i = 0; i < STRAIGHT_BULLET_MAX; i++, bullet++)
	{
		// �����Ă���e������������
		if (!bullet->active)continue;

		// �ړ�
		bullet->posX += bullet->moveX;
		bullet->posY += bullet->moveY;

		// ��������
		if (bullet->life <= 0)
		{
			// �������߂����琶���t���O��܂�
			bullet->active = false;
		}
	}
}

void DrawStraightBullet()
{
	// �����������̂��߃|�C���^���g��
	StraightBulletData* bullet = g_StraightBulletData;
	for (int i = 0; i < STRAIGHT_BULLET_MAX; i++, bullet++)
	{
		// �����Ă���e�����`�悷��
		if (!bullet->active) continue;

		DrawGraph((int)bullet->posX, (int)bullet->posY, bullet->handle, TRUE);
	}
}

void FinStraightBullet()
{
	// ���[�h�����������폜
	for (int i = 0; i < STRAIGHT_BULLET_TYPE_MAX; i++)
	{
		DeleteGraph(g_BulletHandle[i]);
	}
}

void FireStraightBullet(StraightBulletType type, FireBulletData fireData, BulletCollisionTag tag)
{
	// �����������̂��߃|�C���^���g��
	StraightBulletData* bullet = g_StraightBulletData;
	for (int i = 0; i < STRAIGHT_BULLET_MAX; i++, bullet++)
	{
		// �z����Ŏg���Ă��Ȃ��Ƃ����T��
		if (!bullet->active)
		{
			// ���ˏ���
			bullet->active = true;

			// �����ݒ�
			bullet->life = fireData.life;

			// �摜�ݒ�
			bullet->handle = g_BulletHandle[type];

			// ���W�ݒ�
			bullet->posX = fireData.posX;
			bullet->posY = fireData.posY;

			// �ړ��ʐݒ�
			bullet->moveX = fireData.moveX;
			bullet->moveY = fireData.moveY;

			// �摜���畝�ƍ������擾
			int w, h;
			GetGraphSize(bullet->handle, &w, &h);
			bullet->width = (float)w;
			bullet->height = (float)h;

			// �摜�������`�̑O��Ŕ��a��ݒ�
			bullet->radius = bullet->width / 2;

			// �����蔻��^�O�ݒ�
			bullet->tag = tag;

			// 1�����˂����甲����
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

	// �Փ˂����玀�S
	bullet->active = false;

	
}

void StraightBulletHitPlayer(int index)
{
	StraightBulletData* bullet = &g_StraightBulletData[index];

	// �Փ˂����玀�S
	bullet->active = false;
}
