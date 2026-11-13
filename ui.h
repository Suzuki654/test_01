//=============================================================================
//
//UIを管理するクラスの宣言[ui.h]
//Author:鈴木哲汰
//
//=============================================================================
#ifndef _UI_H_
#define _UI_H_

#include "main.h"

//UI列挙型
typedef enum
{
	UI_START,

	UI_TEX_MAX
}UI_TEXTURE;

//UI頂点番号
typedef enum
{
	
	UI_VTX_MAX

}UI_VERTEX;

//プロトタイプ宣言
void InitUI(void);
void UninitUI(void);
void UpdateUI(void);
void DrawUI(void);

#endif // !_UI_H_
