#include <cmath>
#include "DxLib.h"
#include "Player.h"
#include "../Input/Input.h"
#include "../Bullet/Bullet.h"
#include "../Bullet/BulletManager.h"
#include "../Collision/BulletCollision.h"

#define PLAYER_MOVE_SPEED 6.0f
#define PLAYER_BULLET_INTERVAL 20
#define PLAYER_BULLET_SPEED 15.0f
#define PLAYER_BULLET_MAX 16
#define PLAYER_WIDTH 50    // プレイヤーの幅
#define PLAYER_HEIGHT 50   // プレイヤーの高さ
#define PLAYER_RADIUS (PLAYER_WIDTH / 2.0f)  // プレイヤーの半径（仮）
#define PLAYER_MOVE_MIN_X 0
#define PLAYER_MOVE_MAX_X 1600   // 可動範囲の右端
#define PLAYER_MOVE_MIN_Y 0
#define PLAYER_MOVE_MAX_Y 800    // 可動範囲の下端

static PlayerData g_PlayerData = { 0 };

typedef struct {
    bool active;
    float x, y;
    float speedX;
} PlayerBullet;

static PlayerBullet g_PlayerBullets[PLAYER_BULLET_MAX] = { 0 };

static int g_BulletHandle = -1;

int g_LifeIconHandle = -1;

void InitPlayer() {
    g_PlayerData.active = false;
    g_PlayerData.invisible = false;
    g_PlayerData.handle = -1;
    g_PlayerData.respawnTimer = 0;
    g_PlayerData.invisibleTimer = 0;
    g_PlayerData.life = 0;
    g_PlayerData.posX = 200.0f;
    g_PlayerData.posY = 250.0f;
    g_PlayerData.moveX = 0.0f;
    g_PlayerData.moveY = 0.0f;
    g_PlayerData.bulletIntervalTimer = 0;

    for (int i = 0; i < PLAYER_BULLET_MAX; i++) {
        g_PlayerBullets[i].active = false;
    }
}

void LoadPlayer() {
    g_PlayerData.handle = LoadGraph("Data/Player/クラゲ.png");
    g_BulletHandle = LoadGraph("Data/Bullet/弾.png");
    g_LifeIconHandle = LoadGraph("Data/UI/クラゲ.png");  // ハートのアイコンをロード
}

void StartPlayer() {
    g_PlayerData.active = true;
    g_PlayerData.life = 3;
    g_PlayerData.posX = 200.0f;
    g_PlayerData.posY = 250.0f;
    g_PlayerData.invisible = false;
    g_PlayerData.respawnTimer = 0;
    g_PlayerData.invisibleTimer = 0;
}

void CheckPlayerBulletCollision() {
    if (!g_PlayerData.active || g_PlayerData.invisible) return;  // 無敵状態のプレイヤーは判定しない

    // プレイヤーの中心位置と半径を計算
    float px = g_PlayerData.posX + PLAYER_WIDTH / 2.0f;
    float py = g_PlayerData.posY + PLAYER_HEIGHT / 2.0f;
    float pr = PLAYER_RADIUS;  // プレイヤーの半径

    // すべての弾に対してチェック
    for (int i = 0; i < STRAIGHT_BULLET_MAX; i++) {
        StraightBulletData& bullet = g_StraightBulletData[i];

        // 弾がアクティブで、プレイヤーが撃った弾でない場合のみチェック
        if (!bullet.active || bullet.tag != BULLET_COLLISION_TAG_ENEMY) continue;

        // 弾とプレイヤーの距離計算（円形当たり判定）
        float dx = bullet.posX + bullet.radius - px;
        float dy = bullet.posY + bullet.radius - py;
        float distanceSq = dx * dx + dy * dy;
        float radiusSum = bullet.radius + pr;

        // 当たり判定
        if (distanceSq < radiusSum * radiusSum) {
            // 衝突した場合の処理
            StraightBulletHitPlayer(i);  // 弾を消す

            // プレイヤーのライフ減少
            g_PlayerData.life--;
            g_PlayerData.invisible = true;  // 無敵状態にする
            g_PlayerData.invisibleTimer = 120;  // 無敵時間（例：120フレーム）

            // プレイヤーが死亡した場合の処理
            if (g_PlayerData.life <= 0) {
                g_PlayerData.active = false;  // プレイヤーを非アクティブにする
                // ここでゲームオーバー処理などを実装する
            }

            break;  // 1個の弾が当たったら終了
        }
    }
}

