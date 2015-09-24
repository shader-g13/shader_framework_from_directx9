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
#include <WindowModule.h>
#include <SafeDelete.h>
#include <FrameKeeper.h>
#include "application.h"

#pragma comment(lib, "DirectX9Framework.lib")

#define WINDOW_WIDTH (800)
#define WINDOW_HEIGHT (600)

//-----------------------------------------------------------------------------
//	メイン関数
//-----------------------------------------------------------------------------
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

  // ウィンドウ初期化
  snlib::WindowModule* window_ = new snlib::WindowModule(L"shader framework", WINDOW_WIDTH, WINDOW_HEIGHT, hInstance);
  window_->Initialize();
  window_->SetMessageCallback(WM_DESTROY, [](HWND, WPARAM, LPARAM) {
    PostQuitMessage(0);
  });
  window_->SetMessageCallback(WM_KEYDOWN, [](HWND h, WPARAM w, LPARAM) {
    if (w == VK_ESCAPE) { DestroyWindow(h); }
  });

  // アプリケーション初期化
  Application* app = new Application;
  app->Initialize(window_->GetWindowHandle());

  // フレームキーパー初期化
  auto update_func = [app] {
    // アプリケーションの更新と描画
    app->Update();
    app->Draw();
  };
  snlib::FrameKeeper* frame_keeper_ = new snlib::FrameKeeper(60, update_func);

  // メインループ
  while (window_->MessageProcessing()) {
    frame_keeper_->Step();
  }

	// アプリケーションの終了
	app->Finalize();
  snlib::SafeDelete(app);
	
  // フレームキーパー終了
  snlib::SafeDelete(frame_keeper_);

  // ウィンドウ終了
  window_->Finalize();
  snlib::SafeDelete(window_);

	return 0;
}

// EOF