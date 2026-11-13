//=============================================================================
//
//背景の処理実装ファイル[bg.cpp]
//Author:鈴木哲汰
//
// NOTE : セイノがアサインしました
//=============================================================================
#include "player.h"
#include "bg.h"

//マクロ定義
#define NUM_BG (1)//背景の数
//グローバル変数
LPDIRECT3DTEXTURE9 g_apTextureBG[NUM_BG] = {};//テクスチャー三枚分へのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG = NULL;//頂点バッファ
float g_aTexV[NUM_BG];//テクスチャー座標の開始位置（V値）
//=============================================================================
//BGの初期化処理
//=============================================================================
void InitBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	int nCntBG;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャーの読み込み

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Background\\BG03.png",
		&g_apTextureBG[0]);


	//テクスチャ座標の開始位置（V値）の初期化
	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		g_aTexV[nCntBG] = 0.0f;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_BG,//必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBG,
		NULL);

	VERTEX_2D* pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		if (nCntBG == 0)
		{
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
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



		pVtx += 4;//頂点データのポインタを４つ分進める
	}


	//頂点バッファをあんろっくする
	g_pVtxBuffBG->Unlock();
}
//=============================================================================
//BGの終了処理
//=============================================================================
void UninitBG(void)
{
	int nCntBG;
	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		//テクスチャーの破棄
		if (g_apTextureBG[nCntBG] != NULL)
		{
			g_apTextureBG[nCntBG]->Release();
			g_apTextureBG[nCntBG] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffBG != NULL)
	{
		g_pVtxBuffBG->Release();
		g_pVtxBuffBG = NULL;
	}
}
//=============================================================================
//BGの更新処理
//=============================================================================
void UpdateBG(void)
{
	int nCntBG;

	//テクスチャー座標開始位置の更新
	g_aTexV[0] -= 0.0f;   // スクロール速度
	g_aTexV[1] -= 0.0f;   // スクロール速度
	g_aTexV[2] -= 0.01f;   // スクロール速度

	VERTEX_2D* pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		if (nCntBG == 0)
		{
			//テクスチャー座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}
		
		pVtx += 4;//頂点データのポインタを４つ分進める
	}
	//頂点バッファをあんろっくする
	g_pVtxBuffBG->Unlock();

}
//=============================================================================
//BGの描画処理
//=============================================================================
void DrawBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ
	int nCntBG;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBG, 0, sizeof(VERTEX_2D));

	//頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
	{
		//テクスチャーの設定
		pDevice->SetTexture(0, g_apTextureBG[nCntBG]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBG * 4, 2);
	}



}