//=============================================================================
//
//メインを管理するクラスの宣言[main.h]
//Author:鈴木哲汰
//
//=============================================================================
#ifndef _MAIN_H_   //このマクロ定義がされていなかったら
#define _MAIN_H_  //二重インクルード防止のマクロ
#include <windows.h>
#include <time.h>
#include "d3dx9.h"//描画処理に必要
#define DIRECTINPUT_VERSION (0x0800)//ビルド時の警告マクロ
#include "dinput.h"//入力処理に必要
#include "xaudio2.h"//サウンド処理に必要
#include "xinput.h"//ジョイパッド処理に必要

//ライブラリのリンク
#pragma comment(lib,"d3d9.lib")//描画処理に必要
#pragma comment(lib,"d3dx9.lib")//[d3d9]の拡張ライブラリ
#pragma comment(lib,"dxguid.lib")//Diractxコンポーネント（部品）使用に必要
#pragma comment(lib,"Winmm.lib")//システム時刻取得に必要
#pragma comment(lib,"dinput8.lib")//入力処理に必要
#pragma comment(lib,"xinput.lib")//ジョイパッド処理に必要

//マクロ定義
#define SCREEN_WIDTH (1280)      //ウィンドウの幅
#define SCREEN_HEIGHT (720)      //ウィンドウの高さ
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)


//画面モードの種類
typedef enum
{
	MODE_TITLE = 0,//タイトル画面
	MODE_TUTORIAL,//チュートリアル画面
	MODE_GAME,//ゲーム画面
	MODE_RESULT,//リザルト画面
	MODE_MAX
}MODE;



//頂点情報[2D]の構造体を定義
typedef struct
{
	D3DXVECTOR3 pos; //頂点座標
	float rhw;//座標変換用係数
	D3DCOLOR Col;//頂点カラー
	D3DXVECTOR2 tex;//テクスチャー座標（X,Y）

}VERTEX_2D;


//プロトタイプ宣言
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE GetMode(void);



#endif // !_MAIN_H_
