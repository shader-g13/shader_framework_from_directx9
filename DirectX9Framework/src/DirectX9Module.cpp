/// @file DirectX9Module.cpp
/// @brief DirectX9モジュール
/// @data 2015/04/16
/// @author syuki nishida

#include "DirectX9Module.h"
#include <crtdbg.h>

#pragma comment(lib, "d3d9.lib")
#include <DxErr.h>
#pragma comment(lib, "dxerr.lib")

/// @namespace snlib
namespace snlib {

/// @fn DirectX9Module
/// @brief デフォルトコンストラクタ
/// @param[in] window_handle ウィンドウハンドル
/// @param[in] windable ウィンドウモードか
DirectX9Module::DirectX9Module(HWND window_handle, bool windable)
 : window_handle_(window_handle),
   windable_(windable),
   direct3d9_(nullptr),
   device_(nullptr) {
}

/// @fn Initialize
/// @brief 初期化
/// @return 成功：true
bool DirectX9Module::Initialize() {
	if (device_) return false;

	HRESULT result;
	direct3d9_ = Direct3DCreate9(D3D_SDK_VERSION);
	_ASSERT_EXPR(direct3d9_,
		L"snlib DirectX9Module error DirectXCreate9 is failed");
	if (!direct3d9_) return false;

	result = direct3d9_->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &display_mode_);
	if (FAILED(result)) {
		_ASSERT_EXPR(SUCCEEDED(result),
			L"snlib DirectX9Module error "
			L"get display mode is failed");
		direct3d9_->Release();
		direct3d9_ = nullptr;
		return false;
	}

	RECT client_size;
	GetClientRect(window_handle_, &client_size);

	present_params_.BackBufferWidth = client_size.right - client_size.left;
	present_params_.BackBufferHeight = client_size.bottom - client_size.top;
	present_params_.BackBufferFormat = display_mode_.Format;
	present_params_.BackBufferCount = 1;

	present_params_.MultiSampleType = D3DMULTISAMPLE_NONE;
	present_params_.MultiSampleQuality = 0;

	present_params_.SwapEffect = D3DSWAPEFFECT_DISCARD;
	present_params_.hDeviceWindow = nullptr;
	present_params_.Windowed = windable_;
	present_params_.EnableAutoDepthStencil = true;
	present_params_.AutoDepthStencilFormat = D3DFMT_D24S8;
	present_params_.Flags = 0;

	if (windable_) {
		present_params_.FullScreen_RefreshRateInHz = 0;
		present_params_.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	}
	else {
		present_params_.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		present_params_.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	}

	result = direct3d9_->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		window_handle_,
		D3DCREATE_MIXED_VERTEXPROCESSING,
		&present_params_,
		&device_);

	if (SUCCEEDED(result)) return true;

	_ASSERT_EXPR(SUCCEEDED(result),
		L"snlib DirectX9Module error"
		L"CreateDevice is failed");

	_ASSERT_EXPR(SUCCEEDED(result), DXGetErrorDescription(result));

	direct3d9_->Release();
	direct3d9_ = nullptr;
	return false;
}

/// @fn Finalize
/// @brief 終了
void DirectX9Module::Finalize() {
	if (!device_) return;

	ULONG reference_counter;
	reference_counter = device_->Release();

	_ASSERT_EXPR(!reference_counter,
		L"snlib DirectX9Module error"
		L"Those that use the device may not be released.");
	device_ = nullptr;

	reference_counter = direct3d9_->Release();
	_ASSERT_EXPR(!reference_counter,
		L"snlib DirectX9Module error"
		L"Those that use the direct3d9 may not be released.");
	direct3d9_ = nullptr;
}

/// @fn BeginScene
/// @brief 描画開始
/// @return 描画開始：true
bool DirectX9Module::BeginScene() {
	device_->Clear(0, nullptr, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(50, 0, 50, 0), 1.0f, 0);
	return SUCCEEDED(device_->BeginScene());
}

/// @fn EndScene
/// @brief 描画終了
void DirectX9Module::EndScene() {
	device_->EndScene();
	device_->Present(nullptr, nullptr, nullptr, nullptr);
}

/// @fn SwitchWindowMode
/// @brief ウィンドウモード切り替え
void DirectX9Module::SwitchWindowMode() {
	windable_ ^= true;
	present_params_.Windowed = windable_;
	if (windable_) {
		present_params_.BackBufferFormat = D3DFMT_UNKNOWN;
		present_params_.FullScreen_RefreshRateInHz = 0;
		present_params_.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	}
	else {
		present_params_.BackBufferFormat = D3DFMT_X8R8G8B8;
		present_params_.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		present_params_.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	}
	HRESULT result = device_->Reset(&present_params_);
	_ASSERT_EXPR(SUCCEEDED(result), DXGetErrorDescription(result));

	if (windable_) {
		SetWindowLong(window_handle_, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE);
	}
	else {
		SetWindowLong(window_handle_, GWL_STYLE, WS_POPUP | WS_VISIBLE);
	}
}

}; // namespace snlib

//EOF