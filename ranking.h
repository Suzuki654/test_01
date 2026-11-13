//=============================================================================
//
//ランキングを管理するクラスの宣言[ranking.h]
//Author:鈴木哲汰
//
//=============================================================================
#ifndef _RANKING_H_
#define _RANKING_H_

#include"main.h"

//プロトタイプ宣言
void InitRanking(void);
void UninitRanking(void);
void UpdateRanking(void);
void DrawRanking(void);
void SaveRanking(void);
void LoadRanking(void);
void SortRanking(void);
void AddRanking(int nScore);
int GetRanking(int nRank);


#endif // !_RANKING_H_
