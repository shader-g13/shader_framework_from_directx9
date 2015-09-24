//=============================================================================
//
// メイン処理 [main.cpp]
// Author : Kazuki Suetsugu
//
//=============================================================================

//=============================================================================
//	インクルード
//=============================================================================
#define _CRTDBG_MAP_ALLOC
#include <windows.h>
#include <crtdbg.h>
#include "application.h"

#pragma comment(lib, "winmm.lib")

#define CLASS_NAME ("class")
#define WINDOW_WIDTH (800)
#define WINDOW_HEIGHT (600)

//=============================================================================
//	プロトタイプ宣言
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//=============================================================================
//	グローバル変数
//=============================================================================

//-----------------------------------------------------------------------------
//	メイン関数
//-----------------------------------------------------------------------------
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	UNREFERENCED_PARAMETER(hPrevInstance);	// 無くても良いけど、警告が出る（未使用宣言）
	UNREFERENCED_PARAMETER(lpCmdLine);		// 無くても良いけど、警告が出る（未使用宣言）

	DWORD dwExecLastTime;					//FPS表示用変数
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;

	//ウィンドウクラス生成
	WNDCLASSEX	wcex = {
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};
	HWND hWnd;								//ウィンドウハンドル
	MSG msg;

	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// ウィンドウの作成
	hWnd = CreateWindowEx(0,
						CLASS_NAME,
						CLASS_NAME,
						WS_OVERLAPPEDWINDOW,//WS_OVERLAPPEDWINDOW |WS_VSCROLL / WS_MINIMIZEBOX / WS_OVERLAPPEDWINDOW & ~(WS_THICKFRAME |WS_MAXIMIZEBOX)
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						((int)WINDOW_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2),
						((int)WINDOW_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION)),
						NULL,
						NULL,
						hInstance,
						NULL);

	//フレームカウント初期化
	timeBeginPeriod(1);				// 分解能を設定
	dwExecLastTime = 
	dwFPSLastTime = timeGetTime();
	dwCurrentTime =
	dwFrameCount = 0;

	// ウインドウの表示(初期化処理の後に行う)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// アプリケーション初期化
	Application app;
	app.Initialize(hWnd);

	// メッセージループ
	while(1)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)	// メッセージを取得しなかった場合"0"を返す
		{// Windowsの処理
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else
			{
				// メッセージの翻訳と送出
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();
			if((dwCurrentTime - dwFPSLastTime) >= 500)	// 0.5秒ごとに実行
			{
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			if((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;

				// アプリケーションの更新と描画
				app.Update();
				app.Draw();

				dwFrameCount++;
			}
		}
	}

	// アプリケーションの終了
	app.Finalize();
	
	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	timeEndPeriod(1);				// 分解能を戻す

	return (int)msg.wParam;
}

//=============================================================================
// プロシージャ
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:			//Escが押されたらウィンドウを破棄して終了
			DestroyWindow(hWnd);
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

