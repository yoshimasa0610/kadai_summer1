
extern bool g_IsBossAlive; // éŒ¾‚Ì‚İ

// ‘¼‚ÌŠÖ”éŒ¾...

void InitBossEnemy();
void StartBossEnemy();
void UpdateBossEnemy();
void DrawBossEnemy();
void DeleteBossEnemy();
bool IsBossDefeated();
void DamageBoss(int damage);
bool CheckBossHit(float bulletX, float bulletY, float bulletRadius);
void CheckBossCollisionWithPlayerBullets();
