#include "DxLib.h"
#include "../SceneManager.h"
#include "../../BackGround/BackGround.h"
#include "../../Player/Player.h"
#include "../../Input/Input.h"
#include "../../GameSetting/GameSetting.h"
#include "../../Bullet/BulletManager.h"
#include "../../Enemy/Enemy.h"
#include "../../Boss Enemy/BossEnemy.h"

// �w�i�̃X�s�[�h
#define BACK_GROUND_SPEED (-1.5f)

void InitPlayScene()
{
	// �w�i������
	InitBackGround();

	// �v���C���[������
	InitPlayer();

	// �G�l�~�[������
	InitEnemy();

	InitBossEnemy();

	// �e��������
	InitBullet();

}

void LoadPlayScene()
{
	// �v���C���[���[�h
	LoadPlayer();

	// �e���[�h
	LoadBullet();

}

void StartPlayScene()
{
	// �v���C���[�J�n
	StartPlayer();

	StartBossEnemy();

}

void StepPlayScene()
{

	// �v���C���[�X�e�b�v
	StepPlayer();

	// �e�X�e�b�v
	StepBullet();

}

void UpdatePlayScene()
{
	// �w�i�X�V
	UpdateBackGround();

	// �v���C���[�X�V
	UpdatePlayer();

	// �G�l�~�[�X�V
	UpdateEnemy();

	UpdateBossEnemy();

	// �e�X�V
	UpdateBullet();

	if (!g_IsBossAlive && IsBossDefeated())
	{
		ChangeScene(SCENE_GAME_CLEAR);
	}

	
}

void DrawPlayScene()
{
	// �w�i�`��
	DrawBackGround();

	// �e�`��
	DrawBullet();

	// �G�l�~�[�`��
	DrawEnemy();

	DrawBossEnemy();

	// �v���C���[�`��
	DrawPlayer();


}

void FinPlayScene()
{
	// �w�i�I��
	FinBackGround();

	// �v���C���[�I��
	FinPlayer();

	DeleteBossEnemy();

	// �e�I��
	FinBullet();
}
