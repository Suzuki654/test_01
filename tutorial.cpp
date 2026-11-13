//=============================================================================
//
//チュートリアル画面の処理実装ファイル[tutorial.cpp]
//Author:鈴木哲汰
//
//=============================================================================
#include "tutorial.h"
#include "player.h"
#include "bg.h"
#include "input.h"
#include "score.h"
#include "effect.h"
#include "sound.h"
#include "fade.h"
#include "ui.h"
#include "game.h"

//マクロ定義
#define NUM_TUTORIAL (1)        //タイトルの画像の数

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureTutorial[NUM_TUTORIAL] = {};//テクスチャーへのポインター
LPDIRECT3DTEXTURE9 g_pTextureTutorialSuccess = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;//頂点バッファへのポインタ
bool g_bTutorialPause = false;//ポーズ状態のON/OFF
bool g_bTutorialDispDebug = false;//デバック表示のON/OFF
//=============================================================================
//チュートリアル画面の初期化処理
//=============================================================================
void InitTutorial(void)
{
	int nCntTutorial;
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();
	//テクスチャーの読み込み
	D3DXCreateTextureFromFile
	(pDevice,
		"data\\TEXTURE\\Background\\BG02.png",
		&g_pTextureTutorial[0]);


	//頂点バッファの生成
	pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4 * NUM_TUTORIAL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorial,
		NULL);

	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点データポインタを取得
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTutorial = 0; nCntTutorial < NUM_TUTORIAL; nCntTutorial++)
	{

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

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

	//頂点バッファをあんろっくする
	g_pVtxBuffTutorial->Unlock();

}
//=============================================================================
//チュートリアル画面の終了処理
//=============================================================================
void UninitTutorial(void)
{
	int nCntTutorial;
	for (nCntTutorial = 0; nCntTutorial < NUM_TUTORIAL; nCntTutorial++)
	{
		//テクスチャーの破棄
		if (g_pTextureTutorial[nCntTutorial] != NULL)
		{
			g_pTextureTutorial[nCntTutorial]->Release();
			g_pTextureTutorial[nCntTutorial] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffTutorial != NULL)
	{
		g_pVtxBuffTutorial->Release();
		g_pVtxBuffTutorial = NULL;
	}
}
//=============================================================================
//チュートリアル画面の更新処理
//=============================================================================
void UpdateTutorial(void)
{
	if (GetKeyboardTrigger(DIK_SPACE) || GetKeyboardTrigger(DIK_RETURN) || GetJoypadTrigger(JOYKEY_A))
	{

		//スタート
		SetFade(MODE_GAME);

	}
}
//=============================================================================
//チュートリアル画面の描画処理
//=============================================================================
void DrawTutorial(void)
{
	int nCntTutorial;
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTutorial, 0, sizeof(VERTEX_2D));

	//頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_2D);



	for (nCntTutorial = 0; nCntTutorial < NUM_TUTORIAL; nCntTutorial++)
	{
		//テクスチャーの設定
		pDevice->SetTexture(0, g_pTextureTutorial[nCntTutorial]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTutorial * 4, 2);
	}

}

