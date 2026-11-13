//=============================================================================
//
//プレイヤーを管理するクラスの宣言[player.h]
//Author:鈴木哲汰
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_ //二重インクルード防止のマクロ
#include "main.h"

//プレイヤーの状態
typedef enum
{
	PLAYERSTATE_NORMAL = 0,//通常状態
	PLAYERSTATE_DAMAGE,//ダメージ状態
	PLAYERSTATE_MAX

}PLAYERSTATE;

//プレイヤー構造体
typedef struct
{
	D3DXVECTOR3 pos; //位置
	D3DXVECTOR3 move;//移動量
	int nCounterAnim;//アニメーションカウンター
	int nPatternAnim;//アニメーションパターンNo.
	D3DXVECTOR3 rot;//向き
	float fLength;//対角線の長さ
	float fAngle;//対角線の角度
	float fPower;//強さ
	int nLife;//体力
	int nMaxLife;			// 最大HP
	int nCounterState;//状態カウンター
	bool bUse;//使用しているかどうか
	PLAYERSTATE state;//状態
}Player;

//プロトタイプ宣言
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void HitPlayer( int nDamage);
Player* GetPlayer(void);
int GetPlayerLife(void);
float GetShotPower(void);
#endif // !_PLAYER_H_

