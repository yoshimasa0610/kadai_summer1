#pragma once
#include "../Bullet/Bullet.h"

// �e���W�b�N���Ƃ̊֐�
void InitStraightBullet();
void LoadStraightBullet();
void StepStraightBullet();
void UpdateStraightBullet();
void DrawStraightBullet();
void FinStraightBullet();

// ���ˊ֐��i�K��BulletManager�ł����Ă΂Ȃ����Ɓj
void FireStraightBullet(StraightBulletType type, FireBulletData fireData, BulletCollisionTag tag);

// �e�擾
StraightBulletData* GetStraightBullet();

// �����蔻��֘A
void StraightBulletHitEnemy(int index);
void StraightBulletHitPlayer(int index);
