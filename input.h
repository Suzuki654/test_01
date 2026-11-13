//=============================================================================
//
//入力を管理するクラスの宣言[input.h]
//Author:鈴木哲汰
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//ジョイパッドのキーの種類
typedef enum
{
	JOYKEY_UP = XINPUT_GAMEPAD_DPAD_UP,
	JOYKEY_DOWN = XINPUT_GAMEPAD_DPAD_DOWN,
	JOYKEY_LEFT = XINPUT_GAMEPAD_DPAD_LEFT,
	JOYKEY_RIGHT = XINPUT_GAMEPAD_DPAD_RIGHT,

	JOYKEY_START = XINPUT_GAMEPAD_START,
	JOYKEY_BACK = XINPUT_GAMEPAD_BACK,

	JOYKEY_LEFT_THUMB = XINPUT_GAMEPAD_LEFT_THUMB,
	JOYKEY_RIGHT_THUMB = XINPUT_GAMEPAD_RIGHT_THUMB,

	JOYKEY_LEFT_SHOULDER = XINPUT_GAMEPAD_LEFT_SHOULDER,
	JOYKEY_RIGHT_SHOULDER = XINPUT_GAMEPAD_RIGHT_SHOULDER,

	JOYKEY_A = XINPUT_GAMEPAD_A,
	JOYKEY_B = XINPUT_GAMEPAD_B,
	JOYKEY_X = XINPUT_GAMEPAD_X,
	JOYKEY_Y = XINPUT_GAMEPAD_Y,
}JOYKEY;

//プロトタイプ宣言
HRESULT InitKeyboard(HINSTANCE hIndtance, HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);
bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);
bool GetKeyboardRelease(int nKey);
bool GetKeyboardRepeat(int nKey);
HRESULT InitJoypad(void);
void UninitJoypad(void);
void UpdateJoypad(void);
bool GetJoypadPress(JOYKEY key);
bool GetJoypadTrigger(JOYKEY key);
bool GetJoypadRelease(JOYKEY key);
bool GetJoypadRepeat(JOYKEY key);
SHORT GetJoypadLeftStickX(void);
SHORT GetJoypadLeftStickY(void);
bool GetJoypadLeftStickUpTrigger(void);
bool GetJoypadLeftStickDownTrigger(void);
bool GetJoypadLeftStickUpRepeat(void);
bool GetJoypadLeftStickDownRepeat(void);

#endif // !_INPUT_H_

