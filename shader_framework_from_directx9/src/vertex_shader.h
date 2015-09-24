#pragma once

#include "shader_base.h"

class VertexShader : public ShaderBase {
public:
	/// @brief コンストラクタ
	VertexShader(LPDIRECT3DDEVICE9 device, char* filename) :
		ShaderBase(device, filename) {
		HRESULT ret;
		ret = device->CreateVertexShader((const DWORD*)raw_data_, &vertex_shader_);
		_ASSERT_EXPR(SUCCEEDED(ret), L"頂点シェーダだめ");
	}

	/// @brief デストラクタ
	virtual ~VertexShader() {
		vertex_shader_->Release();
	}

	/// @brief 頂点シェーダー設定
	void SetVertexShader(LPDIRECT3DDEVICE9 device) {
		device->SetVertexShader(vertex_shader_);
	}

protected:
private:
	LPDIRECT3DVERTEXSHADER9 vertex_shader_;
};