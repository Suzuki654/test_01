//=============================================================================
//
//UIの処理実装ファイル[ui.cpp]
//Author:鈴木哲汰
//
//=============================================================================
#include "ui.h"
#include "player.h"
#include "game.h"
#include "tutorial.h"
#include "sound.h"
//マクロ定義
#define NUM_UI (UI_TEX_MAX)//UIの数


//グローバル変数
LPDIRECT3DTEXTURE9 g_apTextureUI[NUM_UI] = {};//テクスチャーへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffUI = NULL;//頂点バッファ
int g_nPatternUI = 0;
//=============================================================================
//UIの初期化処理
//=============================================================================
void InitUI(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//全体の頂点バッファ
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * NUM_UI,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffUI,
		NULL
	);
	
}
//=============================================================================
//UIの終了処理
//=============================================================================
void UninitUI(void)
{
	for (int nCntUI = 0; nCntUI < NUM_UI; nCntUI++)
	{
		if (g_apTextureUI[nCntUI] != NULL)
		{
			g_apTextureUI[nCntUI]->Release();
			g_apTextureUI[nCntUI] = NULL;
		}
	}

	if (g_pVtxBuffUI != NULL)
	{
		g_pVtxBuffUI->Release();
		g_pVtxBuffUI = NULL;
	}
}
//=============================================================================
//UIの更新処理
//=============================================================================
void UpdateUI(void)
{
	
}
//=============================================================================
//UIの描画処理
//=============================================================================
void DrawUI(void)
{
	
}
