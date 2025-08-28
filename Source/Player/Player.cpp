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
#define PLAYER_WIDTH 50    // �v���C���[�̕�
#define PLAYER_HEIGHT 50   // �v���C���[�̍���
#define PLAYER_RADIUS (PLAYER_WIDTH / 2.0f)  // �v���C���[�̔��a�i���j
#define PLAYER_MOVE_MIN_X 0
#define PLAYER_MOVE_MAX_X 1600   // ���͈͂̉E�[
#define PLAYER_MOVE_MIN_Y 0
#define PLAYER_MOVE_MAX_Y 800    // ���͈͂̉��[

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
    g_PlayerData.handle = LoadGraph("Data/Player/�N���Q.png");
    g_BulletHandle = LoadGraph("Data/Bullet/�e.png");
    g_LifeIconHandle = LoadGraph("Data/UI/�N���Q.png");  // �n�[�g�̃A�C�R�������[�h
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
    if (!g_PlayerData.active || g_PlayerData.invisible) return;  // ���G��Ԃ̃v���C���[�͔��肵�Ȃ�

    // �v���C���[�̒��S�ʒu�Ɣ��a���v�Z
    float px = g_PlayerData.posX + PLAYER_WIDTH / 2.0f;
    float py = g_PlayerData.posY + PLAYER_HEIGHT / 2.0f;
    float pr = PLAYER_RADIUS;  // �v���C���[�̔��a

    // ���ׂĂ̒e�ɑ΂��ă`�F�b�N
    for (int i = 0; i < STRAIGHT_BULLET_MAX; i++) {
        StraightBulletData& bullet = g_StraightBulletData[i];

        // �e���A�N�e�B�u�ŁA�v���C���[���������e�łȂ��ꍇ�̂݃`�F�b�N
        if (!bullet.active || bullet.tag != BULLET_COLLISION_TAG_ENEMY) continue;

        // �e�ƃv���C���[�̋����v�Z�i�~�`�����蔻��j
        float dx = bullet.posX + bullet.radius - px;
        float dy = bullet.posY + bullet.radius - py;
        float distanceSq = dx * dx + dy * dy;
        float radiusSum = bullet.radius + pr;

        // �����蔻��
        if (distanceSq < radiusSum * radiusSum) {
            // �Փ˂����ꍇ�̏���
            StraightBulletHitPlayer(i);  // �e������

            // �v���C���[�̃��C�t����
            g_PlayerData.life--;
            g_PlayerData.invisible = true;  // ���G��Ԃɂ���
            g_PlayerData.invisibleTimer = 120;  // ���G���ԁi��F120�t���[���j

            // �v���C���[�����S�����ꍇ�̏���
            if (g_PlayerData.life <= 0) {
                g_PlayerData.active = false;  // �v���C���[���A�N�e�B�u�ɂ���
                // �����ŃQ�[���I�[�o�[�����Ȃǂ���������
            }

            break;  // 1�̒e������������I��
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
        fireData.life = 120;  // �e�̎����i��F120�t���[���j

        FireStraightBullet(STRAIGHT_BULLET_TYPE_PLAYER_NORMAL, fireData, BULLET_COLLISION_TAG_PLAYER);

        g_PlayerData.bulletIntervalTimer = PLAYER_BULLET_INTERVAL;
    }

    // �v���C���[�ƒe�̓����蔻����`�F�b�N
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

    // --- ����̐��� ---
    if (g_PlayerData.posX < PLAYER_MOVE_MIN_X)
        g_PlayerData.posX = PLAYER_MOVE_MIN_X;
    if (g_PlayerData.posX > PLAYER_MOVE_MAX_X - PLAYER_WIDTH)
        g_PlayerData.posX = PLAYER_MOVE_MAX_X - PLAYER_WIDTH;

    if (g_PlayerData.posY < PLAYER_MOVE_MIN_Y)
        g_PlayerData.posY = PLAYER_MOVE_MIN_Y;
    if (g_PlayerData.posY > PLAYER_MOVE_MAX_Y - PLAYER_HEIGHT)
        g_PlayerData.posY = PLAYER_MOVE_MAX_Y - PLAYER_HEIGHT;

    // --- �v���C���[�̒e�̍X�V ---
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

    // ���G���͓_�ł�����
    if (g_PlayerData.invisible) {
        if ((g_PlayerData.invisibleTimer / 5) % 2 == 0) return;
    }

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

    // --- �����蔻��̉��� ---
    // �v���C���[�̒��S
    float px = g_PlayerData.posX + PLAYER_WIDTH / 2.0f;
    float py = g_PlayerData.posY + PLAYER_HEIGHT / 2.0f;

    // �������̉~��`��i�ԁj
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);  // ������
    DrawCircle((int)px, (int)py, (int)PLAYER_RADIUS, GetColor(255, 0, 0), FALSE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); // �u�����h����
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
        DeleteGraph(g_LifeIconHandle);  // �n�[�g�̃A�C�R���摜�����
        g_LifeIconHandle = -1;
    }
}

PlayerData* GetPlayer() {
    return &g_PlayerData;
}