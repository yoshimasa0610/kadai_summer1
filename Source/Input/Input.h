#pragma once

// ���̓{�^����`
enum InputKey
{
	KEY_UP = (1 << 0),	// 0x0000 0001
	KEY_DOWN = (1 << 1),	// 0x0000 0010
	KEY_LEFT = (1 << 2), // 0x0000 0100
	KEY_RIGHT = (1 << 3), // 0x0000 1000
	KEY_Z = (1 << 4), // 0x0001 0000
};

// �֐��̃v���g�^�C�v�錾 
void InitInput();
void UpdateInput();
void DrawInput();
void FinInput();

bool IsInputKey(InputKey key);		// �L�[���͔���
bool IsTriggerKey(InputKey key);	// �L�[�������u�Ԕ���


