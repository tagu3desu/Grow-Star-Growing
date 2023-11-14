/*==============================================================================

   DirectXの初期化 [main.cpp]
                                                         Author : 
                                                         Date   : 
--------------------------------------------------------------------------------

==============================================================================*/
#include	"main.h"
#include	"01_Scene.h"
#include	"01_BOSSscene.h"
#include	"00_title.h"
#include	"01.5_StageSelect.h"
#include	"Result.h"
#include	"weapon_shop.h"
#include	"weapon_select.h"
#include	"data.h"

#include	"keyboard.h"

//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************
#pragma comment (lib, "d3d11.lib")		
#pragma comment (lib, "d3dcompiler.lib")
#pragma comment (lib, "d3dx11.lib")	
#pragma comment (lib, "d3dx9.lib")	
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "dxerr.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib,"xinput.lib")

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CLASS_NAME			"GameWindow"				// ウインドウのクラス名
#define WINDOW_CAPTION		"DirectXの初期化"			// ウインドウのキャプション名
//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);


//*****************************************************************************
// グローバル変数:
//*****************************************************************************

#ifdef _DEBUG
int		g_CountFPS;							// FPSカウンタ
char	g_DebugStr[2048] = WINDOW_CAPTION;	// デバッグ文字表示用




#endif

SCENE g_Scene = SCENE_NONE;	// シーンを初期状態に

//=============================================================================
// メイン関数
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// 無くても良いけど、警告が出る（未使用宣言）
	UNREFERENCED_PARAMETER(lpCmdLine);		// 無くても良いけど、警告が出る（未使用宣言）

	// 時間計測用
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;
	
	WNDCLASS wc = {};
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = CLASS_NAME;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);

	RegisterClass(&wc);
	
	// ウィンドウの作成
	HWND hWnd = CreateWindow(CLASS_NAME,
						WINDOW_CAPTION,
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,																		// ウィンドウの左座標
						CW_USEDEFAULT,																		// ウィンドウの上座標
						SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME)*2,									// ウィンドウ横幅
						SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME)*2+GetSystemMetrics(SM_CYCAPTION),	// ウィンドウ縦幅
						NULL,
						NULL,
						hInstance,
						NULL);

	// DirectXの初期化(ウィンドウを作成してから行う)
	if(FAILED(Init(hInstance, hWnd, true)))
	{
		return -1;
	}

	// フレームカウント初期化
	timeBeginPeriod(1);	// 分解能を設定
	dwExecLastTime = dwFPSLastTime = timeGetTime();	// システム時刻をミリ秒単位で取得
	dwCurrentTime = dwFrameCount = 0;
	
	// ウインドウの表示(Init()の後に呼ばないと駄目)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG			msg;

	// メッセージループ
	while(1)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();					// システム時刻を取得

			if ((dwCurrentTime - dwFPSLastTime) >= 1000)	// 1秒ごとに実行
			{
#ifdef _DEBUG
				g_CountFPS = dwFrameCount;
#endif
				dwFPSLastTime = dwCurrentTime;				// FPSを測定した時刻を保存
				dwFrameCount = 0;							// カウントをクリア
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))	// 1/60秒ごとに実行
			{
				dwExecLastTime = dwCurrentTime;	// 処理した時刻を保存

#ifdef _DEBUG	// デバッグ版の時だけFPSを表示する
				wsprintf(g_DebugStr, WINDOW_CAPTION);
				wsprintf(&g_DebugStr[strlen(g_DebugStr)], " FPS:%d", g_CountFPS);
				SetWindowText(hWnd, g_DebugStr);
#endif

				Update();			// 更新処理
				Draw();				// 描画処理

				dwFrameCount++;		// 処理回数のカウントを加算
			}
		}
	}
	
	timeEndPeriod(1);				// 分解能を戻す

	// 終了処理
	Uninit();

	return (int)msg.wParam;
}

//=============================================================================
// プロシージャ
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Keyboard_ProcessMessage(uMsg, wParam, lParam);

	switch (uMsg) {
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) {
			SendMessage(hWnd, WM_CLOSE, 0, 0);
		}
		break;

	case WM_CLOSE:
		if (MessageBox(hWnd, "本当に終了してよろしいですか？", "確認", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK) {
			DestroyWindow(hWnd);
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	};

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// レンダリング処理の初期化
	InitRenderer(hInstance, hWnd, bWindow);


	//入力処理の初期化
	InitInput(hInstance, hWnd);
	Keyboard_Initialize();

	//サウンド初期化
	InitSound(hWnd);
	
	InitPolygon();	//ポリゴン初期化

	//初回起動時のデータ初期化
	InitData();

	SetScene(SCENE_TITLE);	// タイトルシーン初期化

	


	return S_OK;
}


//=============================================================================
// 終了処理
//=============================================================================
void Uninit(void)
{
	UninitPolygon();	//ポリゴン終了処理
	UninitSound();//サウンド終了処理
	


	SetScene(SCENE_NONE);	// タイトルシーン初期化

	//入力処理の終了
	UninitInput();

	// レンダリングの終了処理
	UninitRenderer();
}