void StepPlayer() {
    if (!g_PlayerData.active) return;

    float inputX = 0.0f;
    float inputY = 0.0f;

    if (g_PlayerData.bulletIntervalTimer > 0) {
        g_PlayerData.bulletIntervalTimer--;
    }

    if (IsInputKey(KEY_UP))    inputY = -1.0f;
    if (IsInputKey(KEY_DOWN))  inputY = 1.0f;
    if (IsInputKey(KEY_LEFT))  inputX = -1.0f;
    if (IsInputKey(KEY_RIGHT)) inputX = 1.0f;

    float lenSq = inputX * inputX + inputY * inputY;
    if (lenSq > 0.0f) {
        float invLen = 1.0f / std::sqrt(lenSq);
        inputX *= invLen;
        inputY *= invLen;
    }

    g_PlayerData.moveX = inputX * PLAYER_MOVE_SPEED;
    g_PlayerData.moveY = inputY * PLAYER_MOVE_SPEED;

    if (IsInputKey(KEY_SPACE) && g_PlayerData.bulletIntervalTimer <= 0) {
        FireBulletData fireData;
        fireData.posX = g_PlayerData.posX + PLAYER_WIDTH;
        fireData.posY = g_PlayerData.posY + PLAYER_HEIGHT / 2;
        fireData.moveX = PLAYER_BULLET_SPEED;
        fireData.moveY = 0.0f;  
        fireData.life = 120;  // 弾の寿命（例：120フレーム）

        FireStraightBullet(STRAIGHT_BULLET_TYPE_PLAYER_NORMAL, fireData, BULLET_COLLISION_TAG_PLAYER);

        g_PlayerData.bulletIntervalTimer = PLAYER_BULLET_INTERVAL;
    }

    // プレイヤーと弾の当たり判定をチェック
    CheckPlayerBulletCollision();
}

void UpdatePlayer() {
    if (!g_PlayerData.active) return;

    if (g_PlayerData.invisible) {
        g_PlayerData.invisibleTimer--;
        if (g_PlayerData.invisibleTimer <= 0) {
            g_PlayerData.invisible = false;
        }
    }

    g_PlayerData.posX += g_PlayerData.moveX;
    g_PlayerData.posY += g_PlayerData.moveY;

    // --- 可動域の制限 ---
    if (g_PlayerData.posX < PLAYER_MOVE_MIN_X)
        g_PlayerData.posX = PLAYER_MOVE_MIN_X;
    if (g_PlayerData.posX > PLAYER_MOVE_MAX_X - PLAYER_WIDTH)
        g_PlayerData.posX = PLAYER_MOVE_MAX_X - PLAYER_WIDTH;

    if (g_PlayerData.posY < PLAYER_MOVE_MIN_Y)
        g_PlayerData.posY = PLAYER_MOVE_MIN_Y;
    if (g_PlayerData.posY > PLAYER_MOVE_MAX_Y - PLAYER_HEIGHT)
        g_PlayerData.posY = PLAYER_MOVE_MAX_Y - PLAYER_HEIGHT;

    // --- プレイヤーの弾の更新 ---
    for (int i = 0; i < PLAYER_BULLET_MAX; i++) {
        if (g_PlayerBullets[i].active) {
            g_PlayerBullets[i].x += g_PlayerBullets[i].speedX;
            if (g_PlayerBullets[i].x > 1920) {
                g_PlayerBullets[i].active = false;
            }
        }
    }
}

void DrawPlayer()
{
    if (!g_PlayerData.active) return;

    // 無敵時は点滅させる
    if (g_PlayerData.invisible) {
        if ((g_PlayerData.invisibleTimer / 5) % 2 == 0) return;
    }

    // プレイヤー描画
    DrawGraph((int)g_PlayerData.posX, (int)g_PlayerData.posY, g_PlayerData.handle, TRUE);

    // プレイヤー弾描画
    for (int i = 0; i < PLAYER_BULLET_MAX; i++) {
        if (g_PlayerBullets[i].active) {
            DrawGraph((int)g_PlayerBullets[i].x, (int)g_PlayerBullets[i].y, g_BulletHandle, TRUE);
        }
    }

    // 残機アイコン描画
    for (int i = 0; i < g_PlayerData.life; i++) {
        DrawGraph(50 + i * 80, 50, g_LifeIconHandle, TRUE);
    }

    // --- 当たり判定の可視化 ---
    // プレイヤーの中心
    float px = g_PlayerData.posX + PLAYER_WIDTH / 2.0f;
    float py = g_PlayerData.posY + PLAYER_HEIGHT / 2.0f;

    // 半透明の円を描画（赤）
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);  // 半透明
    DrawCircle((int)px, (int)py, (int)PLAYER_RADIUS, GetColor(255, 0, 0), FALSE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); // ブレンド解除
}


void FinPlayer() 
{
    if (g_PlayerData.handle != -1) {
        DeleteGraph(g_PlayerData.handle);
        g_PlayerData.handle = -1;
    }
    if (g_BulletHandle != -1) {
        DeleteGraph(g_BulletHandle);
        g_BulletHandle = -1;
    }
    if (g_LifeIconHandle != -1) {
        DeleteGraph(g_LifeIconHandle);  // ハートのアイコン画像を解放
        g_LifeIconHandle = -1;
    }
}

PlayerData* GetPlayer() {
    return &g_PlayerData;
}