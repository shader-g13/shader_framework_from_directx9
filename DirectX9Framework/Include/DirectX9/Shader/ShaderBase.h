/// @file ShaderBase.h
/// @brief シェーダベース
/// @date 2015/02/27
/// @author syuki nishida

#pragma once
#ifndef SNLIB_SHADER_BASE_H_
#define SNLIB_SHADER_BASE_H_

#include <stdio.h>
#include <d3dx9.h>
#include <crtdbg.h>

/// @namespace snlib
namespace snlib {

/// @class ShaderBase
class ShaderBase {
public:
	/// @fn ShaderBase
	/// @brief コンストラクタ
	/// @param[in] shader_name シェーダファイル名
	ShaderBase(const char* shader_name)
	 : constant_table_(nullptr),
	   code_(nullptr) {
		HRESULT ret = 0;
		FILE* fp = nullptr;
		fopen_s(&fp, shader_name, "rb");
		_ASSERT_EXPR(fp, L"shader file not found シェーダファイルがありません");
		fseek(fp, 0, SEEK_END);
		UINT size = ftell(fp);
		fseek(fp, SEEK_SET, 0);
		code_ = new DWORD[size / sizeof(DWORD)];
		fread_s(code_, size, size, 1, fp);
		fclose(fp);
		ret = D3DXGetShaderConstantTable(code_, &constant_table_);
		_ASSERT_EXPR(SUCCEEDED(ret), L"acquire constant table failed");
	}

	/// @fn ~ShaderBase
	/// @brief デストラクタ
	virtual ~ShaderBase() {
		constant_table_->Release();
		delete[] code_;
	}

	/// @fn GetHandle
	/// @brief 定数ハンドル取得
	/// @param[in] value_name 取得したい定数名
	/// @param[in] parent 親階層がある場合指定
	D3DXHANDLE GetHandle(const char* const_name, D3DXHANDLE parent = nullptr) {
		D3DXHANDLE ret = constant_table_->GetConstantByName(parent, const_name);
		_ASSERT_EXPR(ret, L"ShaderBase : ハンドルが取得できませんでした。");
		return ret;
	}

	/// @fn GetConstantTable
	/// @brief コンスタントテーブル取得
	/// @return コンスタントテーブル
	LPD3DXCONSTANTTABLE GetConstantTable() {
		return constant_table_;
	}

	/// @fn SetValue
	/// @brief 値設定
	/// @param[in] device デバイス
	/// @param[in] handle 設定したい値のハンドル
	/// @param[in] value 値
	/// @param[in] count 個数
	void SetValue(LPDIRECT3DDEVICE9 device,
		const D3DXHANDLE& handle, const D3DXMATRIX* value) {
		constant_table_->SetMatrix(device, handle, value);
	}

	void SetValue(LPDIRECT3DDEVICE9 device,
		const D3DXHANDLE& handle, const float value) {
		constant_table_->SetFloat(device, handle, value);
	}

	void SetValue(LPDIRECT3DDEVICE9 device,
		const D3DXHANDLE& handle, const float* value, const UINT& count) {
		constant_table_->SetFloatArray(device, handle, value, count);
	}

	void SetValue(LPDIRECT3DDEVICE9 device,
		const D3DXHANDLE& handle, D3DXVECTOR4 value) {
		constant_table_->SetVector(device, handle, &value);
	}
	void SetValue(LPDIRECT3DDEVICE9 device,
		const D3DXHANDLE& handle, D3DXMATRIX* mtx, UINT count) {
		constant_table_->SetMatrixArray(device, handle, mtx, count);
	}

protected:
	LPD3DXCONSTANTTABLE constant_table_;
	DWORD* code_;

private:
};

} // namespace snlib

#endif // SNLIB_SHADER_BASE_H_

//EOF