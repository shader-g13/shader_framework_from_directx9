#pragma once

#include <Windows.h>
#include "renderer.h"
#include "perth_matrix.h"
#include "view_matrix.h"
#include "vertex_shader.h"
#include "pixel_shader.h"
#include "plane.h"
#include "xmodel.h"

class Application {
public:
	/// @brief コンストラクタ
	Application();

	/// @brief デストラクタ
	virtual ~Application();

	/// @brief 初期化
	void Initialize(HWND window_handle);

	/// @brief 終了
	void Finalize();

	/// @brief 更新
	void Update();

	/// @brief 描画
	void Draw();

protected:
private:
	bool is_initialize_;
	Renderer* renderer_;

	HWND window_handle_;

	VertexShader* vs_;
	PixelShader* ps_;

	PerthMatrix perth_;
	ViewMatrix view_;

	Plane* plane_;
	XModel* model_;
};