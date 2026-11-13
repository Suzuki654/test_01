//=============================================================================
//
//エフェクトの処理実装ファイル[effect.cpp]
//Author:鈴木哲汰
//
//=============================================================================
#include"effect.h"
//マクロ定義
#define MAX_EFFECT (4096)//エフェクトの最大数
#define SIZE_EFFECT (50.0f)//弾の大きさ

//エフェクト構造体
typedef struct 
{
	D3DXVECTOR3 pos; //位置
	D3DXCOLOR col; //色
	float fRadius;//半径（大きさ）
	int nLife; //寿命
	bool bUse; //使用しているかどうか


}Effect;

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL;//テクスチャーへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;//頂点バッファへのポインタ
Effect g_aEffect[MAX_EFFECT];//エフェクトの情報

//=============================================================================
//エフェクトの初期化処理
//=============================================================================
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEffect;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャーの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\effect000.jpg",
		&g_pTextureEffect);

	//弾の初期化処理
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_aEffect[nCntEffect].fRadius = 0.0f;
		g_aEffect[nCntEffect].nLife = 100;
		g_aEffect[nCntEffect].bUse = false;
	}


	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);

	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点データポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - 50.0f, g_aEffect[nCntEffect].pos.y - 50.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + 50.0f, g_aEffect[nCntEffect].pos.y - 50.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - 50.0f, g_aEffect[nCntEffect].pos.y + 50.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + 50.0f, g_aEffect[nCntEffect].pos.y + 50.0f, 0.0f);
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
	g_pVtxBuffEffect->Unlock();
}
//=============================================================================
//エフェクトの終了処理
//=============================================================================
void UninitEffect(void)
{
	//テクスチャーの破棄
	if (g_pTextureEffect != NULL)
	{
		g_pTextureEffect->Release();
		g_pTextureEffect = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}



}
//=============================================================================
//エフェクトの更新処理
//=============================================================================
void UpdateEffect(void)
{
	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点データポインタを取得
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for ( int nCntEffect = 0; nCntEffect <MAX_EFFECT ; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{
			pVtx[0].Col = g_aEffect[nCntEffect].col;
			pVtx[1].Col = g_aEffect[nCntEffect].col;
			pVtx[2].Col = g_aEffect[nCntEffect].col;
			pVtx[3].Col = g_aEffect[nCntEffect].col;
			
			// 少しずつ小さくする
			g_aEffect[nCntEffect].fRadius -= 0.5f;

			// 頂点の大きさに fRadius を使う
			float size = g_aEffect[nCntEffect].fRadius;

			pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - size, g_aEffect[nCntEffect].pos.y - size, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + size, g_aEffect[nCntEffect].pos.y - size, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - size, g_aEffect[nCntEffect].pos.y + size, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + size, g_aEffect[nCntEffect].pos.y + size, 0.0f);

			// 寿命を減らす
			g_aEffect[nCntEffect].nLife--;

			// 寿命切れ、または小さくなり切ったら消す
			if (g_aEffect[nCntEffect].nLife <= 0 ||
				g_aEffect[nCntEffect].fRadius <= 0.0f)
			{
				g_aEffect[nCntEffect].bUse = false;
			}
		}

		pVtx += 4;
	}
}
//=============================================================================
//エフェクトの描画処理
//=============================================================================
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEffect;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_2D));
	//頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_2D);
	//テクスチャーの設定
	pDevice->SetTexture(0, g_pTextureEffect);

	//aブレンディング加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{//弾が使用されている
			
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEffect * 4, 2);
		}
	}


	//aブレンディングをもとに戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	

}
//=============================================================================
//エフェクトの設定処理
//=============================================================================
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius, int nLife)
{
	for (int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == false)
		{
			g_aEffect[nCntEffect].pos = pos;
			g_aEffect[nCntEffect].col = col;
			g_aEffect[nCntEffect].fRadius = fRadius;
			g_aEffect[nCntEffect].nLife = nLife;
			g_aEffect[nCntEffect].bUse = true;
			break;
		}
	}
}