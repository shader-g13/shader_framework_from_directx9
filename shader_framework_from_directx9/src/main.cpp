//=============================================================================
//
// ���C������ [main.cpp]
// Author : Kazuki Suetsugu
//
//=============================================================================

//=============================================================================
//	�C���N���[�h
//=============================================================================
#define _CRTDBG_MAP_ALLOC
#include <windows.h>
#include <crtdbg.h>
#include "application.h"
#include <KinectLap.h>

#pragma comment(lib, "DirectX9Framework.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "KinectLap.lib")

//-----------------------------------------------------------------------------
//	���C���֐�
//-----------------------------------------------------------------------------
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

  KinectLap lap;
  auto body = lap.CreateBodyReader();

  Application app(hInstance);
  app.MainLoop();

	return 0;
}

// EOF