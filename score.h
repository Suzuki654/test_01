//=============================================================================
//
//スコアを管理するクラスの宣言[score.h]
//Author:鈴木哲汰
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"
//プロトタイプ宣言
void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);
void SetScore(int nScore);
void SetScorePosition(float x, float y);
void AddScore(int nValueint);
int GetScore(void);

#endif // !_SCORE_H_

