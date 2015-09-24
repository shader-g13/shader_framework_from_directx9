#pragma once

#include "shader_base.h"

class PixelShader : public ShaderBase {
public:
	/// @brief �R���X�g���N�^
	PixelShader(LPDIRECT3DDEVICE9 device, char* filename) :
		ShaderBase(device, filename) {
		HRESULT ret;
		ret = device->CreatePixelShader((const DWORD*)raw_data_, &pixel_shader_);
		_ASSERT_EXPR(SUCCEEDED(ret), L"�s�N�Z���V�F�[�_����");
	}

	/// @brief �f�X�g���N�^
	virtual ~PixelShader() {
		pixel_shader_->Release();
	}

	/// @brief �s�N�Z���V�F�[�_�[�ݒ�
	void SetPixelShader(LPDIRECT3DDEVICE9 device) {
		device->SetPixelShader(pixel_shader_);
	}

protected:
private:
	LPDIRECT3DPIXELSHADER9 pixel_shader_;
};