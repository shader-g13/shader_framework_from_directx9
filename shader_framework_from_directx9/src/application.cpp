
#include "application.h"
#include <SafeDelete.h>

using namespace snlib;

/// @brief �R���X�g���N�^
Application::Application(HINSTANCE instance_handle) :
instance_handle_(instance_handle),
renderer_(nullptr),
test_scene_(nullptr) {

  // �E�B���h�E������
  window_ = new snlib::WindowModule(L"shader framework", 800, 600, instance_handle_);
  window_->Initialize();
  window_->SetMessageCallback(WM_DESTROY, [](HWND, WPARAM, LPARAM) {
    PostQuitMessage(0);
  });
  window_->SetMessageCallback(WM_KEYDOWN, [](HWND h, WPARAM w, LPARAM) {
    if (w == VK_ESCAPE) { DestroyWindow(h); }
  });

  // �t���[���L�[�p�[������
  auto update_func = [this] {
    // �A�v���P�[�V�����̍X�V�ƕ`��
    Update();
    Draw();
  };
  frame_keeper_ = new snlib::FrameKeeper(60, update_func);

  // �����_���[������
  renderer_ = new Renderer();
  renderer_->Initialize(window_->GetWindowHandle(), 800, 600);

  LPDIRECT3DDEVICE9 device = renderer_->GetDevice();

  test_scene_ = new TestScene();
  test_scene_->Initialize(device);
}

/// @brief �f�X�g���N�^
Application::~Application() {

  test_scene_->Finalize();
  SafeDelete(test_scene_);

  // �����_���[�I��
  renderer_->Finalize();
  delete renderer_;
  renderer_ = nullptr;

  // �t���[���L�[�p�[�I��
  snlib::SafeDelete(frame_keeper_);

  // �E�B���h�E�I��
  window_->Finalize();
  snlib::SafeDelete(window_);
}

/// @brief �X�V
void Application::Update() {
  test_scene_->Update();
}

/// @brief �`��
void Application::Draw() {
  LPDIRECT3DDEVICE9 device = renderer_->GetDevice();

  renderer_->BegenDraw();

  test_scene_->Draw(device);

	renderer_->EndDraw();
}


/// @brief ���C�����[�v
void Application::MainLoop() {
  while (window_->MessageProcessing()) {
    frame_keeper_->Step();
  }
}
