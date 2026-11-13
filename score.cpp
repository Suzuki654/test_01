//=============================================================================
//
//スコア画面の処理実装ファイル[score.cpp]
//Author:鈴木哲汰
//
//=============================================================================
#include "score.h"
//マクロ定義
#define NUM_PLACE (8)

#define SCORE_OFFSETX (40.0f)
#define SCORE_SIZE (25.0f)

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureScore = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;
D3DXVECTOR3 g_posScore;//スコアの位置
int g_nScore;//スコアの値

//=============================================================================
//スコアの初期化処理
//=============================================================================
void InitScore(void)
{
	int nCntScore;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//テクスチャーの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Score.png",
		&g_pTextureScore);

	g_posScore = D3DXVECTOR3(960.0f, 50.0f, 0.0f);//位置を初期化
	g_nScore = 0;//値を初期化する

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLACE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);


	VERTEX_2D* pVtx;
	//頂点バッファをロックし、頂点データポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3((g_posScore.x + nCntScore * SCORE_OFFSETX) - SCORE_SIZE, g_posScore.y - SCORE_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3((g_posScore.x + nCntScore * SCORE_OFFSETX) + SCORE_SIZE, g_posScore.y - SCORE_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3((g_posScore.x + nCntScore * SCORE_OFFSETX) - SCORE_SIZE, g_posScore.y + SCORE_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3((g_posScore.x + nCntScore * SCORE_OFFSETX) + SCORE_SIZE, g_posScore.y + SCORE_SIZE, 0.0f);

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
		pVtx[1].tex = D3DXVECTOR2(0.2f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
		pVtx[3].tex = D3DXVECTOR2(0.2f, 0.5f);
		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();
}
//=============================================================================
//スコアの終了処理
//=============================================================================
void UninitScore(void)
{
	//テクスチャーの破棄
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}
//=============================================================================
//スコアの更新処理
//=============================================================================
void UpdateScore(void)
{

}
//=============================================================================
//スコアの描画処理
//=============================================================================
void DrawScore(void)
{

	int nCntScore;
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));
	//頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_2D);
	//テクスチャーの設定
	pDevice->SetTexture(0, g_pTextureScore);

	for (nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++)
	{
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntScore * 4, 2);
	}
}
//=============================================================================
//スコアの設定処理
//=============================================================================
void SetScore(int nScore)
{
	int aTexU[NUM_PLACE];//各桁の数字を格納
	int nCntScore;

	g_nScore = nScore;

	aTexU[0] = g_nScore % 100000000 / 10000000;
	aTexU[1] = g_nScore % 10000000 / 1000000;
	aTexU[2] = g_nScore % 1000000 / 100000;
	aTexU[3] = g_nScore % 100000 / 10000;
	aTexU[4] = g_nScore % 10000 / 1000;
	aTexU[5] = g_nScore % 1000 / 100;
	aTexU[6] = g_nScore % 100 / 10;
	aTexU[7] = g_nScore % 10 / 1;


	VERTEX_2D* pVtx;
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++)
	{


		float fTextureU = (aTexU[nCntScore] % 5) * 0.2f;
		float fTextureV = (aTexU[nCntScore] / 5) * 0.5f;

		pVtx[0].tex = D3DXVECTOR2(fTextureU, fTextureV);
		pVtx[1].tex = D3DXVECTOR2(fTextureU + 0.2f, fTextureV);
		pVtx[2].tex = D3DXVECTOR2(fTextureU, fTextureV + 0.5f);
		pVtx[3].tex = D3DXVECTOR2(fTextureU + 0.2f, fTextureV + 0.5f);
		pVtx += 4;
	}

	g_pVtxBuffScore->Unlock();
}
//=============================================================================
//スコアの座標設定処理
//=============================================================================
void SetScorePosition(float x, float y)
{
	g_posScore.x = x;
	g_posScore.y = y;

	VERTEX_2D* pVtx;
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntScore = 0; nCntScore < NUM_PLACE; nCntScore++)
	{
		pVtx[0].pos = D3DXVECTOR3((g_posScore.x + nCntScore * SCORE_OFFSETX) - SCORE_SIZE, g_posScore.y - SCORE_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3((g_posScore.x + nCntScore * SCORE_OFFSETX) + SCORE_SIZE, g_posScore.y - SCORE_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3((g_posScore.x + nCntScore * SCORE_OFFSETX) - SCORE_SIZE, g_posScore.y + SCORE_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3((g_posScore.x + nCntScore * SCORE_OFFSETX) + SCORE_SIZE, g_posScore.y + SCORE_SIZE, 0.0f);

		pVtx += 4;
	}

	g_pVtxBuffScore->Unlock();
}
//=============================================================================
//スコアの加算処理
//=============================================================================
void AddScore(int nValue)
{
	SetScore(g_nScore + nValue);
}
//=============================================================================
//スコアの取得処理
//=============================================================================
int GetScore(void)
{
	return g_nScore;
}
