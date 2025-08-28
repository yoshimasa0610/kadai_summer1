#include "DxLib.h"
#include "BossEnemy.h"
#include "../Enemy/Enemy.h"
#include "../Bullet/Bullet.h"
#include "../Bullet/BulletManager.h"
#include "../Collision/BulletCollision.h"
#
// ==== 外部変数 ====
bool g_IsBossAlive = false;

// ==== 内部クラス ====
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
    g_BossSpawnedOnce = false;   // 追加：2回目以降も出現できるように
    boss.Finalize();             // 古い画像や状態をクリア
}

void StartBossEnemy()
{
    boss.Initialize();  // HPや位置、isAlive を初期化
}

void UpdateBossEnemy()
{
    if (!g_IsBossAlive)
    {
        if (!g_BossSpawnedOnce) // 初回出現か？
        {
            g_BossSpawnTimer++;
            if (g_BossSpawnTimer >= BOSS_APPEAR_TIME) {
                boss.Initialize();
                g_IsBossAlive = true;
                g_BossSpawnedOnce = true; // 以降は出現させない
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

    // ==== 画像サイズを取得 ====
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

    const int bossHeight = 375; // ボス画像の高さ

    // 上端で反転
    if (y < 0) {
        y = 0;    // 上端に合わせる
        dir = 1;  // 下方向に
    }

    // 下端で反転
    else if (y > 900 - bossHeight) {
        y = 900 - bossHeight; // 下端に合わせる
        dir = -1;             // 上方向に
    }
}

void BossEnemy::Shoot() 
{
    if (--shotTimer <= 0) 
    {
        FireBullet();  // ボスが弾を発射

        shotTimer = shotInterval;
    }
}

void BossEnemy::FireBullet() 
{
    FireBulletData fireData;

    // ボスの弾を画面中央に向けて発射する例
    fireData.posX = (float)(x + 300); // ボスの中心付近
    fireData.posY = (float)(y + 170); // ボスの中心付近
    fireData.moveX = -5.0f;           // 左向き
    fireData.moveY = 0.0f;            // 垂直方向なし
    fireData.life = 400;               // 弾の寿命（例）

    // ボス弾の発射（STRAIGHT_BULLET_TYPE_ENEMY_NORMAL）
    FireStraightBullet(STRAIGHT_BULLET_TYPE_BOSS, fireData, BULLET_COLLISION_TAG_ENEMY);

}

void BossEnemy::Draw()
{
    if (!isAlive) return;

    // 画像描画
    DrawGraph(x, y, image, TRUE);

    // HPバー
    int barWidth = 400;
    int hpWidth = (int)((double)hp / maxHp * barWidth);
    int barX = (1600 - barWidth) / 2;
    DrawBox(barX, 20, barX + barWidth, 40, GetColor(80, 80, 80), TRUE);
    DrawBox(barX, 20, barX + hpWidth, 40, GetColor(255, 0, 0), TRUE);

    // ==== 当たり判定の可視化 ====
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
    StraightBulletData* bullets = GetStraightBullet();  // 弾の配列を取得

    for (int i = 0; i < STRAIGHT_BULLET_MAX; i++) 
    {
        if (!bullets[i].active) continue;  // 弾がアクティブでない場合はスキップ
        if (bullets[i].tag != BULLET_COLLISION_TAG_PLAYER) continue;  // プレイヤーの弾かどうかをチェック

        float bx = bullets[i].posX + bullets[i].radius;  // 弾の中心位置（X）
        float by = bullets[i].posY + bullets[i].radius;  // 弾の中心位置（Y）
        float br = bullets[i].radius;  // 弾の半径

        if (CheckBossHit(bx, by, br)) {  // ボスと弾の衝突を判定
            DamageBoss(1);  // ボスにダメージを与える
            bullets[i].active = false;  // 弾を非アクティブ化（消去）
            break;  // 1発だけ処理
        }
    }
}

// ボスと弾の衝突を判定する関数（円と矩形の簡易衝突判定）
bool CheckBossHit(float bulletX, float bulletY, float bulletRadius)
{
    if (!g_IsBossAlive) return false;

    int bossX = boss.x+150;
    int bossY = boss.y+75;

    // ボス画像サイズを使用
    int bossWidth = boss.width;
    int bossHeight = boss.height-100;

    float closestX = (float)(bulletX < bossX ? bossX : (bulletX > bossX + bossWidth ? bossX + bossWidth : bulletX));
    float closestY = (float)(bulletY < bossY ? bossY : (bulletY > bossY + bossHeight ? bossY + bossHeight : bulletY));

    float dx = bulletX - closestX;
    float dy = bulletY - closestY;

    return (dx * dx + dy * dy) <= (bulletRadius * bulletRadius);
}
