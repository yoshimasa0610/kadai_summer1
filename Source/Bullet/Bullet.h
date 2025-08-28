#pragma once

#define STRAIGHT_BULLET_MAX (1024)

// ���˂���e�ۂ̃J�e�S��
enum BulletCategory
{
	BULLET_CATEGORY_STRAIGHT,
};

// �e�̓����蔻��ŋ�ʂ����邽�߂̃^�O
enum BulletCollisionTag
{
	BULLET_COLLISION_TAG_PLAYER,	// �v���C���[���������e
	BULLET_COLLISION_TAG_ENEMY,		// �G���������e
};

// �����e�̎��
enum StraightBulletType
{
	STRAIGHT_BULLET_TYPE_PLAYER_NORMAL, // �v���C���[�̒ʏ�e
	STRAIGHT_BULLET_TYPE_ENEMY_NORMAL,  // �G�̒ʏ�e
	STRAIGHT_BULLET_TYPE_BOSS,          // �{�X��p�e��ǉ�
	STRAIGHT_BULLET_TYPE_MAX
};

// �����e�̃f�[�^
struct StraightBulletData
{
	int handle;              // �摜�n���h��
	int life;                // �e�̎���
	float posX;
	float posY;
	float moveX;
	float moveY;
	float width;
	float height;
	float radius;
	bool active;
	BulletCollisionTag tag;  // �����蔻��p�^�O
};

// ���˂ɕK�v�ȃf�[�^
struct FireBulletData
{
	int life;
	float posX;
	float posY;
	float moveX;
	float moveY;
};

extern StraightBulletData g_StraightBulletData[STRAIGHT_BULLET_MAX];
