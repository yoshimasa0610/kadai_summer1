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
};

// �����e�̎��
enum StraightBulletType
{
	STRAIGHT_BULLET_TYPE_PLAYER_NORMAL,	// �v���C���[�̒ʏ�e
	STRAIGHT_BULLET_TYPE_MAX
};

// �����e�̃f�[�^
struct StraightBulletData
{
	int handle;
	int life;
	float posX;
	float posY;
	float moveX;
	float moveY;
	float width;
	float height;
	float radius;
	bool active;
	BulletCollisionTag tag;
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