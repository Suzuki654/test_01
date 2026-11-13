//=============================================================================
//
//入力の処理実装ファイル[input.cpp]
//Author:鈴木哲汰
//
//=============================================================================
#include "input.h"
//マクロ定義
#define NUM_KEY_MAX (256)//キーの最大数
#define NUM_JOYKEY_MAX (16)//ジョイパッドのキー
#define JOY_STICK_DEADZONE (8000)//デットゾーン

//グローバル変数
LPDIRECTINPUT8 g_pInput = NULL;//DirectInputオブジェクトのポインタ
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;//入力デバイスのポインタ
BYTE g_aKeyState[NUM_KEY_MAX];//キーボードのプレス情報
BYTE g_aKeyStateTrigger[NUM_KEY_MAX];//キーボードのトリガー情報
BYTE g_aKeyStateRelease[NUM_KEY_MAX];//キーボードのリリース情報
BYTE g_aKeyStateRepeat[NUM_KEY_MAX];//キーボードのリピート情報
int g_aKeyRepeatCount[NUM_KEY_MAX] = {};   // リピート用カウンタ
XINPUT_STATE g_JoykeyState;//ジョイパッドのプレス情報
XINPUT_STATE g_JoykeyStateTrigger;//ジョイパッドのトリガー情報
XINPUT_STATE g_JoykeyStateRelease;//ジョイパッドのリリース情報
XINPUT_STATE g_JoykeyStateRepeat;//ジョイパッドのリピート情報
int g_aJoykeyRepeatCount[NUM_JOYKEY_MAX] = {};
int g_nStickUpRepeatCount = 0;
int g_nStickDownRepeatCount = 0;
SHORT g_nOldStickY = 0;
//=============================================================================
//キーボードの初期化処理
//=============================================================================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInputオブジェクトの生成
	if (FAILED(DirectInput8Create(hInstance,DIRECTINPUT_VERSION,IID_IDirectInput8,(void**)&g_pInput,NULL)))
	{
		return E_FAIL;
	}

	//入力デバイスの生成
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard,&g_pDevKeyboard,NULL)))
	{
		return E_FAIL;
	}
	
	//データフォーマット
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//協調モードを設定
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd,(DISCL_FOREGROUND|DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	
	//キーボードへのアクセス権を獲得
	g_pDevKeyboard->Acquire();

	return S_OK;
}
//=============================================================================
//キーボードの終了処理
//=============================================================================
void UninitKeyboard(void)
{
	//入力デバイスの破棄
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();//キーボードへのアクセス権を放棄
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	//DirectInputオブジェクトの破棄
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}
//=============================================================================
//キーボードの更新処理
//=============================================================================
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];//キーボードの入力情報
	int nCntKey;
	
	//入力デバイスからデータを取得
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState),&aKeyState[0])))
	{
		for (nCntKey = 0;  nCntKey < NUM_KEY_MAX ; nCntKey++)
		{
			g_aKeyStateTrigger[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];//キーボードのトリガー情報を保存
			g_aKeyStateRelease[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & g_aKeyState[nCntKey];//キーボードのリリース情報を保存
			
			if (aKeyState[nCntKey] & 0x80)
			{
				g_aKeyRepeatCount[nCntKey]++;

				if (g_aKeyRepeatCount[nCntKey] == 1)
				{
					// 最初の1回
					g_aKeyStateRepeat[nCntKey] = 0x80;
				}
				else if (g_aKeyRepeatCount[nCntKey] > 20 && (g_aKeyRepeatCount[nCntKey] % 5) == 0)
				{
					// 20フレーム後から5フレームごと
					g_aKeyStateRepeat[nCntKey] = 0x80;
				}
				else
				{
					g_aKeyStateRepeat[nCntKey] = 0;
				}
			}
			else
			{
				g_aKeyRepeatCount[nCntKey] = 0;
				g_aKeyStateRepeat[nCntKey] = 0;
			}

			g_aKeyState[nCntKey] = aKeyState[nCntKey];//キーボードのプレス情報を保存
		}
	}
	else
	{
		g_pDevKeyboard->Acquire();//キーボードへのアクセス権を獲得
	}
}
//=============================================================================
//キーボードのプレス情報を取得
//=============================================================================
bool GetKeyboardPress(int nKey)
{
	return (g_aKeyState[nKey] & 0x80) ? true : false;
}
//=============================================================================
//キーボードのトリガー情報を取得
//=============================================================================
bool GetKeyboardTrigger(int nKey)
{
	return (g_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}
//=============================================================================
//キーボードのリリース情報を取得
//=============================================================================
bool GetKeyboardRelease(int nKey)
{
	return (g_aKeyStateRelease[nKey] & 0x80) ? true : false;
}
//=============================================================================
//キーボードのリピート情報を取得
//=============================================================================
bool GetKeyboardRepeat(int nKey)
{
	return (g_aKeyStateRepeat[nKey] & 0x80) ? true : false;
}
//=============================================================================
//ジョイパッドの初期化処理
//=============================================================================
HRESULT InitJoypad(void)
{
	//メモリのクリア
	memset(&g_JoykeyState, 0, sizeof(XINPUT_STATE));

	//xinputのステート設定（有効にする）
	XInputEnable(true);

	return S_OK;
}
//=============================================================================
//ジョイパッドの終了処理
//=============================================================================
void UninitJoypad(void)
{
	//xInoutのステートを設定（無効にする）
	XInputEnable(false);
}
//=============================================================================
//ジョイパッドの更新処理
//=============================================================================
void UpdateJoypad(void)
{
	XINPUT_STATE JoykeyState;//ジョイパッドの入力情報
	int nCntKey;

	// 現在の状態を保存
	g_nOldStickY = g_JoykeyState.Gamepad.sThumbLY;

	// ジョイパッドの状態を取得
	if (XInputGetState(0, &JoykeyState) == ERROR_SUCCESS)
	{
		//トリガー
		g_JoykeyStateTrigger.Gamepad.wButtons =(g_JoykeyState.Gamepad.wButtons ^JoykeyState.Gamepad.wButtons) &JoykeyState.Gamepad.wButtons;
		//リリース
		g_JoykeyStateRelease.Gamepad.wButtons =(g_JoykeyState.Gamepad.wButtons ^JoykeyState.Gamepad.wButtons) &g_JoykeyState.Gamepad.wButtons;
		//リピート
		g_JoykeyStateRepeat.Gamepad.wButtons = 0;

		for (nCntKey = 0; nCntKey < NUM_JOYKEY_MAX; nCntKey++)
		{
			WORD button = (WORD)(1 << nCntKey);

			if (JoykeyState.Gamepad.wButtons & button)
			{
				g_aJoykeyRepeatCount[nCntKey]++;

				if (g_aJoykeyRepeatCount[nCntKey] == 1)
				{
					g_JoykeyStateRepeat.Gamepad.wButtons |= button;
				}
				else if (g_aJoykeyRepeatCount[nCntKey] > 20 && (g_aJoykeyRepeatCount[nCntKey] % 5) == 0)
				{
					g_JoykeyStateRepeat.Gamepad.wButtons |= button;
				}
			}
			else
			{
				g_aJoykeyRepeatCount[nCntKey] = 0;
			}
		}

		// 現在の状態を保存
		g_JoykeyState = JoykeyState;
		
	}
}
//=============================================================================
//ジョイパッドのプレス情報取得
//=============================================================================
bool GetJoypadPress(JOYKEY key)
{
	return (g_JoykeyState.Gamepad.wButtons & key) ? true : false;
}
//=============================================================================
// ジョイパッドのトリガー情報取得
//=============================================================================
bool GetJoypadTrigger(JOYKEY key)
{
	return (g_JoykeyStateTrigger.Gamepad.wButtons & key) ? true : false;
}
//=============================================================================
// ジョイパッドのリリース情報取得
//=============================================================================
bool GetJoypadRelease(JOYKEY key)
{
	return (g_JoykeyStateRelease.Gamepad.wButtons & key) ? true : false;
}
//=============================================================================
// ジョイパッドのリピート情報取得
//=============================================================================
bool GetJoypadRepeat(JOYKEY key)
{
	return (g_JoykeyStateRepeat.Gamepad.wButtons & key) ? true : false;

}
//=============================================================================
// ジョイパッドの左スティックX取得
//=============================================================================
SHORT GetJoypadLeftStickX(void)
{
	SHORT Value = g_JoykeyState.Gamepad.sThumbLX;

	//デットゾーンで小さい数字を排除
	if (Value > -JOY_STICK_DEADZONE && Value < JOY_STICK_DEADZONE)
	{
		Value = 0;
	}

	return Value;
}
//=============================================================================
// ジョイパッドの左スティックY取得
//=============================================================================
SHORT GetJoypadLeftStickY(void)
{
	SHORT value = g_JoykeyState.Gamepad.sThumbLY;

	//デットゾーンで小さい数字を排除
	if (value > -JOY_STICK_DEADZONE && value < JOY_STICK_DEADZONE)
	{
		value = 0;
	}

	return value;
}
//=============================================================================
// ジョイパッドの左スティックYのトリガー処理（上）
//=============================================================================
bool GetJoypadLeftStickUpTrigger(void)
{
	SHORT stickY = GetJoypadLeftStickY();

	if (g_nOldStickY <= 8000 && stickY > 8000)
	{
		return true;
	}

	return false;
}
//=============================================================================
// ジョイパッドの左スティックYのトリガー処理（下）
//=============================================================================
bool GetJoypadLeftStickDownTrigger(void)
{
	SHORT stickY = GetJoypadLeftStickY();

	if (g_nOldStickY >= -8000 && stickY < -8000)
	{
		return true;
	}

	return false;
}
//=============================================================================
// ジョイパッドの左スティックYのリピート処理（上）
//=============================================================================
bool GetJoypadLeftStickUpRepeat(void)
{
	SHORT stickY = GetJoypadLeftStickY();

	if (stickY > 8000)
	{
		g_nStickUpRepeatCount++;

		// 最初の1回
		if (g_nStickUpRepeatCount == 1)
		{
			return true;
		}
		// 20フレーム後から5フレームごと
		else if (g_nStickUpRepeatCount > 20 &&
			(g_nStickUpRepeatCount % 5) == 0)
		{
			return true;
		}
	}
	else
	{
		// スティックを離したらリセット
		g_nStickUpRepeatCount = 0;
	}

	return false;
}
//=============================================================================
// ジョイパッドの左スティックYのリピート処理（下）
//=============================================================================
bool GetJoypadLeftStickDownRepeat(void)
{
	SHORT stickY = GetJoypadLeftStickY();

	if (stickY < -8000)
	{
		g_nStickDownRepeatCount++;

		// 最初の1回
		if (g_nStickDownRepeatCount == 1)
		{
			return true;
		}
		// 20フレーム後から5フレームごと
		else if (g_nStickDownRepeatCount > 20 &&
			(g_nStickDownRepeatCount % 5) == 0)
		{
			return true;
		}
	}
	else
	{
		// スティックを離したらリセット
		g_nStickDownRepeatCount = 0;
	}

	return false;
}