
extern bool g_IsBossAlive; // �錾�̂�

// ���̊֐��錾...

void InitBossEnemy();
void StartBossEnemy();
void UpdateBossEnemy();
void DrawBossEnemy();
void DeleteBossEnemy();
bool IsBossDefeated();
void DamageBoss(int damage);
bool CheckBossHit(float bulletX, float bulletY, float bulletRadius);
void CheckBossCollisionWithPlayerBullets();
