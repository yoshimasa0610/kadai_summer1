#include "Enemy.h"
#include "DxLib.h"

// グローバル変数
Enemy g_Enemies[ENEMY_MAX];
EnemyBullet g_EnemyBullets[ENEMY_BULLET_MAX];
int g_EnemySpawnTimer = 0;

void InitEnemy() {
    int enemyHandle = LoadGraph("Data/Enemy/Enemy.png");
    int bulletHandle = LoadGraph("Data/Enemy/EnemyBullet.png");

    for (int i = 0; i < ENEMY_MAX; i++) {
        g_Enemies[i].active = false;
        g_Enemies[i].handle = enemyHandle;
        g_Enemies[i].width = 64;
        g_Enemies[i].height = 64;
        g_Enemies[i].shotTimer = 0;
    }

    for (int i = 0; i < ENEMY_BULLET_MAX; i++) {
        g_EnemyBullets[i].active = false;
        g_EnemyBullets[i].handle = bulletHandle;
        g_EnemyBullets[i].width = 50;
        g_EnemyBullets[i].height = 38;
        // 弾のX方向の速度を使うためspeedXも初期化しておく
        g_EnemyBullets[i].speedX = 0.0f;
        g_EnemyBullets[i].speedY = 0.0f;
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

void UpdateEnemy() {
    // 自動出現処理
    g_EnemySpawnTimer++;
    if (g_EnemySpawnTimer >= 180) {
        // 右端+64ピクセルから、上下は100〜799の間で出現
        float spawnX = 1600.0f + 64.0f;
        float spawnY = 100.0f + rand() % 700;
        SpawnEnemy(spawnX, spawnY, -2.0f, 0.0f); // 左方向に移動
        g_EnemySpawnTimer = 0;
    }

    for (int i = 0; i < ENEMY_MAX; i++) {
        if (!g_Enemies[i].active) continue;

        g_Enemies[i].x += g_Enemies[i].speedX;
        g_Enemies[i].y += g_Enemies[i].speedY;

        g_Enemies[i].shotTimer++;
        if (g_Enemies[i].shotTimer >= 120) {
            float bx = g_Enemies[i].x;
            float by = g_Enemies[i].y + g_Enemies[i].height / 2 - 8;

            for (int j = 0; j < ENEMY_BULLET_MAX; j++) {
                if (!g_EnemyBullets[j].active) {
                    g_EnemyBullets[j].active = true;
                    g_EnemyBullets[j].x = bx;
                    g_EnemyBullets[j].y = by;
                    g_EnemyBullets[j].speedX = -5.0f;  // ← 左方向に弾を飛ばす
                    g_EnemyBullets[j].speedY = 0.0f;
                    break;
                }
            }
            g_Enemies[i].shotTimer = 0;
        }

        // 画面左端を超えたら敵は非アクティブ化
        if (g_Enemies[i].x + g_Enemies[i].width < 0) {
            g_Enemies[i].active = false;
        }
    }

    // 弾の更新
    for (int i = 0; i < ENEMY_BULLET_MAX; i++) {
        if (!g_EnemyBullets[i].active) continue;

        g_EnemyBullets[i].x += g_EnemyBullets[i].speedX;
        g_EnemyBullets[i].y += g_EnemyBullets[i].speedY;

        // 弾が画面左端外に出たら非アクティブ化
        if (g_EnemyBullets[i].x + g_EnemyBullets[i].width < 0) {
            g_EnemyBullets[i].active = false;
        }
    }
}

void DrawEnemy() {
    for (int i = 0; i < ENEMY_MAX; i++) {
        if (g_Enemies[i].active) {
            DrawGraph((int)g_Enemies[i].x, (int)g_Enemies[i].y, g_Enemies[i].handle, TRUE);
        }
    }

    for (int i = 0; i < ENEMY_BULLET_MAX; i++) {
        if (g_EnemyBullets[i].active) {
            DrawGraph((int)g_EnemyBullets[i].x, (int)g_EnemyBullets[i].y, g_EnemyBullets[i].handle, TRUE);
        }
    }
}

void DeleteEnemy() {
    if (ENEMY_MAX > 0 && g_Enemies[0].handle != -1) {
        DeleteGraph(g_Enemies[0].handle);
    }
    if (ENEMY_BULLET_MAX > 0 && g_EnemyBullets[0].handle != -1) {
        DeleteGraph(g_EnemyBullets[0].handle);
    }
}