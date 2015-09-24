/// @file DirectX9Module.h
/// @brief DirectX9モジュール
/// @data 2015/04/16
/// @author syuki nishida

#pragma once
#ifndef SNLIB_DIRECTX9_MODULE_H_
#define SNLIB_DIRECTX9_MODULE_H_

#include <d3d9.h>

/// @namespace snlib
namespace snlib {

/// @class DirectX9Module
class DirectX9Module {
public:
	/// @fn DirectX9Module
	/// @brief デフォルトコンストラクタ
	/// @param[in] window_handle ウィンドウハンドル
	/// @param[in] windable ウィンドウモードか
	DirectX9Module(HWND window_handle, bool windable = true);

	/// @fn Initialize
	/// @brief 初期化
	/// @return 成功：true
	bool Initialize();

	/// @fn Finalize
	/// @brief 終了
	void Finalize();

	/// @fn BeginScene
	/// @brief 描画開始
	/// @return 描画開始：true
	bool BeginScene();

	/// @fn EndScene
	/// @brief 描画終了
	void EndScene();

	/// @fn SwitchWindowMode
	/// @brief ウィンドウモード切り替え
	void SwitchWindowMode();

	/// @fn GetDevice
	/// @brief デバイス取得
	/// @return デバイス
	__forceinline const LPDIRECT3DDEVICE9 GetDevice() {
		return device_;
	}

	/// @fn GetBufferWidth
	/// @brief バッファ幅取得
	/// @return バッファ幅
	__forceinline UINT GetBufferWidth() {
		return present_params_.BackBufferWidth;
	}

	/// @fn GetBufferHeight
	/// @brief バッファ高さ取得
	/// @return バッファ高さ
	__forceinline UINT GetBufferHeight() {
		return present_params_.BackBufferHeight;
	}

private:
	HWND window_handle_;
	bool windable_;
	D3DPRESENT_PARAMETERS present_params_;

	LPDIRECT3D9       direct3d9_;
	D3DDISPLAYMODE    display_mode_;
	LPDIRECT3DDEVICE9 device_;

protected:
};

} // namespace snlib

#endif // SNLIB_DIRECTX9_MODULE_H_

//EOF