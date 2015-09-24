/// @file LightShaderInterface.h
/// @brief ライトシェーダのインターフェース
/// @date 2015/05/10
/// @author syuki nishida

#pragma once
#ifndef SNLIB_LIGHT_SHADER_INTERFACE_H_
#define SNLIB_LIGHT_SHADER_INTERFACE_H_

#include <crtdbg.h>
#include <d3dx9.h>

/// @namespace snlib
namespace snlib {

/// @class LightShaderInterface
class LightShaderInterface {
public:
	/// @fn LightShaderInterface
	/// @brief デフォルトコンストラクタ
	/// @param[in] constant_table 定数テーブル
	LightShaderInterface(LPD3DXCONSTANTTABLE constant_table)
	 : constant_table_(constant_table) {
		direction_handle_ = constant_table_->GetConstantByName(nullptr, "LightDirection");
		diffuse_handle_ = constant_table_->GetConstantByName(nullptr, "LightDiffuse");
  ambient_handle_ = constant_table_->GetConstantByName(nullptr,"LightAmbient");
  position_handle_ = constant_table_->GetConstantByName(nullptr,"LightPosition");
  specDiffuse_handle_ = constant_table_->GetConstantByName(nullptr,"SpecDiffuse");
  specMaterial_handle_ = constant_table_->GetConstantByName(nullptr,"SpecMatDiffuse");
  specPower_handle_ = constant_table_->GetConstantByName(nullptr,"SpecPower");
	}

	/// @fn ~LightShaderInterface
	/// @brief デフォルトデストラクタ
	virtual ~LightShaderInterface() {}

	/// @fn SetLightDirection
	/// @brief ライトベクトル設定
	/// @param[in] direction ライトベクトル
	void SetLightDirection(const D3DXVECTOR3& direction) {
		direction_.x = direction.x;
		direction_.y = direction.y;
		direction_.z = direction.z;
	}

	/// @fn SetLightDiffuse
	/// @brief ディフューズカラー設定
	/// @param[in] diffuse ディフューズカラー
	void SetLightDiffuse(const D3DXVECTOR3& diffuse) {
		diffuse_.x = diffuse.x;
		diffuse_.y = diffuse.y;
		diffuse_.z = diffuse.z;
	}

	/// @fn SetLightAmbient
	/// @brief アンビエントカラー設定
	/// @param[in] ambient アンビエントカラー
	void SetLightAmbient(const D3DXVECTOR3& ambient) {
		ambient_.x = ambient.x;
		ambient_.y = ambient.y;
		ambient_.z = ambient.z;
	}
 void SetLightPosition(const D3DXVECTOR3& ambient) {
  position_.x = ambient.x;
  position_.y = ambient.y;
  position_.z = ambient.z;
 }
 void SetSpecDiffuse(const D3DXVECTOR3& ambient) {
  specDiffuse_.x = ambient.x;
  specDiffuse_.y = ambient.y;
  specDiffuse_.z = ambient.z;
 }
 void SetSpecAmbient(const D3DXVECTOR3& ambient) {
  specMaterial_.x = ambient.x;
  specMaterial_.y = ambient.y;
  specMaterial_.z = ambient.z;
 }
 void SetSpecPower(const float specPower){
  specPower_ = specPower;
 }

	/// @fn Apply
	/// @brief コンスタントテーブルに値適応
	/// @param[in] device デバイス
	void Apply(LPDIRECT3DDEVICE9 device) {
		_ASSERT_EXPR(constant_table_, L"snlib LightShaderInterhace error "
			L"初期化されずに使用されている");
		constant_table_->SetVector(device, direction_handle_, &direction_);
		constant_table_->SetVector(device, diffuse_handle_, &diffuse_);
  constant_table_->SetVector(device,ambient_handle_,&ambient_);
  constant_table_->SetVector(device,ambient_handle_,&position_);
  constant_table_->SetVector(device,ambient_handle_,&specDiffuse_);
  constant_table_->SetVector(device,ambient_handle_,&specMaterial_);
  constant_table_->SetFloat(device,ambient_handle_,specPower_);
	}

protected:
private:
	LPD3DXCONSTANTTABLE constant_table_;

	D3DXVECTOR4 direction_;
	D3DXVECTOR4 diffuse_;
 D3DXVECTOR4 ambient_;
 D3DXVECTOR4 position_;
 D3DXVECTOR4 specDiffuse_;
 D3DXVECTOR4 specMaterial_;
 float specPower_;

	D3DXHANDLE direction_handle_;
	D3DXHANDLE diffuse_handle_;
 D3DXHANDLE ambient_handle_;
 D3DXHANDLE position_handle_;
 D3DXHANDLE specDiffuse_handle_;
 D3DXHANDLE specMaterial_handle_;
 D3DXHANDLE specPower_handle_;
};

} // namespace snlib

#endif // SNLIB_LIGHT_SHADER_INTERFACE_H_

//EOF