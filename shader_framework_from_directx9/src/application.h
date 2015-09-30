#pragma once

#include <Windows.h>
#include <Win32Api/WindowModule.h>
#include <Util/FrameKeeper.h>
#include <DirectX9/Rendering/DirectX9module.h>
#include "test_scene.h"

class Application {
public:
	/// @brief �R���X�g���N�^
  Application(HINSTANCE instance_handle);

	/// @brief �f�X�g���N�^
	virtual ~Application();

	/// @brief �X�V
	void Update();

	/// @brief �`��
	void Draw();

  /// @brief ���C�����[�v
  void MainLoop();

protected:
private:
  HINSTANCE instance_handle_;

  snlib::WindowModule* window_;

  snlib::FrameKeeper* frame_keeper_;

  snlib::DirectX9Module* renderer_;

  TestScene* test_scene_;
};