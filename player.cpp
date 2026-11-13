//=============================================================================
//
//プレイヤーの処理実装ファイル[Player.cpp]
//Author:鈴木哲汰
//
//=============================================================================
#include "player.h"
#include "input.h"
/*#include "bg.h"

#include "bullet.h"
#include "explosion.h"
#include "score.h"
#include "sound.h"*/

//マクロ定義
#define PLAYER_WIDTH  200.0f//幅
#define PLAYER_HEIGHT 400.0f//縦
//dddada
//グローバル変数
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;//テクスチャーへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;//頂点バッファ
Player g_Player;
bool g_bChargeSound = false;
bool g_bPlayerFlip = false;

float g_fShotPower = 0.0f;

//=============================================================================
//プレイヤーの初期化処理
//=============================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャーの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\Player\\male_hero.png",
		&g_pTexturePlayer);

	g_bPlayerFlip = false;
	g_Player.pos = D3DXVECTOR3(500.0f, 500.0f, 0.0f);//位置を初期化する
	g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//移動量を初期化する
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//向きを初期化する
	g_Player.nCounterAnim = 0;//カウンターを初期化する
	g_Player.nPatternAnim = 0;//パターンNo.を初期化する
	g_Player.fPower = 0;//パワーを初期化
	g_Player.nLife = g_Player.nMaxLife;//体力を初期化
	g_Player.nMaxLife = 200;			// 最大HP
	g_Player.nCounterState = 0;//状態カウンターを初期化
	g_Player.state = PLAYERSTATE_NORMAL;//状態を初期化
	g_Player.bUse = true;//使用している状態に初期化


	//対角線を算出
	g_Player.fLength = sqrtf(PLAYER_WIDTH * PLAYER_WIDTH + PLAYER_HEIGHT * PLAYER_HEIGHT) * 0.5f;//幅＋縦
	//対角線の角度を算出
	g_Player.fAngle = atan2f(PLAYER_WIDTH, PLAYER_HEIGHT);//幅、縦



	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,//必要な頂点数
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer,
		NULL);

	VERTEX_2D* pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
	/*//頂点座標の設定
	pVtx[0].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (D3DX_PI + g_Player.fAngle)) * g_Player.fLength;
	pVtx[0].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (D3DX_PI + g_Player.fAngle)) * g_Player.fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + (D3DX_PI - g_Player.fAngle)) * g_Player.fLength;
	pVtx[1].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + (D3DX_PI - g_Player.fAngle)) * g_Player.fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_Player.pos.x + sinf(g_Player.rot.z - g_Player.fAngle) * g_Player.fLength;
	pVtx[2].pos.y = g_Player.pos.y + cosf(g_Player.rot.z - g_Player.fAngle) * g_Player.fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_Player.pos.x + sinf(g_Player.rot.z + g_Player.fAngle) * g_Player.fLength;
	pVtx[3].pos.y = g_Player.pos.y + cosf(g_Player.rot.z + g_Player.fAngle) * g_Player.fLength;
	pVtx[3].pos.z = 0.0f;
	*/

	//左上
	pVtx[0].pos.x = g_Player.pos.x - PLAYER_WIDTH;
	pVtx[0].pos.y = g_Player.pos.y - PLAYER_HEIGHT;

	//右上
	pVtx[1].pos.x = g_Player.pos.x + PLAYER_WIDTH;
	pVtx[1].pos.y = g_Player.pos.y - PLAYER_HEIGHT;

	//左下
	pVtx[2].pos.x = g_Player.pos.x - PLAYER_WIDTH;
	pVtx[2].pos.y = g_Player.pos.y;

	//右下
	pVtx[3].pos.x = g_Player.pos.x + PLAYER_WIDTH;
	pVtx[3].pos.y = g_Player.pos.y;
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
	pVtx[1].tex = D3DXVECTOR2(0.10f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.125);
	pVtx[3].tex = D3DXVECTOR2(0.10f, 0.125);

	//頂点バッファをアンロックする
	g_pVtxBuffPlayer->Unlock();
}
//=============================================================================
//プレイヤーの終了処理
//=============================================================================
void UninitPlayer(void)
{
	//テクスチャーの破棄
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}
//=============================================================================
//プレイヤーの更新処理
//=============================================================================
void UpdatePlayer(void)
{
	//アニメーション
	float fUCoord, fVCoord;
	// スティックの入力値を取得
	SHORT stickX = GetJoypadLeftStickX();
	SHORT stickY = GetJoypadLeftStickY();

	VERTEX_2D* pVtx;//頂点情報へのポインタ
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	
	if (GetKeyboardPress(DIK_A))
	{//Aキーが押された
		
		g_Player.move.x -= 5.0f;
		g_bPlayerFlip = true;

	}
	else if (GetKeyboardPress(DIK_D))
	{//Dキーが押された
		
		g_Player.move.x += 5.0f;
		g_bPlayerFlip = false;
	}
		


	//壁
	if (g_Player.pos.x >= SCREEN_WIDTH + 50.0f) // 右端
	{
		g_Player.pos.x = SCREEN_WIDTH+50.0f;
		g_Player.pos.x = 0.0f;//ワープ	
	}
	else if (g_Player.pos.x <=0.0f - 50.0f) // 左端
	{
		g_Player.pos.x = 0.0f-50.0f;
		g_Player.pos.x = SCREEN_WIDTH;
	}


	g_Player.nCounterAnim++;//カウンタを加算
	if ((g_Player.nCounterAnim % 4) == 0)
	{//一定時間経過

		//パターンNo.を更新する
		g_Player.nPatternAnim = (g_Player.nPatternAnim + 1) % 10;

		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

		fUCoord = (g_Player.nPatternAnim % 10) * 0.1f;
		//fVCoord = (g_nPatternAnimPlayer / 4) * 0.1f;
		
		if (fabsf(g_Player.move.x) > 0.2f)
		{
			//4段目を固定
			fVCoord = 3.0f / 8.0f;
		}
		else
		{
			//3段目を固定
			fVCoord = 1.0f / 8.0f;
		}
		

		if (g_bPlayerFlip == false)
		{
			//右向き
			pVtx[0].tex = D3DXVECTOR2(fUCoord, fVCoord);
			pVtx[1].tex = D3DXVECTOR2(fUCoord + 0.1f, fVCoord);
			pVtx[2].tex = D3DXVECTOR2(fUCoord, fVCoord + 0.125f);
			pVtx[3].tex = D3DXVECTOR2(fUCoord + 0.1f, fVCoord + 0.125f);
		}
		else
		{
			//左向き
			pVtx[0].tex = D3DXVECTOR2(fUCoord + 0.1f, fVCoord);
			pVtx[1].tex = D3DXVECTOR2(fUCoord, fVCoord);
			pVtx[2].tex = D3DXVECTOR2(fUCoord + 0.1f, fVCoord + 0.125f);
			pVtx[3].tex = D3DXVECTOR2(fUCoord, fVCoord + 0.125f);
		}
		//頂点バッファをあんろっくする
		g_pVtxBuffPlayer->Unlock();
	}

	//位置を更新
	g_Player.pos.x += g_Player.move.x;
	g_Player.pos.y += g_Player.move.y;

	//移動量を更新
	g_Player.move.x += (0.0f - g_Player.move.x) * 0.1f;
	g_Player.move.y += (0.0f - g_Player.move.y) * 0.1f;




	//左上
	pVtx[0].pos.x = g_Player.pos.x - PLAYER_WIDTH;
	pVtx[0].pos.y = g_Player.pos.y - PLAYER_HEIGHT;

	//右上
	pVtx[1].pos.x = g_Player.pos.x + PLAYER_WIDTH;
	pVtx[1].pos.y = g_Player.pos.y - PLAYER_HEIGHT;

	//左下
	pVtx[2].pos.x = g_Player.pos.x - PLAYER_WIDTH;
	pVtx[2].pos.y = g_Player.pos.y;

	//右下
	pVtx[3].pos.x = g_Player.pos.x + PLAYER_WIDTH;
	pVtx[3].pos.y = g_Player.pos.y;

	//頂点バッファをあんろっくする
	g_pVtxBuffPlayer->Unlock();


}
//=============================================================================
//プレイヤーの描画処理
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

	//頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_2D);

	//ドット絵用の補間設定
	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);

	//テクスチャの端を固定
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);

	if (g_Player.bUse == true)
	{
		//テクスチャーの設定
		pDevice->SetTexture(0, g_pTexturePlayer);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}


}
//=============================================================================
//プレイヤーのヒット処理
//=============================================================================
void HitPlayer(int nDamage)
{
	/*VERTEX_2D* pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	g_Player.nLife -= nDamage;

	if (g_Player.nLife <= 0)
	{//体力がゼロになったら
		//爆発の設定
		SetExplosion(g_Player.pos, D3DCOLOR_RGBA(255, 255, 255, 255),1);
		g_Player.bUse = false;//使用していない
		PlaySound(SOUND_LABEL_SE_PlayerDeath);

	}
	else
	{//ゼロじゃないとき
		g_Player.state = PLAYERSTATE_DAMAGE;
		g_Player.nCounterState = 5;//ダメージ状態をたもつ時間

		PlaySound(SOUND_LABEL_SE_HIT);

		//頂点カラーの設定
		pVtx[0].Col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[1].Col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].Col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].Col = D3DCOLOR_RGBA(255, 0, 0, 255);
	}

	//頂点バッファをあんろっくする

	g_pVtxBuffPlayer->Unlock();
*/

}
//=============================================================================
//プレイヤーを取得
//=============================================================================
Player* GetPlayer(void)
{
	return &g_Player;
}
//=============================================================================
//プレイヤーのHpを取得
//=============================================================================
int GetPlayerLife(void)
{
	return g_Player.nLife;
}
//=============================================================================
//プレイヤーのパワーを取得
//============================================================================
float GetShotPower(void)
{
	return g_fShotPower;
}
