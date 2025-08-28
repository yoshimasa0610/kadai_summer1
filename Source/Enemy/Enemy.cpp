#include "Enemy.h"
#include "DxLib.h"
#include "../Boss Enemy/BossEnemy.h"
#include "../Bullet/BulletManager.h"   
#include "../Bullet/Bullet.h"
#include "../Collision/BulletCollision.h"

// グローバル変数
Enemy g_Enemies[ENEMY_MAX];
int g_EnemySpawnTimer = 0;
extern bool g_IsBossAlive;  

// 敵の弾発射間隔（フレーム数）
#define ENEMY_SHOT_INTERVAL 60

void InitEnemy() {
    int enemyHandle = LoadGraph("Data/Enemy/Enemy.png");

    for (int i = 0; i < ENEMY_MAX; i++) {
        g_Enemies[i].active = false;
        g_Enemies[i].handle = enemyHandle;
        g_Enemies[i].width = 64;
        g_Enemies[i].height = 64;
        g_Enemies[i].shotTimer = 0;
    }

    g_EnemySpawnTimer = 0;
}

void SpawnEnemy(float x, float y, float speedX, float speedY) {
    for (int i = 0; i < ENEMY_MAX; i++) {
        if (!g_Enemies[i].active) {
            g_Enemies[i].active = true;
            g_Enemies[i].x = x;
            g_Enemies[i].y = y;
            g_Enemies[i].speedX = speedX;
            g_Enemies[i].speedY = speedY;
            g_Enemies[i].shotTimer = 0;
            break;
        }
    }
}

// 矩形 vs 円 の当たり判定
bool CheckCircleRectCollision(float cx, float cy, float radius, float rx, float ry, int rw, int rh) {
    float closestX = (cx < rx) ? rx : (cx > rx + rw) ? rx + rw : cx;
    float closestY = (cy < ry) ? ry : (cy > ry + rh) ? ry + rh : cy;

    float dx = cx - closestX;
    float dy = cy - closestY;

    return (dx * dx + dy * dy) < (radius * radius);
}

void EnemyShot() {
    for (int i = 0; i < ENEMY_MAX; i++) {
        if (!g_Enemies[i].active) continue;

        g_Enemies[i].shotTimer++;
        if (g_Enemies[i].shotTimer >= ENEMY_SHOT_INTERVAL) {
            g_Enemies[i].shotTimer = 0;

            FireBulletData fireData;
            fireData.posX = g_Enemies[i].x;
            fireData.posY = g_Enemies[i].y + g_Enemies[i].height / 2.0f;
            fireData.moveX = -5.0f;
            fireData.moveY = 0.0f;
            fireData.life = 400;

            FireStraightBullet(
                STRAIGHT_BULLET_TYPE_ENEMY_NORMAL,
                fireData,
                BULLET_COLLISION_TAG_ENEMY
            );
        }
    }
}

void UpdateEnemy() {
    if (g_IsBossAlive) return;

    // 敵出現タイマー
    g_EnemySpawnTimer++;
    if (g_EnemySpawnTimer >= 180) {
        float spawnX = 1600.0f + 64.0f;
        float spawnY = 100.0f + rand() % 700;
        SpawnEnemy(spawnX, spawnY, -4.0f, 0.0f);
        g_EnemySpawnTimer = 0;
    }

    StraightBulletData* bullets = GetStraightBullet();

    // 敵の移動と当たり判定
    for (int i = 0; i < ENEMY_MAX; i++) {
        if (!g_Enemies[i].active) continue;

        g_Enemies[i].x += g_Enemies[i].speedX;
        g_Enemies[i].y += g_Enemies[i].speedY;

        // プレイヤー弾との当たり判定
        for (int b = 0; b < STRAIGHT_BULLET_MAX; ++b) {
            if (!bullets[b].active) continue;
            if (bullets[b].tag != BULLET_COLLISION_TAG_PLAYER) continue;

            if (CheckCircleRectCollision(
                bullets[b].posX, bullets[b].posY, bullets[b].radius,
                g_Enemies[i].x, g_Enemies[i].y, g_Enemies[i].width, g_Enemies[i].height))
            {
                // 敵と弾を無効化
                g_Enemies[i].active = false;
                StraightBulletHitEnemy(b);
                break;
            }
        }

        // 画面外に出たら無効化
        if (g_Enemies[i].x + g_Enemies[i].width < 0) {
            g_Enemies[i].active = false;
        }
    }

    // 敵の弾発射処理呼び出し
    EnemyShot();
}

void DrawEnemy() {
    for (int i = 0; i < ENEMY_MAX; i++) {
        if (g_Enemies[i].active) {
            DrawGraph((int)g_Enemies[i].x, (int)g_Enemies[i].y, g_Enemies[i].handle, TRUE);
        }
    }
}

void ClearAllEnemiesAndBullets() {
    for (int i = 0; i < ENEMY_MAX; i++) {
        g_Enemies[i].active = false;
    }
}

void DeleteEnemy() {
    if (ENEMY_MAX > 0 && g_Enemies[0].handle != -1) {
        DeleteGraph(g_Enemies[0].handle);
    }
}