//=============================================================================
// 更新処理
//=============================================================================
void Update(void)
{
	//入力処理の更新
	UpdateInput();
	

	UpdatePolygon();	//ポリゴン更新処理

	switch (g_Scene)
	{
	case SCENE_TITLE:
		Updatetitle();
		//Keyboard_IsKeyDown(K);
		break;
	case SCENE_SELECT:
		UpdateStageSelect();

		break;

	case SCENE_GAME://ステージ01
		UpdateScene();
		break;

	case SCENE_STAGE02://ステージ02
		UpdateScene();
		break;

	case SCENE_STAGE03://ステージ03
		UpdateScene();
		break;

	case SCENE_STAGE04://ステージ04
		UpdateScene();
		break;

	case SCENE_BOSS01:
		UpdateBossScene();
		break;
	case SCENE_BOSS02:
		UpdateBossScene();
		break;
	case SCENE_BOSS03:
		UpdateBossScene();
		break;
	case SCENE_BOSS04:
		UpdateBossScene();
		break;
	case SCENE_RESULT:
		UpdateResultScene();
		break;
	case SCENE_SHOP:
		UpdateWeaponShop();
		break;
	case SCENE_SKILL_SET:
		UpdateWeaponSelect();
		break;
	}

	


	
}

//=============================================================================
// 描画処理
//=============================================================================
void Draw(void)
{
	// バックバッファクリア
	Clear();

	// 2D描画なので深度無効
	SetDepthEnable(false);

	DrawPolygon();	//ポリゴン描画処理



	switch (g_Scene)
	{
	case SCENE_TITLE:
		Drawtitle();
		break;

	case SCENE_SELECT:
		DrawStageSelect();
		break;

	case SCENE_GAME:
		DrawBScene();//ステージ01
		break;

	case SCENE_STAGE02://ステージ02
		DrawBScene();
		break;

	case SCENE_STAGE03://ステージ03
		DrawBScene();
		break;

	case SCENE_STAGE04://ステージ04
		DrawBScene();
		break;

	case SCENE_BOSS01:
		DrawBossScene();
		break;
	case SCENE_BOSS02:
		DrawBossScene();
		break;
	case SCENE_BOSS03:
		DrawBossScene();
		break;
	case SCENE_BOSS04:
		DrawBossScene();
		break;
	case SCENE_RESULT:
		DrawResultScene();
		break;

	case SCENE_SHOP:
		DrawWeaponShop();
		break;

	case SCENE_SKILL_SET:
		DrawWeaponSelect();
		break;
	}



	// バックバッファ、フロントバッファ入れ替え
	Present();
}

void SetScene(SCENE Scene)
{
	// 現在のシーンの終了処理
	switch (g_Scene)
	{
	case SCENE_NONE:
		break;

	case SCENE_TITLE://タイトル
		Uninittitle();
		break;

	case SCENE_SELECT://ステージセレクト
		UninitStageSelect();
		break;

	case SCENE_GAME://ステージ01
		UninitScene();
		break;

	case SCENE_STAGE02://ステージ02
		UninitScene();
		break;

	case SCENE_STAGE03://ステージ03
		UninitScene();
		break;

	case SCENE_STAGE04://ステージ04
		UninitScene();
		break;

	case SCENE_BOSS01:
		UninitBossScene();
		break;

	case SCENE_BOSS02:
		UninitBossScene();
		break;

	case SCENE_BOSS03:
		UninitBossScene();
		break;

	case SCENE_BOSS04:
		UninitBossScene();
		break;

	case SCENE_RESULT:
		UninitResultScene();
		break;

	case SCENE_SHOP:
		UninitWeaponShop();
		break;

	case SCENE_SKILL_SET:
		UninitWeaponSelect();
		break;
	}

	StopSoundAll();//すべての再生を停止

	// シーン状態を更新
	g_Scene = Scene;

	// 次のシーンの初期化処理
	switch (g_Scene)
	{
	case SCENE_NONE:
		break;

	case SCENE_TITLE://タイトル
		Inittitle();
		break;

	case SCENE_SELECT://ステージセレクト
		InitStageSelect();
		break;

	case SCENE_GAME://ステージ01
		InitScene();
		break;

	case SCENE_STAGE02://ステージ02
		InitScene();
		break;

	case SCENE_STAGE03://ステージ03
		InitScene();
		break;

	case SCENE_STAGE04://ステージ04
		InitScene();
		break;


	case SCENE_BOSS01:
		InitBossScene();
		break;

	case SCENE_BOSS02:
		InitBossScene();
		break;

	case SCENE_BOSS03:
		InitBossScene();
		break;

	case SCENE_BOSS04:
		InitBossScene();
		break;
	case SCENE_RESULT:
		InitResultScene();
		break;
	case SCENE_SHOP:
		InitWeaponShop();
		break;
	case SCENE_SKILL_SET:
		InitWeaponSelect();
		break;
	}
}

SCENE GetScene()
{
	return g_Scene;
}
