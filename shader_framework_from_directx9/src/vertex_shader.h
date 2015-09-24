#pragma once

#include "shader_base.h"

class VertexShader : public ShaderBase {
public:
	/// @brief �R���X�g���N�^
	VertexShader(LPDIRECT3DDEVICE9 device, char* filename) :
		ShaderBase(device, filename) {
		HRESULT ret;
		ret = device->CreateVertexShader((const DWORD*)raw_data_, &vertex_shader_);
		_ASSERT_EXPR(SUCCEEDED(ret), L"���_�V�F�[�_����");
	}

	/// @brief �f�X�g���N�^
	virtual ~VertexShader() {
		vertex_shader_->Release();
	}

	/// @brief ���_�V�F�[�_�[�ݒ�
	void SetVertexShader(LPDIRECT3DDEVICE9 device) {
		device->SetVertexShader(vertex_shader_);
	}

protected:
private:
	LPDIRECT3DVERTEXSHADER9 vertex_shader_;
};