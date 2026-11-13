//=============================================================================
//
//リザルト画面を管理するクラスの宣言[result.h]
//Author:鈴木哲汰
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_
#include "main.h"

//プロトタイプ宣言
void InitResult(void);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(void);
void SetResultScore(int nScore);

#endif // !_RESULT_H_
