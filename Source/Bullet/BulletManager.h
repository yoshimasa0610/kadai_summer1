#pragma once
#include "Bullet.h"

// �e�S�̂̏���
void InitBullet();
void LoadBullet();
void StepBullet();
void UpdateBullet();
void DrawBullet();
void FinBullet();

// �e����
void FireBullet(BulletCategory category, int typeID, FireBulletData fireData, BulletCollisionTag tag);
