#pragma once


// 最大数
#define ENEMY_MAX         50
#define ENEMY_BULLET_MAX 100

// 敵構造体
struct Enemy {
    bool active;        // 使用中かどうか
    float x, y;         // 座標
    float speedX, speedY;
    int handle;         // 画像ハンドル
    int width, height;  // サイズ
    int shotTimer;      // 弾発射タイマー
};

// 敵の弾構造体
struct EnemyBullet {
    bool active;
    float x, y;
    float speedX;
    float speedY;
    int handle;
    int width, height;
};

// 敵＆敵弾の初期化
void InitEnemy();

// 敵の出現・移動・弾処理（自動）
void UpdateEnemy();

// 敵と弾の描画
void DrawEnemy();

// 敵と弾の終了処理
void DeleteEnemy();

// 明示的に敵を出現させたいとき用（必要があれば使用）
void SpawnEnemy(float x, float y, float speedX, float speedY);