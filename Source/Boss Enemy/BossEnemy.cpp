#include "DxLib.h"
#include "BossEnemy.h"
#include "../Enemy/Enemy.h"
#include "../Bullet/Bullet.h"
#include "../Bullet/BulletManager.h"
#include "../Collision/BulletCollision.h"
#
// ==== �O���ϐ� ====
bool g_IsBossAlive = false;

// ==== �����N���X ====
class BossEnemy 
{
public:
    BossEnemy() = default;
    ~BossEnemy() = default;

    void Initialize();
    void Update();
    void Draw();
    void TakeDamage(int damage);
    bool IsDefeated() const;
    void Finalize();

public:
    int x = 0, y = 0;
    int width = 0;   
    int height = 0;  
    int speed = 4;
    int dir = 1;
    int hp = 100, maxHp = 100;
    int image = -1;
    int shotTimer = 0;
    int shotInterval = 90;
    bool isAlive = true;

    void Move();
    void Shoot();
    void FireBullet();
};

static BossEnemy boss;
static bool g_BossSpawnedOnce = false;

static int g_BossSpawnTimer = 0;
static const int BOSS_APPEAR_TIME = 300;


void InitBossEnemy()
{
    g_BossSpawnTimer = 0;
    g_IsBossAlive = false;
    g_BossSpawnedOnce = false;   // �ǉ��F2��ڈȍ~���o���ł���悤��
    boss.Finalize();             // �Â��摜���Ԃ��N���A
}

void StartBossEnemy()
{
    boss.Initialize();  // HP��ʒu�AisAlive ��������
}

void UpdateBossEnemy()
{
    if (!g_IsBossAlive)
    {
        if (!g_BossSpawnedOnce) // ����o�����H
        {
            g_BossSpawnTimer++;
            if (g_BossSpawnTimer >= BOSS_APPEAR_TIME) {
                boss.Initialize();
                g_IsBossAlive = true;
                g_BossSpawnedOnce = true; // �ȍ~�͏o�������Ȃ�
                ClearAllEnemiesAndBullets();
            }
        }
        return;
    }

    boss.Update();
    CheckBossCollisionWithPlayerBullets();

    if (boss.IsDefeated())
    {
        g_IsBossAlive = false;
    }
}

void DrawBossEnemy() 
{
    if (g_IsBossAlive)
    {
        boss.Draw();
    }
}

void DeleteBossEnemy() 
{
    boss.Finalize();
}

bool IsBossDefeated()
{
    return boss.IsDefeated();
}

void DamageBoss(int dmg) 
{
    if (g_IsBossAlive) 
    {
        boss.TakeDamage(dmg);
    }
}

void BossEnemy::Initialize()
{
    x = 1550 - 502;
    y = 400;
    speed = 4;
    dir = 1;
    maxHp = 100;
    hp = maxHp;
    shotInterval = 90;
    shotTimer = 0;
    isAlive = true;

    image = LoadGraph("Data/Boss/Boss.png");

    // ==== �摜�T�C�Y���擾 ====
    GetGraphSize(image, &width, &height);
}


void BossEnemy::Finalize()
{
    if (image != -1) 
    {
        DeleteGraph(image);
        image = -1;
    }
}


void BossEnemy::Update()
{
    if (!isAlive) return;

    Move();
    Shoot();

    if (hp <= 0) 
    {
        isAlive = false;
    }
}

void BossEnemy::Move()
{
    y += speed * dir;

    const int bossHeight = 375; // �{�X�摜�̍���

    // ��[�Ŕ��]
    if (y < 0) {
        y = 0;    // ��[�ɍ��킹��
        dir = 1;  // ��������
    }

    // ���[�Ŕ��]
    else if (y > 900 - bossHeight) {
        y = 900 - bossHeight; // ���[�ɍ��킹��
        dir = -1;             // �������
    }
}

void BossEnemy::Shoot() 
{
    if (--shotTimer <= 0) 
    {
        FireBullet();  // �{�X���e�𔭎�

        shotTimer = shotInterval;
    }
}

void BossEnemy::FireBullet() 
{
    FireBulletData fireData;

    // �{�X�̒e����ʒ����Ɍ����Ĕ��˂����
    fireData.posX = (float)(x + 300); // �{�X�̒��S�t��
    fireData.posY = (float)(y + 170); // �{�X�̒��S�t��
    fireData.moveX = -5.0f;           // ������
    fireData.moveY = 0.0f;            // ���������Ȃ�
    fireData.life = 400;               // �e�̎����i��j

    // �{�X�e�̔��ˁiSTRAIGHT_BULLET_TYPE_ENEMY_NORMAL�j
    FireStraightBullet(STRAIGHT_BULLET_TYPE_BOSS, fireData, BULLET_COLLISION_TAG_ENEMY);

}

void BossEnemy::Draw()
{
    if (!isAlive) return;

    // �摜�`��
    DrawGraph(x, y, image, TRUE);

    // HP�o�[
    int barWidth = 400;
    int hpWidth = (int)((double)hp / maxHp * barWidth);
    int barX = (1600 - barWidth) / 2;
    DrawBox(barX, 20, barX + barWidth, 40, GetColor(80, 80, 80), TRUE);
    DrawBox(barX, 20, barX + hpWidth, 40, GetColor(255, 0, 0), TRUE);

    // ==== �����蔻��̉��� ====
    DrawBox(x+150, y+75, x + width, y + height-100, GetColor(0, 255, 0), FALSE);
}


void BossEnemy::TakeDamage(int damage)
{
    hp -= damage;
    if (hp < 0) hp = 0;
}

bool BossEnemy::IsDefeated() const
{
    return !isAlive;
}

void CheckBossCollisionWithPlayerBullets()
{
    StraightBulletData* bullets = GetStraightBullet();  // �e�̔z����擾

    for (int i = 0; i < STRAIGHT_BULLET_MAX; i++) 
    {
        if (!bullets[i].active) continue;  // �e���A�N�e�B�u�łȂ��ꍇ�̓X�L�b�v
        if (bullets[i].tag != BULLET_COLLISION_TAG_PLAYER) continue;  // �v���C���[�̒e���ǂ������`�F�b�N

        float bx = bullets[i].posX + bullets[i].radius;  // �e�̒��S�ʒu�iX�j
        float by = bullets[i].posY + bullets[i].radius;  // �e�̒��S�ʒu�iY�j
        float br = bullets[i].radius;  // �e�̔��a

        if (CheckBossHit(bx, by, br)) {  // �{�X�ƒe�̏Փ˂𔻒�
            DamageBoss(1);  // �{�X�Ƀ_���[�W��^����
            bullets[i].active = false;  // �e���A�N�e�B�u���i�����j
            break;  // 1����������
        }
    }
}

// �{�X�ƒe�̏Փ˂𔻒肷��֐��i�~�Ƌ�`�̊ȈՏՓ˔���j
bool CheckBossHit(float bulletX, float bulletY, float bulletRadius)
{
    if (!g_IsBossAlive) return false;

    int bossX = boss.x+150;
    int bossY = boss.y+75;

    // �{�X�摜�T�C�Y���g�p
    int bossWidth = boss.width;
    int bossHeight = boss.height-100;

    float closestX = (float)(bulletX < bossX ? bossX : (bulletX > bossX + bossWidth ? bossX + bossWidth : bulletX));
    float closestY = (float)(bulletY < bossY ? bossY : (bulletY > bossY + bossHeight ? bossY + bossHeight : bulletY));

    float dx = bulletX - closestX;
    float dy = bulletY - closestY;

    return (dx * dx + dy * dy) <= (bulletRadius * bulletRadius);
}
