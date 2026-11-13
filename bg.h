//=============================================================================
//
//背景を管理するクラスの宣言[bg.h]
//Author:鈴木哲汰
//
//=============================================================================
#ifndef _BG_H_
#define _BG_H_ //二重インクルード防止のマクロ

#include "main.h"
//マクロ定義
#define GAME_BG_RIGHT (900.0f)//ゲーム画面右
#define GAME_BG_LEFT (376.0f)//ゲーム画面左
#define GAME_BG_TOP (0.0f)//ゲーム画面上
#define GAME_BG_UNDER (720.0f)//ゲーム画面下
#define BORDEA_BG_RIGHT (970.0f)//ボーダー右
#define BORDEA_BG_LEFT (306.0f)//ボーダー左
#define BORDEA_BG_TOP (-100.0f)//ボーダー上
#define BORDEA_BG_UNDER (820.0f)//ボーダー下

//プロトタイプ宣言
void InitBG(void);
void UninitBG(void);
void UpdateBG(void);
void DrawBG(void);

#endif // !_BG_H_

