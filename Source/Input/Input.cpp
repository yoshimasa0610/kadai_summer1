#include "DxLib.h"
#include "Input.h"

// ���̓t���O
int g_InputState = 0;
// �O��̓���
int g_PrevInputState = 0;

void InitInput()
{
	g_InputState = 0;
	g_PrevInputState = 0;
}

void UpdateInput()
{
	// �O��̓��͂��o���Ă���
	g_PrevInputState = g_InputState;

	// ���͏�Ԃ��N���A
	g_InputState = 0;

	// ���͏�Ԃ��r�b�g�t���O�Őݒ�
	if (CheckHitKey(KEY_INPUT_W))
	{
		g_InputState |= KEY_UP;
	}
	if (CheckHitKey(KEY_INPUT_S))
	{
		g_InputState |= KEY_DOWN;
	}
	if (CheckHitKey(KEY_INPUT_A))
	{
		g_InputState |= KEY_LEFT;
	}
	if (CheckHitKey(KEY_INPUT_D))
	{
		g_InputState |= KEY_RIGHT;
	}
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		g_InputState |= KEY_Z;
	}
}

void DrawInput()
{
}

void FinInput()
{
}

bool IsInputKey(InputKey key)
{
	return g_InputState & key;
}

bool IsTriggerKey(InputKey key)
{
	return (g_InputState & key) && !(g_PrevInputState & key);
}