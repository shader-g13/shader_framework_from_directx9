/// @file MaterialShaderInterface.h
/// @brief マテリアルシェーダインターフェース
/// @date 2015/05/10
/// @author syuki nishida

#pragma once
#ifndef SNLIB_MATERIAL_LIGHTING_SHADER_INTERFACE_H_
#define SNLIB_MATERIAL_LIGHTING_SHADER_INTERFACE_H_

#include <crtdbg.h>
#include <d3dx9.h>

/// @namespace snlib
namespace snlib {

/// @class MaterialShaderInterface
class MaterialShaderInterface {
public:
	/// @fn MaterialShaderInterface
	/// @brief デフォルトコンストラクタ
	/// @param[in] constant_table コンスタントテーブル
	MaterialShaderInterface(LPD3DXCONSTANTTABLE constant_table)
	 : constant_table_(constant_table) {
		diffuse_handle_ = constant_table_->GetConstantByName(nullptr, "MaterialDiffuse");
		ambient_handle_ = constant_table_->GetConstantByName(nullptr, "MaterialAmbient");
	}

	/// @fn ~MaterialShaderInterface
	virtual ~MaterialShaderInterface() {}

	/// @fn SetLightDiffuse
	/// @brief ディフューズカラー設定
	/// @param[in] diffuse ディフューズカラー
	void SetMaterialDiffuse(const D3DCOLORVALUE& diffuse) {
		diffuse_.x = diffuse.r;
		diffuse_.y = diffuse.g;
		diffuse_.z = diffuse.b;
		diffuse_.w = diffuse.a;
	}

	/// @fn SetLightAmbient
	/// @brief アンビエントカラー設定
	/// @param[in] ambient アンビエントカラー
	void SetMaterialAmbient(const D3DCOLORVALUE& ambient) {
		ambient_.x = ambient.r;
		ambient_.y = ambient.g;
		ambient_.z = ambient.b;
		ambient_.w = ambient.a;
	}

	/// @fn Apply
	/// @brief コンスタントテーブルに値適応
	/// @param[in] device デバイス
	void Apply(LPDIRECT3DDEVICE9 device) {
		_ASSERT_EXPR(constant_table_, L"snlib MaterialShaderInterhace error "
			L"初期化されずに使用されている");
		constant_table_->SetVector(device, diffuse_handle_, &diffuse_);
		constant_table_->SetVector(device, ambient_handle_, &ambient_);
	}

protected:
private:
	LPD3DXCONSTANTTABLE constant_table_;

	D3DXVECTOR4 diffuse_;
	D3DXVECTOR4 ambient_;

	D3DXHANDLE diffuse_handle_;
	D3DXHANDLE ambient_handle_;
};

} // namespace snlib

#endif // MATERIAL_SHADER_INTERFACE_H_

//EOF