#include <cmath>
#include "DxLib.h"
#include "Player.h"
#include "../Input/Input.h"
#include "../Bullet/Bullet.h"
#include "../Bullet/BulletManager.h"
#include "../Collision/BulletCollision.h"
#include "../Scene/SceneManager.h"

#define PLAYER_MOVE_SPEED 6.0f
#define PLAYER_BULLET_INTERVAL 20
#define PLAYER_BULLET_SPEED 15.0f
#define PLAYER_BULLET_MAX 16
#define PLAYER_MOVE_MIN_X 0
#define PLAYER_MOVE_MAX_X 1600
#define PLAYER_MOVE_MIN_Y 0
#define PLAYER_MOVE_MAX_Y 800

static PlayerData g_PlayerData = { 0 };

typedef struct {
    bool active;
    float x, y;
    float speedX;
} PlayerBullet;

static PlayerBullet g_PlayerBullets[PLAYER_BULLET_MAX] = { 0 };
static int g_BulletHandle = -1;
int g_LifeIconHandle = -1;

int g_PlayerWidth = 0;
int g_PlayerHeight = 0;
float g_PlayerRadius = 0.0f;

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
    g_PlayerData.handle = LoadGraph("Data/Player/�N���Q.png");
    g_BulletHandle = LoadGraph("Data/Bullet/�e.png");
    g_LifeIconHandle = LoadGraph("Data/UI/�N���Q.png");

    // �摜�T�C�Y�擾
    GetGraphSize(g_PlayerData.handle, &g_PlayerWidth, &g_PlayerHeight);
    g_PlayerRadius = g_PlayerWidth / 2.0f; // ���a�͉摜���̔���
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

// �Փ˔���`�F�b�N�i�k���ςݔ��a�j
void CheckPlayerBulletCollision() {
    if (!g_PlayerData.active || g_PlayerData.invisible) return;

    float shrinkRate = 0.8f; // ���a��80%�ɏk��
    float px = g_PlayerData.posX + g_PlayerWidth / 2.0f;
    float py = g_PlayerData.posY + g_PlayerHeight / 2.0f;
    float pr = g_PlayerRadius * shrinkRate; // �k����̔��a

    for (int i = 0; i < STRAIGHT_BULLET_MAX; i++) {
        StraightBulletData& bullet = g_StraightBulletData[i];
        if (!bullet.active || bullet.tag != BULLET_COLLISION_TAG_ENEMY) continue;

        float bx = bullet.posX;
        float by = bullet.posY;

        float dx = bx - px;
        float dy = by - py;
        float distanceSq = dx * dx + dy * dy;
        float radiusSum = bullet.radius + pr;

        if (distanceSq < radiusSum * radiusSum) {
            // �Փˏ���
            StraightBulletHitPlayer(i);

            g_PlayerData.life--;
            g_PlayerData.invisible = true;
            g_PlayerData.invisibleTimer = 120;

            if (g_PlayerData.life <= 0) {
                g_PlayerData.active = false;
                ChangeScene(SCENE_GAME_OVER);
            }
            break;
        }
    }
}


void StepPlayer() {
    if (!g_PlayerData.active) return;

    float inputX = 0.0f;
    float inputY = 0.0f;

    if (g_PlayerData.bulletIntervalTimer > 0) g_PlayerData.bulletIntervalTimer--;

    if (IsInputKey(KEY_UP)) inputY = -1.0f;
    if (IsInputKey(KEY_DOWN)) inputY = 1.0f;
    if (IsInputKey(KEY_LEFT)) inputX = -1.0f;
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
        fireData.posX = g_PlayerData.posX + g_PlayerWidth;
        fireData.posY = g_PlayerData.posY + g_PlayerHeight / 2;
        fireData.moveX = PLAYER_BULLET_SPEED;
        fireData.moveY = 0.0f;
        fireData.life = 120;

        FireStraightBullet(STRAIGHT_BULLET_TYPE_PLAYER_NORMAL, fireData, BULLET_COLLISION_TAG_PLAYER);
        g_PlayerData.bulletIntervalTimer = PLAYER_BULLET_INTERVAL;
    }

    CheckPlayerBulletCollision();
}

void UpdatePlayer() {
    if (!g_PlayerData.active) return;

    if (g_PlayerData.invisible) {
        g_PlayerData.invisibleTimer--;
        if (g_PlayerData.invisibleTimer <= 0) g_PlayerData.invisible = false;
    }

    g_PlayerData.posX += g_PlayerData.moveX;
    g_PlayerData.posY += g_PlayerData.moveY;

    if (g_PlayerData.posX < PLAYER_MOVE_MIN_X) g_PlayerData.posX = PLAYER_MOVE_MIN_X;
    if (g_PlayerData.posX > PLAYER_MOVE_MAX_X - g_PlayerWidth) g_PlayerData.posX = PLAYER_MOVE_MAX_X - g_PlayerWidth;

    if (g_PlayerData.posY < PLAYER_MOVE_MIN_Y) g_PlayerData.posY = PLAYER_MOVE_MIN_Y;
    if (g_PlayerData.posY > PLAYER_MOVE_MAX_Y - g_PlayerHeight) g_PlayerData.posY = PLAYER_MOVE_MAX_Y - g_PlayerHeight;

    for (int i = 0; i < PLAYER_BULLET_MAX; i++) {
        if (g_PlayerBullets[i].active) {
            g_PlayerBullets[i].x += g_PlayerBullets[i].speedX;
            if (g_PlayerBullets[i].x > 1920) g_PlayerBullets[i].active = false;
        }
    }
}

void DrawPlayer() {
    if (!g_PlayerData.active) return;

    // ���G���͓_��
    if (g_PlayerData.invisible && (g_PlayerData.invisibleTimer / 5) % 2 == 0) return;

    // �v���C���[�`��
    DrawGraph((int)g_PlayerData.posX, (int)g_PlayerData.posY, g_PlayerData.handle, TRUE);

    // �v���C���[�e�`��
    for (int i = 0; i < PLAYER_BULLET_MAX; i++) {
        if (g_PlayerBullets[i].active) {
            DrawGraph((int)g_PlayerBullets[i].x, (int)g_PlayerBullets[i].y, g_BulletHandle, TRUE);
        }
    }

    // �c�@�A�C�R���`��
    for (int i = 0; i < g_PlayerData.life; i++) {
        DrawGraph(50 + i * 80, 50, g_LifeIconHandle, TRUE);
    }

    // --- �����蔻��̉����i�摜���S�E�����k���j ---
    float shrinkRate = 0.8f; // ���a��80%�ɏk��
    float px = g_PlayerData.posX + g_PlayerWidth / 2.0f;
    float py = g_PlayerData.posY + g_PlayerHeight / 2.0f;
    float radius = g_PlayerRadius * shrinkRate;

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
    DrawCircle((int)px, (int)py, (int)radius, GetColor(255, 0, 0), FALSE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}


void FinPlayer() {
    if (g_PlayerData.handle != -1) { DeleteGraph(g_PlayerData.handle); g_PlayerData.handle = -1; }
    if (g_BulletHandle != -1) { DeleteGraph(g_BulletHandle); g_BulletHandle = -1; }
    if (g_LifeIconHandle != -1) { DeleteGraph(g_LifeIconHandle); g_LifeIconHandle = -1; }
}

PlayerData* GetPlayer() { return &g_PlayerData; }
