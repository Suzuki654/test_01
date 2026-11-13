//=============================================================================
//
//タイトル画面の処理実装ファイル[title.cpp]
//Author:鈴木哲汰
//
//=============================================================================
#include "title.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "bg.h"
#include "score.h"

#define NUM_TITLE (1)//タイトルの画像の数
//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureTitle[NUM_TITLE] = {};//テクスチャーへのポインター
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;//頂点バッファへのポインタ
int g_nSelectTitle = 0;// 0 = スタート// 1 = 終わる
int g_nTitleBlinkCount = 0;
bool g_nPushTitle = false;
//=============================================================================
//タイトル画面の初期化
//=============================================================================
void InitTitle(void)
{
	int nCntTitle;
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();
	//テクスチャーの読み込み
	D3DXCreateTextureFromFile
	(pDevice,
		"data\\TEXTURE\\Background\\BG01.png",
		&g_pTextureTitle[0]);



	g_nPushTitle = false;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer
	(sizeof(VERTEX_2D) * 4 * NUM_TITLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点データポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTitle = 0; nCntTitle < NUM_TITLE; nCntTitle++)
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
	g_pVtxBuffTitle->Unlock();


}
//=============================================================================
//タイトル画面の終了処理
//=============================================================================
void UninitTitle(void)
{
	//サウンドの停止
	StopSound();
	int nCntTitle;
	for (nCntTitle = 0; nCntTitle < NUM_TITLE; nCntTitle++)
	{
		//テクスチャーの破棄
		if (g_pTextureTitle[nCntTitle] != NULL)
		{
			g_pTextureTitle[nCntTitle]->Release();
			g_pTextureTitle[nCntTitle] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}
}
//=============================================================================
//タイトル画面の更新処理
//=============================================================================
void UpdateTitle(void)
{
	if (GetKeyboardTrigger(DIK_SPACE) || GetKeyboardTrigger(DIK_RETURN) || GetJoypadTrigger(JOYKEY_A))
	{

		//スタート
		SetFade(MODE_TUTORIAL);

	}

}
//=============================================================================
//タイトル画面の描画処理
//=============================================================================
void DrawTitle(void)
{
	int nCntTitle;
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_2D);



	for (nCntTitle = 0; nCntTitle < NUM_TITLE; nCntTitle++)
	{
		//テクスチャーの設定
		pDevice->SetTexture(0, g_pTextureTitle[nCntTitle]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTitle * 4, 2);
	}

}