#pragma once

#include "shader_base.h"

class PixelShader : public ShaderBase {
public:
	/// @brief コンストラクタ
	PixelShader(LPDIRECT3DDEVICE9 device, char* filename) :
		ShaderBase(device, filename) {
		HRESULT ret;
		ret = device->CreatePixelShader((const DWORD*)raw_data_, &pixel_shader_);
		_ASSERT_EXPR(SUCCEEDED(ret), L"ピクセルシェーダだめ");
	}

	/// @brief デストラクタ
	virtual ~PixelShader() {
		pixel_shader_->Release();
	}

	/// @brief ピクセルシェーダー設定
	void SetPixelShader(LPDIRECT3DDEVICE9 device) {
		device->SetPixelShader(pixel_shader_);
	}

protected:
private:
	LPDIRECT3DPIXELSHADER9 pixel_shader_;
};