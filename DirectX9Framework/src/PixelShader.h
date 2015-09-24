/// @file PixelShader.h
/// @brief �s�N�Z���V�F�[�_
/// @date 2014/11/30
/// @author syuki nishida
#pragma once
#ifndef SNLIB_PIXEL_SHADER_H_
#define SNLIB_PIXEL_SHADER_H_

#include "ShaderBase.h"

/// @namespace snlib
namespace snlib {

/// @class PixelShader
/// @brief �s�N�Z���V�F�[�_
class PixelShader : public ShaderBase {
public:
	/// @fn PixelShader
	/// @brief �f�t�H���g�R���X�g���N�^
	/// @param[in] device �f�o�C�X
	/// @param[in] shader_name �V�F�[�_�t�@�C����
	PixelShader(LPDIRECT3DDEVICE9 device, const char* shader_name)
	 : ShaderBase(shader_name),
	   pixel_shader_(nullptr) {
		HRESULT ret = 0;
		ret = device->CreatePixelShader(code_, &pixel_shader_);
		_ASSERT_EXPR(SUCCEEDED(ret), L"create pixelshader failed");
	}

	/// @fn ~PixelShader
	/// @brief �f�t�H���g�f�X�g���N�^
	virtual ~PixelShader() {
		pixel_shader_->Release();
	}

	/// @fn SetPixelShader
	/// @brief �V�F�[�_�ݒ�
	/// @param[in] device �f�o�C�X
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