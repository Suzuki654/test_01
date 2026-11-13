//=============================================================================
//
//ゲーム画面を管理するクラスの宣言[game.h]
//Author:鈴木哲汰
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_
#include"main.h"


//プロトタイプ宣言
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
//グローバル変数
extern int g_nGameEndSelect;
#endif // !_GAME_H_

