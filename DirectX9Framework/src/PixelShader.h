/// @file PixelShader.h
/// @brief ピクセルシェーダ
/// @date 2014/11/30
/// @author syuki nishida
#pragma once
#ifndef SNLIB_PIXEL_SHADER_H_
#define SNLIB_PIXEL_SHADER_H_

#include "ShaderBase.h"

/// @namespace snlib
namespace snlib {

/// @class PixelShader
/// @brief ピクセルシェーダ
class PixelShader : public ShaderBase {
public:
	/// @fn PixelShader
	/// @brief デフォルトコンストラクタ
	/// @param[in] device デバイス
	/// @param[in] shader_name シェーダファイル名
	PixelShader(LPDIRECT3DDEVICE9 device, const char* shader_name)
	 : ShaderBase(shader_name),
	   pixel_shader_(nullptr) {
		HRESULT ret = 0;
		ret = device->CreatePixelShader(code_, &pixel_shader_);
		_ASSERT_EXPR(SUCCEEDED(ret), L"create pixelshader failed");
	}

	/// @fn ~PixelShader
	/// @brief デフォルトデストラクタ
	virtual ~PixelShader() {
		pixel_shader_->Release();
	}

	/// @fn SetPixelShader
	/// @brief シェーダ設定
	/// @param[in] device デバイス
	void SetPixelShader(LPDIRECT3DDEVICE9 device) {
		device->SetPixelShader(pixel_shader_);
	}

protected:
private:
	LPDIRECT3DPIXELSHADER9 pixel_shader_;

};

} // namespace snlib

#endif // SNLIB_PIXEL_SHADER_H_

//EOF