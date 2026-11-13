//=============================================================================
//
//リザルト画面の処理実装ファイル[result.cpp]
//Author:鈴木哲汰
//
//=============================================================================
#include "result.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "bg.h"
#include "score.h"
#include "ranking.h"

#define NUM_RESULT (9)//リザルトの画像の数

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureResult[NUM_RESULT] = {};//テクスチャーへのポインター
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;//頂点バッファへのポインタ
int g_nResultScore = 0;
bool g_PushResult = false;
//=============================================================================
//リザルト画面の初期化
//=============================================================================
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();
	//テクスチャーの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\BG02.png",
		&g_pTextureResult[0]);
	//テクスチャーの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\BG02_02.png",
		&g_pTextureResult[1]);
	//テクスチャーの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Result_Title.png",
		&g_pTextureResult[2]);
	//テクスチャーの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\You.png",
		&g_pTextureResult[3]);
	//テクスチャーの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Ranking.png",
		&g_pTextureResult[4]);
	//テクスチャーの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\push_button.png",
		&g_pTextureResult[5]);
	//テクスチャーの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\No.1.png",
		&g_pTextureResult[6]);
	//テクスチャーの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\No.2.png",
		&g_pTextureResult[7]);
	//テクスチャーの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\No.3.png",
		&g_pTextureResult[8]);

	g_PushResult = false;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4 * NUM_RESULT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL);

	//リザルト用のスコアを初期化
	InitScore();
	//保存していたスコアを設定
	SetScore(g_nResultScore);
	//スコアの表示位置初期化
	SetScorePosition(500.0f, 220.0f);
	// ランキング初期化
	InitRanking();
	// 今回のスコアをランキングに追加
	AddRanking(g_nResultScore);

	g_nResultScore = 0;

	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点データポインタを取得
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntResult = 0; nCntResult < NUM_RESULT; nCntResult++)
	{
		if (nCntResult == 0)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
		}
		if (nCntResult == 1)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(GAME_BG_LEFT, GAME_BG_TOP, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(GAME_BG_RIGHT, GAME_BG_TOP, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(GAME_BG_LEFT, GAME_BG_UNDER, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(GAME_BG_RIGHT, GAME_BG_UNDER, 0.0f);
		}
		if (nCntResult == 2)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(438.0f, 50.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(838.0f, 50.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(438.0f, 150.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(838.0f, 150.0f, 0.0f);
		}
		if (nCntResult == 3)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(400.0f, 160.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(500.0f, 160.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(400.0f, 200.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(500.0f, 200.0f, 0.0f);
		}
		if (nCntResult == 4)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(438.0f, 250.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(838.0f, 250.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(438.0f, 350.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(838.0f, 350.0f, 0.0f);
		}
		if (nCntResult == 5)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(950.0f, 600.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(1250.0f, 600.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(950.0f, 700.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1250.0f, 700.0f, 0.0f);
		}
		if (nCntResult == 6)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(400.0f, 360.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(505.0f, 360.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(400.0f, 430.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(505.0f, 430.0f, 0.0f);
		}
		if (nCntResult == 7)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(420.0f, 440.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(500.0f, 440.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(420.0f, 490.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(500.0f, 490.0f, 0.0f);
		}
		if (nCntResult == 8)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(430.0f, 510.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(500.0f, 510.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(430.0f, 550.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(500.0f, 550.0f, 0.0f);
		}


		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//頂点カラーの設定
		pVtx[0].Col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].Col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].Col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].Col = D3DCOLOR_RGBA(255, 255, 255, 255);
		//テクスチャー座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffResult->Unlock();
	
}
//=============================================================================
//リザルト画面の終了処理
//=============================================================================
void UninitResult(void)
{
	//サウンドの停止
	StopSound();
	//ランキング終了処理
	UninitRanking();
	//スコア終了処理
	UninitScore();

	//テクスチャーの破棄
	int nCntResult;
	for (nCntResult = 0; nCntResult < NUM_RESULT; nCntResult++)
	{
		//テクスチャーの破棄
		if (g_pTextureResult[nCntResult] != NULL)
		{
			g_pTextureResult[nCntResult]->Release();
			g_pTextureResult[nCntResult] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}
}
//=============================================================================
//リザルト画面の更新処理
//=============================================================================
void UpdateResult(void)
{
	if (g_PushResult == false)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true || GetKeyboardTrigger(DIK_SPACE) == true || GetJoypadTrigger(JOYKEY_A) == true)
		{//決定キー(ENTER)が押された
			//モード設定(ゲーム画面に移動)
			SetFade(MODE_TITLE);
			g_PushResult = true;
			
		}
	}
	
}
//=============================================================================
//リザルト画面の描画処理
//=============================================================================
void DrawResult(void)
{

	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_2D);
	for (int nCntResult = 0; nCntResult < NUM_RESULT; nCntResult++)
	{
		//テクスチャーの設定
		pDevice->SetTexture(0, g_pTextureResult[nCntResult]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntResult * 4, 2);
	}
	//スコアの描画処理
	DrawScore();
	//ランキングの描画処理
	DrawRanking();

}
//=============================================================================
//リザルトスコア設定
//=============================================================================
void SetResultScore(int nScore)
{
	g_nResultScore = nScore;
}