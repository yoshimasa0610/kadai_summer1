
//プレイヤーサイズ
#define PLAYER_WIDTH    (100.0f)
#define PLAYER_HEIGHT	(100.0f)
#define PLAYER_RADIUS	(50.0f)

struct PlayerData
{
	bool active;
	bool invisible;
	int handle;
	int respawnTimer;			// リスポーン待機タイマー
	int invisibleTimer;			// 無敵時間タイマー
	int life;					// 残機数
	float posX;					// X座標
	float posY;					// Y座標
	float moveX;				// X移動量
	float moveY;				// Y移動量
	int bulletIntervalTimer;	// 弾の発射間隔タイマー
};

//関数（仮）
void InitPlayer();
void LoadPlayer();
void StartPlayer();
void StepPlayer();
void UpdatePlayer();
void DrawPlayer();
void FinPlayer();

// 取得関数
PlayerData* GetPlayer();
