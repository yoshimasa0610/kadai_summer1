#include "DxLib.h"
#include "GameSetting/GameSetting.h"
#include "Input/Input.h"
#include "Scene/SceneManager.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	// ウィンドウモードON
	ChangeWindowMode(TRUE);

	// 画面解像度の設定
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_COLOR_DEPTH);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	// ウィンドウサイズ設定
	SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	// 透過色の設定
	SetTransColor(TRANS_COLOR_R, TRANS_COLOR_G, TRANS_COLOR_B);

	// 描画先を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);

	// 入力システムを初期化
	InitInput();

	float m_Time = 0.0f;
	// ゲームのメインループ
	while (ProcessMessage() >= 0)
	{
		//StartFrame
		{
			m_Time = GetNowCount();
		}

		// 画面をクリア
		ClearDrawScreen();

		// 入力を更新
		UpdateInput();

		// シーン管理の更新
		SceneManagerUpdate();

		// 入力システムの描画
		DrawInput();

		// エスケープキーで終了
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;
		{

		}

		//WaitFrame()
		{
			int before = m_Time;
			int after = GetNowCount();
			int interval = (int)((1000 / 1000) - (after - before));
			if (interval > 0) { WaitTimer(interval); }
		}

		// 画面フリップ
		ScreenFlip();
	}

	// 入力システムの終了
	FinInput();


	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}
