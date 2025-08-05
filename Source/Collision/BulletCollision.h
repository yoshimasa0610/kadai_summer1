#pragma once
#include "../Bullet/Bullet.h"

// 各ロジックごとの関数
void InitStraightBullet();
void LoadStraightBullet();
void StepStraightBullet();
void UpdateStraightBullet();
void DrawStraightBullet();
void FinStraightBullet();

// 発射関数（必ずBulletManagerでしか呼ばないこと）
void FireStraightBullet(StraightBulletType type, FireBulletData fireData, BulletCollisionTag tag);

// 弾取得
StraightBulletData* GetStraightBullet();

// 当たり判定関連
void StraightBulletHitEnemy(int index);
void StraightBulletHitPlayer(int index);
