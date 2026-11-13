//=============================================================================
//
//ランキング画面の処理実装ファイル[ranking.cpp]
//Author:鈴木哲汰
//
//=============================================================================
#include "ranking.h"
#include <stdio.h>
//マクロ定義
#define NUM_PLACE (8)
#define NUM_RANKING (5)
#define RANKING_FILE "ranking.txt"
//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureRanking = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRanking = NULL;
int g_aRanking[NUM_RANKING] = { 0 };
int g_nNewRanking = -1;
//=============================================================================
//ランキングの初期化処理
//=============================================================================
void InitRanking(void)
{

	//ランキングを読み込む
	LoadRanking();
	//並び替える
	SortRanking();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// Score.pngを読み込む
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Score.png",
		&g_pTextureRanking);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_RANKING * NUM_PLACE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRanking,
		NULL);

	if (g_pVtxBuffRanking == NULL)
	{
		return;
	}

	//ランキングの更新処理
	UpdateRanking();
}
//=============================================================================
//ランキングの終了処理
//=============================================================================
void UninitRanking(void)
{
	if (g_pTextureRanking != NULL)
	{
		g_pTextureRanking->Release();
		g_pTextureRanking = NULL;
	}

	if (g_pVtxBuffRanking != NULL)
	{
		g_pVtxBuffRanking->Release();
		g_pVtxBuffRanking = NULL;
	}
	
}
//=============================================================================
//ランキングの更新処理
//=============================================================================
void UpdateRanking(void)
{
	if (g_pVtxBuffRanking == NULL)
	{
		return;
	}

	VERTEX_2D* pVtx;

	//頂点バッファをロック
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	for (int nRank = 0; nRank < NUM_RANKING; nRank++)
	{
		int nScore = g_aRanking[nRank];
		int aTexU[NUM_PLACE];

		aTexU[0] = nScore % 100000000 / 10000000;
		aTexU[1] = nScore % 10000000 / 1000000;
		aTexU[2] = nScore % 1000000 / 100000;
		aTexU[3] = nScore % 100000 / 10000;
		aTexU[4] = nScore % 10000 / 1000;
		aTexU[5] = nScore % 1000 / 100;
		aTexU[6] = nScore % 100 / 10;
		aTexU[7] = nScore % 10;

		for (int nPlace = 0; nPlace < NUM_PLACE; nPlace++)
		{
			float x = 515.0f + nPlace * 37.0f;
			float y = 400.0f + nRank * 65.0f;

			float size = 23.0f;

			pVtx[0].pos = D3DXVECTOR3(x - size, y - size, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(x + size, y - size, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(x - size, y + size, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(x + size, y + size, 0.0f);

			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			if (nRank == g_nNewRanking)
			{
				//今回追加されたスコア
				pVtx[0].Col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].Col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].Col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].Col = D3DCOLOR_RGBA(255, 255, 255, 255);
			}
			else
			{
				//通常のスコア
				pVtx[0].Col = D3DCOLOR_RGBA(255, 120, 0, 180);
				pVtx[1].Col = D3DCOLOR_RGBA(255, 120, 0, 180);
				pVtx[2].Col = D3DCOLOR_RGBA(255, 120, 0, 180);
				pVtx[3].Col = D3DCOLOR_RGBA(255, 120, 0, 180);
			}

			float fTextureU = (aTexU[nPlace] % 5) * 0.2f;
			float fTextureV = (aTexU[nPlace] / 5) * 0.5f;

			pVtx[0].tex = D3DXVECTOR2(fTextureU, fTextureV);
			pVtx[1].tex = D3DXVECTOR2(fTextureU + 0.2f, fTextureV);
			pVtx[2].tex = D3DXVECTOR2(fTextureU, fTextureV + 0.5f);
			pVtx[3].tex = D3DXVECTOR2(fTextureU + 0.2f, fTextureV + 0.5f);

			pVtx += 4;
		}
	}

	g_pVtxBuffRanking->Unlock();
}
//=============================================================================
//ランキングの描画処理
//=============================================================================
void DrawRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (g_pVtxBuffRanking == NULL ||g_pTextureRanking == NULL)
	{
		return;
	}

	pDevice->SetStreamSource(0,g_pVtxBuffRanking,0,sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetTexture(0, g_pTextureRanking);

	for (int nRank = 0; nRank < NUM_RANKING; nRank++)
	{
		for (int nPlace = 0; nPlace < NUM_PLACE; nPlace++)
		{
			int nVertex = (nRank * NUM_PLACE + nPlace) * 4;

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,nVertex,2);
		}
	}
}
//=============================================================================
//ランキングの並び変え処理
//=============================================================================
void SortRanking(void)
{
	int nCntRanking;
	int nCntSort;
	
	for (nCntRanking = 0; nCntRanking < NUM_RANKING - 1; nCntRanking++)
	{
		for (nCntSort = nCntRanking + 1; nCntSort < NUM_RANKING; nCntSort++)
		{
			//nCntRanking番目よりnCntSort番目の方が高得点なら入れ替える
			if (g_aRanking[nCntSort] > g_aRanking[nCntRanking])
			{
				int nSort = g_aRanking[nCntRanking];
				g_aRanking[nCntRanking] = g_aRanking[nCntSort];
				g_aRanking[nCntSort] = nSort;
			}
		}
	}
}
//=============================================================================
//ランキングのセーブ処理
//=============================================================================
void SaveRanking(void)
{
	FILE* pFile;
	//ファイルを開く
	pFile=fopen(RANKING_FILE, "w");
	if (pFile == NULL)
	{
		return;
	}
	//5位まで保存
	for (int nCntRanking = 0; nCntRanking < NUM_RANKING; nCntRanking++)
	{
		fprintf(pFile, "%d\n", g_aRanking[nCntRanking]);
	}

	//ファイルを閉じる
	fclose(pFile);
}

//=============================================================================
//ランキングのロード処理
//=============================================================================
void LoadRanking(void)
{
	int nCntRanking;

	FILE* pFile;
	//ファイルを開く
	pFile = fopen(RANKING_FILE, "r");
	//ファイルが存在しない場合
	if (pFile == NULL)
	{
		// すべて0点
		for (nCntRanking = 0; nCntRanking < NUM_RANKING; nCntRanking++)
		{
			g_aRanking[nCntRanking] = 0;
		}

		return;
	}

	//5位まで読み込む
	for (nCntRanking = 0; nCntRanking < NUM_RANKING; nCntRanking++)
	{
		if (fscanf(pFile, "%d", &g_aRanking[nCntRanking]) != 1)
		{
			g_aRanking[nCntRanking] = 0;
		}
	}
	// ファイルを閉じる
	fclose(pFile);
}
//=============================================================================
//スコアを登録する処理
//=============================================================================
void AddRanking(int nScore)
{
	//5位より高ければランキングに入れる
	if (nScore > g_aRanking[NUM_RANKING - 1])
	{
		g_aRanking[NUM_RANKING - 1] = nScore;
		//並び替える
		SortRanking();

		//今回のスコアが何位になったか調べる
		g_nNewRanking = -1;

		for (int nRank = 0; nRank < NUM_RANKING; nRank++)
		{
			if (g_aRanking[nRank] == nScore)
			{
				g_nNewRanking = nRank;
				break;
			}
		}

		//保存
		SaveRanking();
		//更新処理
		UpdateRanking();
	}
}
//=============================================================================
//ランキングのスコアを取得処理
//=============================================================================
int GetRanking(int nRank)
{
	if (nRank < 0 || nRank >= NUM_RANKING)
	{
		return 0;
	}

	return g_aRanking[nRank];
}
