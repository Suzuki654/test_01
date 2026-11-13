//=============================================================================
//
//タイトルを管理するクラスの宣言[title.h]
//Author:鈴木哲汰
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_
#include "main.h"

//タイトルの種類
typedef enum
{
	SELECT_START = 0,
	SELECT_RANKING,
	SELECT_END,
	SELECT_MAX,
}SERECT_TITLE;

//プロトタイプ宣言
void InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);

#endif // !_TITLE_H_


