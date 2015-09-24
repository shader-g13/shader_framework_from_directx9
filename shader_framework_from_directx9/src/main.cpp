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
#include <WindowModule.h>
#include <SafeDelete.h>
#include <FrameKeeper.h>
#include "application.h"

#pragma comment(lib, "DirectX9Framework.lib")

#define WINDOW_WIDTH (800)
#define WINDOW_HEIGHT (600)

//-----------------------------------------------------------------------------
//	���C���֐�
//-----------------------------------------------------------------------------
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

  // �E�B���h�E������
  snlib::WindowModule* window_ = new snlib::WindowModule(L"shader framework", WINDOW_WIDTH, WINDOW_HEIGHT, hInstance);
  window_->Initialize();
  window_->SetMessageCallback(WM_DESTROY, [](HWND, WPARAM, LPARAM) {
    PostQuitMessage(0);
  });
  window_->SetMessageCallback(WM_KEYDOWN, [](HWND h, WPARAM w, LPARAM) {
    if (w == VK_ESCAPE) { DestroyWindow(h); }
  });

  // �A�v���P�[�V����������
  Application* app = new Application;
  app->Initialize(window_->GetWindowHandle());

  // �t���[���L�[�p�[������
  auto update_func = [app] {
    // �A�v���P�[�V�����̍X�V�ƕ`��
    app->Update();
    app->Draw();
  };
  snlib::FrameKeeper* frame_keeper_ = new snlib::FrameKeeper(60, update_func);

  // ���C�����[�v
  while (window_->MessageProcessing()) {
    frame_keeper_->Step();
  }

	// �A�v���P�[�V�����̏I��
	app->Finalize();
  snlib::SafeDelete(app);
	
  // �t���[���L�[�p�[�I��
  snlib::SafeDelete(frame_keeper_);

  // �E�B���h�E�I��
  window_->Finalize();
  snlib::SafeDelete(window_);

	return 0;
}

// EOF