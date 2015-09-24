#pragma once

#include <Windows.h>
#include <WindowModule.h>
#include <FrameKeeper.h>
#include "renderer.h"
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

	Renderer* renderer_;

  TestScene* test_scene_;
};