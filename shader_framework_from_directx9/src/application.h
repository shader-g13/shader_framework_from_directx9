#pragma once

#include <Windows.h>
#include <Win32Api/WindowModule.h>
#include <Util/FrameKeeper.h>
#include <DirectX9/Rendering/DirectX9module.h>
#include "test_scene.h"

class Application {
public:
	/// @brief コンストラクタ
  Application(HINSTANCE instance_handle);

	/// @brief デストラクタ
	virtual ~Application();

	/// @brief 更新
	void Update();

	/// @brief 描画
	void Draw();

  /// @brief メインループ
  void MainLoop();

protected:
private:
  HINSTANCE instance_handle_;

  snlib::WindowModule* window_;

  snlib::FrameKeeper* frame_keeper_;

  snlib::DirectX9Module* renderer_;

  TestScene* test_scene_;
};