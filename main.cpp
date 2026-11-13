//=============================================================================
//
//プレイヤーの処理実装ファイル[main.cpp]
//Author:鈴木哲汰
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "sound.h"
#include "title.h"
#include "game.h"
#include "tutorial.h"
#include "result.h"
#include "fade.h"


//マクロ定義
#define CLASS_NAME "WindowClass" //ウィンドウクラスの名前
#define WINDOU_MAME "テスト" //ウィンドウの名前

//プロトタイプ宣言
void DrawFPS(void);


//グローバル変数
LPDIRECT3D9 g_pD3D = NULL;//Direct3Dオブジェクトのポインタ
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;//Direct3Dデバイスへのポインタ
MODE g_mode = MODE_TITLE;//現在のモード
LPD3DXFONT g_pFont = NULL;//フォントへのポイントカウンター
int g_nCountFPS = 0;//FPSカウンター
//=============================================================================
//メイン関数
//=============================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),                  //メモリサイズ
		CS_CLASSDC,                          //ウィンドウのスタイル
		WindowProc,                          //ウィンドウのプロシージャ
		0,                                   //０にする（通常はしない）
		0,                                   //０にする（略
		hInstance,                           //インスタンスハンドル
		LoadIcon(NULL,IDI_APPLICATION),      //タスクバーのアイコン
		LoadCursor(NULL,IDC_ARROW),          //マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1),          //クライアント領域の背景色
		NULL,                                //メニューバー
		CLASS_NAME,                          //ウィンドウクラスの名前
		LoadIcon(NULL,IDI_APPLICATION),      //ファイルのアイコン
	};
	HWND hWnd; //ウィンドウハンドル（識別子）
	MSG msg;   //メッセージを格納する変数

	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };//画面サイズの構造体

	//ウィンドウクラスの登録
	RegisterClassEx(&wcex);  //メッセージを格納する変数

	//クライアント領域を指定のサイズに調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//ウィンドウを生成
	hWnd = CreateWindowEx    //拡張ウィンドウスタイル
	(0,
		CLASS_NAME,          //ウィンドウクラスの名前
		WINDOU_MAME,         //ウィンドウの名前
		WS_OVERLAPPEDWINDOW, //ウィンドウスタイル
		CW_USEDEFAULT,       //ウィンドウの左上ｘ座標
		CW_USEDEFAULT,       //ウィンドウの左上ｙ座標
		(rect.right - rect.left),//ウィンドウの幅
		(rect.bottom - rect.top),//ウィンドウの左上高さ
		NULL,                //親ウィンドウのハンドル
		NULL,                //メニューハンドルまたは子ウィンドウID
		hInstance,           //インスタンスバンドル
		NULL                 //ウィンドウの作成データ
	);

	DWORD dwCurrentTime;//現在時刻
	DWORD dwExecLastTime;//最後に処理した時刻
	DWORD dwFrameCount;//フレームカウント
	DWORD dwFPSLastTime;//さいごにFPSを計測した時刻
	//初期化処理
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{//初期化処理が失敗した場合
		return -1;
	}

	//分解能を設定
	timeBeginPeriod(1);
	dwCurrentTime = 0;//初期化する
	dwExecLastTime = timeGetTime();//現在時刻を取得（保存）
	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	//ウィンドウを表示
	ShowWindow(hWnd, nCmdShow); //ウィンドウ表示状態を設定
	UpdateWindow(hWnd);         //クライアント領域を更新

	//メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//windowsの処理
			if (msg.message == WM_QUIT)
			{//WM_QUITメッセージを受けっとったらメッセージグループを抜ける
				break;
			}
			else
			{
				//メッセージの設定
				TranslateMessage(&msg); //仮想キーメッセージを文字メッセージへ変換
				DispatchMessage(&msg);  //ウィンドウプロシージャへメッセージを送出
			}

		}
		else
		{//DirectXの処理
			dwCurrentTime = timeGetTime();//現在時刻を取得
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5秒経過
				//FPSを計測
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;//FPSを測定を保存
				dwFrameCount = 0;//フレームカウントをクリア

			}
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{//60分の1秒経過
				dwExecLastTime = dwCurrentTime;//処理開始の時刻[現在時刻]を保存
				dwFrameCount++;//フレームカウントを加算

				//更新処理
				Update();
				//描画処理
				Draw();
			}


		}

	}
	//終了処理
	Uninit();

	//分解能を戻す
	timeEndPeriod(1);

	//ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return(int)msg.wParam;



}
//=============================================================================
//ウィンドウプロシージャ
//=============================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;//返り値を格納

	switch (uMsg)
	{
	case WM_DESTROY://ウィンドウの破棄メッセージ
		//WM＿QUITメッセージを送る
		PostQuitMessage(0);

		break;
	case WM_KEYDOWN:    //キー押下のメッセージ   
		switch (wParam)
		{
		
		}
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam); //既定の処理を返す
}
//=============================================================================
//初期化処理
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;//ディスプレイモード

	D3DPRESENT_PARAMETERS d3dpp; //プレゼンテーションパラメーター

	srand((unsigned int)time(NULL));//ランダムを初期化

	//Direct3Dオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//現在のディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));//パラメータゼロクリア

	d3dpp.BackBufferWidth = SCREEN_WIDTH;//ゲーム画面サイズ（幅）
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;//ゲーム画面サイズ（高さ）
	d3dpp.BackBufferFormat = d3ddm.Format;//バックバッファの形成
	d3dpp.BackBufferCount = 1;//バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;//ダブルバッファの切り換え（映像信号に同期）
	d3dpp.EnableAutoDepthStencil = TRUE;//デプスバッファとステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;//デプスバッファとして16bitを使う
	d3dpp.Windowed = bWindow;//ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;//リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;//インターバル

	//Direct3Dデバイスの生成
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;

			}
		}
	}
	//レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//サンプラーステートの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	//テクスチャーステージステートの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
	// テクスチャカラー
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	//デバック表示用のフォント生成
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE,
		SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"Terminal", &g_pFont);

	//キーボードの初期化処理
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}
	//ジョイパッドの初期化処理
	if (FAILED(InitJoypad()))
	{
		return E_FAIL;
	}
	
	//サウンドの初期化処理
	InitSound(hWnd);

	//フェードの設定
	InitFade(g_mode);
	

	return S_OK;
}

