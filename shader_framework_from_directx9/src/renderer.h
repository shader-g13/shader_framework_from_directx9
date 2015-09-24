#pragma once

#include <d3d9.h>

class Renderer {
public:
	/// @brief コンストラクタ
	Renderer();

	/// @brief デストラクタ
	virtual ~Renderer();

	/// @brief 初期化
	void Initialize(HWND window_handle, UINT buffer_width, UINT buffer_heignt, bool windable = true);

	/// @biref 終了
	void Finalize();

	/// @brief 描画開始
	void BegenDraw();

	/// @brief 描画終了
	void EndDraw();

	/// @brief デバイス取得
	LPDIRECT3DDEVICE9 GetDevice() { return device_; }

protected:
private:
	LPDIRECT3D9 direct3d_;
	LPDIRECT3DDEVICE9 device_;

	bool windable_;
	UINT buffer_width_;
	UINT buffer_height_;
	HWND window_handle_;
};