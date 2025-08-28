#pragma once

#define ENEMY_MAX         50
#define ENEMY_BULLET_MAX 100

struct Enemy {
    bool active;
    float x, y;
    float speedX, speedY;
    int handle;
    int width, height;
    int shotTimer;
};

struct EnemyBullet {
    bool active;
    float x, y;
    float speedX, speedY;
    int handle;
    int width, height;
};

// ƒOƒ[ƒoƒ‹•Ï”‚Ì extern éŒ¾
extern Enemy g_Enemies[ENEMY_MAX];
extern EnemyBullet g_EnemyBullets[ENEMY_BULLET_MAX];
extern bool g_IsBossAlive;

// ŠÖ”
void InitEnemy();
void UpdateEnemy();
void DrawEnemy();
void DeleteEnemy();
void SpawnEnemy(float x, float y, float speedX, float speedY);
void ClearAllEnemiesAndBullets();