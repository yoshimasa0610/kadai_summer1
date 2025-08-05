#pragma once


// �ő吔
#define ENEMY_MAX         50
#define ENEMY_BULLET_MAX 100

// �G�\����
struct Enemy {
    bool active;        // �g�p�����ǂ���
    float x, y;         // ���W
    float speedX, speedY;
    int handle;         // �摜�n���h��
    int width, height;  // �T�C�Y
    int shotTimer;      // �e���˃^�C�}�[
};

// �G�̒e�\����
struct EnemyBullet {
    bool active;
    float x, y;
    float speedX;
    float speedY;
    int handle;
    int width, height;
};

// �G���G�e�̏�����
void InitEnemy();

// �G�̏o���E�ړ��E�e�����i�����j
void UpdateEnemy();

// �G�ƒe�̕`��
void DrawEnemy();

// �G�ƒe�̏I������
void DeleteEnemy();

// �����I�ɓG���o�����������Ƃ��p�i�K�v������Ύg�p�j
void SpawnEnemy(float x, float y, float speedX, float speedY);