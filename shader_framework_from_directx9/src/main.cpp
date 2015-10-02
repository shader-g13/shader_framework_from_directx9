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

#pragma comment(lib, "DirectX9Framework.lib")
#pragma comment(lib, "d3dx9.lib")

//-----------------------------------------------------------------------------
//	メイン関数
//-----------------------------------------------------------------------------
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

  Application app(hInstance);
  app.MainLoop();

	return 0;
}

// EOF