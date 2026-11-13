//=============================================================================
//
//フェードの処理実装ファイル[fade.cpp]
//Author:鈴木哲汰
//
//=============================================================================
#include "fade.h"

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL;//頂点バッファ
FADE g_fade;//フェードの状態
MODE g_modeNext;//次の画面（モード）
D3DXCOLOR g_colorFade;//ポリゴンの（フェード)の色

//=============================================================================
//フェードの初期化処理
//=============================================================================
void InitFade(MODE modeNext)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	g_fade = FADE_IN;//フェードインの状態に

	g_modeNext = modeNext; //次の画面モードを設定

	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);//黒いポリゴン不透明にしておく

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 *1,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFade,
		NULL);

	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点データポインタを取得
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);
	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//頂点カラーの設定
	pVtx[0].Col = D3DCOLOR_RGBA(0, 0, 0, 255);
	pVtx[1].Col = D3DCOLOR_RGBA(0, 0, 0, 255);
	pVtx[2].Col = D3DCOLOR_RGBA(0, 0, 0, 255);
	pVtx[3].Col = D3DCOLOR_RGBA(0, 0, 0, 255);
	//テクスチャー座標の設定
	
	//頂点バッファをあんろっくする
	g_pVtxBuffFade->Unlock();

	//モードの設定
	SetMode(g_modeNext);
}
//=============================================================================
//フェードの終了処理
//=============================================================================
void UninitFade(void)
{
	//頂点バッファの破棄
	if (g_pVtxBuffFade != NULL)
	{
		g_pVtxBuffFade->Release();
		g_pVtxBuffFade = NULL;
	}
}
//=============================================================================
//フェードの更新処理
//=============================================================================
void UpdateFade(void)
{
	if (g_fade!=FADE_NONE)
	{
		if (g_fade==FADE_IN)
		{//フェードイン状態
			g_colorFade.a -= 0.1f;//ポリゴンを透明にしていく
			if (g_colorFade.a<=0.0f)
			{
				g_colorFade.a = 0.0f;
				g_fade = FADE_NONE;//何もしていない状態にする
			}

		}
		else if (g_fade==FADE_OUT)
		{//フェードアウト状態
			g_colorFade.a += 0.1f;//ポリゴンを不透明にしていく
			if (g_colorFade.a>=1.0f)
			{
				g_colorFade.a = 1.0f;
				g_fade = FADE_IN;//フェードイン状態にする

				//モードの設定（次に画面に移行）
				SetMode(g_modeNext);
			}
		}
		VERTEX_2D* pVtx;
		//頂点バッファをロックし、頂点データポインタを取得
		g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);
		pVtx[0].Col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorFade.a);
		pVtx[1].Col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorFade.a);
		pVtx[2].Col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorFade.a);
		pVtx[3].Col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorFade.a);
		//頂点バッファをあんろっくする
		g_pVtxBuffFade->Unlock();
	}	
}		
//=============================================================================
//フェードの描画処理
//=============================================================================
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX_2D));

	//頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, NULL);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
//=============================================================================
//フェードの設定
//=============================================================================
void SetFade(MODE modeNext)
{
	g_fade = FADE_OUT;//フェードアウト状態
	g_modeNext = modeNext;//次の画面モードに設定
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);//黒いポリゴンにしていく

}
//=============================================================================
//フェードの取得
//=============================================================================
FADE GetFade(void)
{
	return g_fade;
}