//=============================================================================
//終了処理
//=============================================================================
void Uninit(void)
{
	//キーボードの終了処理
	UninitKeyboard();
	//タイトル画面の処理
	UninitTitle();
	//ゲーム画面の終了処理
	UninitGame();
	//リザルト画面の終了処理
	UninitResult();
	//ジョイパッドの終了処理
	UninitJoypad();
	//サウンドの停止
	StopSound();
	//サウンドの終了処理
	UninitSound();
	//フェードの終了処理
	UninitFade();
	

	//デバック表示用フォントの破棄
	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}
	//Direct3Dデバイスの破棄
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;

	}

	//Direct3Dオブジェクトの破棄
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;

	}
}

//=============================================================================
//更新処理
//=============================================================================
void Update(void)
{
	//キーボードの更新処理
	UpdateKeyboard();
	//ジョイパッドの更新処理
	UpdateJoypad();

	switch (g_mode)
	{
	case MODE_TITLE://タイトル画面
		UpdateTitle();
		break;
	case MODE_TUTORIAL://チュートリアル画面
		UpdateTutorial();
		break;
	case MODE_GAME://ゲーム画面
		UpdateGame();
		break;
	case MODE_RESULT://リザルト画面
		UpdateResult();
		break;
	}
	//フェードの更新処理
	UpdateFade();
	
	

}

//=============================================================================
//描画処理
//=============================================================================
void Draw(void)
{
	//画面クリア
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//描画開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//描画開始が成功した場合

		switch (g_mode)
		{
		case MODE_TITLE://タイトル画面
			DrawTitle();
			break;
		case MODE_TUTORIAL://チュートリアル画面
			DrawTutorial();
			break;
		case MODE_GAME://ゲーム画面
			DrawGame();
			break;
		case MODE_RESULT://リザルト画面
			DrawResult();
			break;
		}
		//フェードの描画処理
		DrawFade();
		
#ifdef _DEBUG
		//FPSの表示
		DrawFPS();
#endif // !_DEBUG



		//描画終了
		g_pD3DDevice->EndScene();
	}
	//バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
	
}
//=============================================================================
//FPSの描画処理
//=============================================================================
void DrawFPS(void)
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	//文字列に代入
	wsprintf(&aStr[0], "FPS:%d\n", g_nCountFPS);
	//テキストの描画
	g_pFont->DrawTextA(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//=============================================================================
//デバイスの取得
//=============================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}
//=============================================================================
//モードの設定
//=============================================================================
void SetMode(MODE mode)
{
	//現在の画面の終了処理
	switch (g_mode)
	{
	case MODE_TITLE://タイトル画面
		UninitTitle();
		break;
	case MODE_TUTORIAL://チュートリアル画面
		UninitTutorial();
		break;
	case MODE_GAME://ゲーム画面
		UninitGame();
		break;
	case MODE_RESULT://リザルト画面
		UninitResult();
		break;
	}
	g_mode = mode;//モードを保存

	//新しい画面モードの初期化処理
	switch (mode)
	{
	case MODE_TITLE://タイトル画面
		InitTitle();
		break;
	case MODE_TUTORIAL://チュートリアル画面
		InitTutorial();
		break;
	case MODE_GAME://ゲーム画面
		InitGame();
		break;
	case MODE_RESULT://リザルト画面
		InitResult();
		break;
	}
	

}
//=============================================================================
//モードの取得
//=============================================================================
MODE GetMode(void)
{
	return g_mode;
}