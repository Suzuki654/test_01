//=============================================================================
//
//ゲーム画面の処理実装ファイル[game.cpp]
//Author:鈴木哲汰
//
//=============================================================================
#include "game.h"
#include "player.h"
#include "bg.h"
#include "input.h"
//#include "bullet.h"
//#include "explosion.h"
//#include "enemy.h"
#include "score.h"
#include "effect.h"
#include "sound.h"
#include "fade.h"
//#include "gun.h"
#include "ui.h"
//#include "laser.h"
//#include "boss.h"
#include "result.h"

//マクロ定義
#define WAVE_WAIT_TIME (120) //ウェーブ間待ち時間
#define GAMEEND_WAIT_TIME (60) //ゲームオーバー後待ち時間
#define GAMECLEAR_WAIT_TIME (180) //ゲームクリア後待ち時間

//プロトタイプ宣言
void SetGameWave(int nWave, int nPhase);

//グローバル変数
bool g_bPause = false;//ポーズ状態のON/OFF
bool g_bDispDebug = false;//デバック表示のON/OFF

//=============================================================================
//ゲーム画面の初期化処理
//=============================================================================
void InitGame(void)
{
	//BGの初期化処理
	InitBG();
	//プレイヤーの初期化処理
	InitPlayer();
	
	//スコアの初期化処理
	InitScore();
	//UIの初期化処理
	InitUI();

	g_bPause = false;
	
	
}
//=============================================================================
//ゲーム画面の終了処理
//=============================================================================
void UninitGame(void)
{
	//サウンドの停止
	StopSound();
	//BGの終了処理
	UninitBG();
	//プレイヤーの終了処理
	UninitPlayer();
	
	//スコアの終了処理
	UninitScore();
	//UIの終了処理
	UninitUI();
}
//=============================================================================
//ゲーム画面の更新処理
//=============================================================================
void UpdateGame(void)
{

	//ポーズ処理
	if (g_bPause == false)
	{

		//BGの更新処理
		UpdateBG();
		//プレイヤーの更新処理
		UpdatePlayer();
		
		//スコアの更新処理
		UpdateScore();
		//UIの更新処理
		UpdateUI();

	}
	if (GetKeyboardTrigger(DIK_P) || GetKeyboardTrigger(DIK_ESCAPE) || GetJoypadTrigger(JOYKEY_START))
	{   //Pキーを押した
		g_bPause = !g_bPause;
		
	}

}

//=============================================================================
//ゲーム画面の描画処理
//=============================================================================
void DrawGame(void)
{
	//BGの描画処理
	DrawBG();
	//プレイヤーの描画処理
	DrawPlayer();
	//スコアの描画処理
	SetScorePosition(960.0f, 50.0f);//場所
	DrawScore();
	//UIの描画処理
	DrawUI();


}
//=============================================================================
//ゲームのウェーブ処理
//=============================================================================
void SetGameWave(int nWave, int nPhase)
{

}

