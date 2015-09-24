
#include "application.h"
#include <SafeDelete.h>

using namespace snlib;

/// @brief コンストラクタ
Application::Application(HINSTANCE instance_handle) :
instance_handle_(instance_handle),
renderer_(nullptr),
test_scene_(nullptr) {

  // ウィンドウ初期化
  window_ = new snlib::WindowModule(L"shader framework", 800, 600, instance_handle_);
  window_->Initialize();
  window_->SetMessageCallback(WM_DESTROY, [](HWND, WPARAM, LPARAM) {
    PostQuitMessage(0);
  });
  window_->SetMessageCallback(WM_KEYDOWN, [](HWND h, WPARAM w, LPARAM) {
    if (w == VK_ESCAPE) { DestroyWindow(h); }
  });

  // フレームキーパー初期化
  auto update_func = [this] {
    // アプリケーションの更新と描画
    Update();
    Draw();
  };
  frame_keeper_ = new snlib::FrameKeeper(60, update_func);

  // レンダラー初期化
  renderer_ = new Renderer();
  renderer_->Initialize(window_->GetWindowHandle(), 800, 600);

  LPDIRECT3DDEVICE9 device = renderer_->GetDevice();

  test_scene_ = new TestScene();
  test_scene_->Initialize(device);
}

/// @brief デストラクタ
Application::~Application() {

  test_scene_->Finalize();
  SafeDelete(test_scene_);

  // レンダラー終了
  renderer_->Finalize();
  delete renderer_;
  renderer_ = nullptr;

  // フレームキーパー終了
  snlib::SafeDelete(frame_keeper_);

  // ウィンドウ終了
  window_->Finalize();
  snlib::SafeDelete(window_);
}

/// @brief 更新
void Application::Update() {
  test_scene_->Update();
}

/// @brief 描画
void Application::Draw() {
  LPDIRECT3DDEVICE9 device = renderer_->GetDevice();

  renderer_->BegenDraw();

  test_scene_->Draw(device);

	renderer_->EndDraw();
}


/// @brief メインループ
void Application::MainLoop() {
  while (window_->MessageProcessing()) {
    frame_keeper_->Step();
  }
}
