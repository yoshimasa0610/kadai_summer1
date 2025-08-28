
//�v���C���[�T�C�Y
#define PLAYER_WIDTH    (100.0f)
#define PLAYER_HEIGHT	(100.0f)
#define PLAYER_RADIUS	(50.0f)

struct PlayerData
{
	bool active;
	bool invisible;
	int handle;
	int respawnTimer;			// ���X�|�[���ҋ@�^�C�}�[
	int invisibleTimer;			// ���G���ԃ^�C�}�[
	int life;					// �c�@��
	float posX;					// X���W
	float posY;					// Y���W
	float moveX;				// X�ړ���
	float moveY;				// Y�ړ���
	int bulletIntervalTimer;	// �e�̔��ˊԊu�^�C�}�[
};

//�֐��i���j
void InitPlayer();
void LoadPlayer();
void StartPlayer();
void StepPlayer();
void UpdatePlayer();
void DrawPlayer();
void FinPlayer();

// �擾�֐�
PlayerData* GetPlayer();
