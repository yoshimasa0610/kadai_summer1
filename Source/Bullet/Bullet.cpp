
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


// ����������
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
		bullet.tag = BULLET_COLLISION_TAG_PLAYER; // �f�t�H���g�̓v���C���[�e
	}

	for (int i = 0; i < STRAIGHT_BULLET_TYPE_MAX; i++)
	{
		g_BulletHandle[i] = 0;
	}
}

// �摜���[�h����
void LoadStraightBullet()
{
	int width, height;

	// �v���C���[�ʏ�e�̉摜���[�h
	int handle = LoadGraph("Data/Bullet/�}�O��.png");
	g_BulletHandle[STRAIGHT_BULLET_TYPE_PLAYER_NORMAL] = handle;
	GetGraphSize(handle, &width, &height);
	g_BulletRadius[STRAIGHT_BULLET_TYPE_PLAYER_NORMAL] = width / 3.0f;
	// �G�ʏ�e�̉摜���[�h�i��j
	handle = LoadGraph("Data/Bullet/EnemyBullet.png");
	g_BulletHandle[STRAIGHT_BULLET_TYPE_ENEMY_NORMAL] = handle;
	GetGraphSize(handle, &width, &height);
	g_BulletRadius[STRAIGHT_BULLET_TYPE_ENEMY_NORMAL] = width / 3.0f;
	// �{�X�e
	handle = LoadGraph("Data/Bullet/BossBullet.png");
	g_BulletHandle[STRAIGHT_BULLET_TYPE_BOSS] = handle;
	GetGraphSize(handle, &width, &height);
	g_BulletRadius[STRAIGHT_BULLET_TYPE_BOSS] = width / 6.0f;

}

// �X�e�b�v�����i���������j
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

// �X�V�����i�ړ������j
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

		// �e�̉摜��`��
		DrawGraph((int)bullet.posX, (int)bullet.posY, bullet.handle, TRUE);

		// === �����蔻��̉����i�f�o�b�O�p�j ===
		int centerX = (int)(bullet.posX + bullet.width / 2.0f);
		int centerY = (int)(bullet.posY + bullet.height / 2.0f);
		int radius = (int)bullet.radius;

		// �Ԃ��~�ŕ`��i�h��Ԃ��Ȃ��j
		DrawCircle(centerX, centerY, radius, GetColor(255, 0, 0), FALSE);
	}
}


// �I�������i�摜����j
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

// �e���ˏ���
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

			// �摜�T�C�Y�擾�i�L���b�V�����Ă��������O�̂��߁j
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

// �z��A�N�Z�X�p�̃|�C���^�ԋp
StraightBulletData* GetStraightBullet()
{
	return g_StraightBulletData;
}

// �v���C���[�ɓ����������̏���
void StraightBulletHitPlayer(int index)
{
	if (index < 0 || index >= STRAIGHT_BULLET_MAX) return;

	StraightBulletData& bullet = g_StraightBulletData[index];
	bullet.active = false;

	// �����Ƀv���C���[��e���̃G�t�F�N�g�⏈����ǉ����Ă��悢
}

// �G�ɓ����������̏���
void StraightBulletHitEnemy(int index)
{
	if (index < 0 || index >= STRAIGHT_BULLET_MAX) return;

	StraightBulletData& bullet = g_StraightBulletData[index];
	bullet.active = false;

	// �����ɓG��e���̃G�t�F�N�g�⏈����ǉ����Ă��悢
}


void ClearAllStraightBullets() 
{
	for (int i = 0; i < STRAIGHT_BULLET_MAX; i++) {
		g_StraightBulletData[i].active = false;
	}
}