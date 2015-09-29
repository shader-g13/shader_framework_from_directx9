/// @file vertex_shader.h
/// @brief 頂点シェーダ
/// @date 2015/02/27
/// @author syuki nishida
#pragma once
#ifndef SNLIB_VERTEX_SHADER_H_
#define SNLIB_VERTEX_SHADER_H_

#include "ShaderBase.h"

/// @namespace snlib
namespace snlib {

/// @class VertexShader
/// @brief 頂点シェーダ
class VertexShader : public ShaderBase {
public:
	/// @fn VertexShader
	/// @brief コンストラクタ
	/// @param[in] device デバイス
	/// @param[in] shader_name シェーダファイル名
	VertexShader(LPDIRECT3DDEVICE9 device, const char* shader_name)
	 : ShaderBase(shader_name),
	   vertex_shader_(nullptr) {
		HRESULT ret = 0;
		ret = device->CreateVertexShader(code_, &vertex_shader_);
		_ASSERT_EXPR(SUCCEEDED(ret), L"create vertexshader failed");
	}

	/// @fn ~VertexShader
	/// @brief デストラクタ
	virtual ~VertexShader() {
		vertex_shader_->Release();
	}

	/// @fn SetVertexShader
	/// @brief シェーダ設定
	/// @param[in] device デバイス
	void SetVertexShader(LPDIRECT3DDEVICE9 device) {
		device->SetVertexShader(vertex_shader_);
	}

protected:
private:
	LPDIRECT3DVERTEXSHADER9 vertex_shader_;

};

} // namespace snlib

#endif // SNLIB_VERTEX_SHADER_H_

//EOF