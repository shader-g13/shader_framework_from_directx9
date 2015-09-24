#pragma once

#include <Windows.h>
#include <WindowModule.h>
#include <FrameKeeper.h>
#include "renderer.h"
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

	Renderer* renderer_;

  TestScene* test_scene_;
};