/// @file TransformShaderInterface.h
/// @brief トランスフォームシェーダインターフェース
/// @date 2015/05/10
/// @author syuki nishida

#pragma once
#ifndef SNLIB_TRANSFORM_SHADER_INTERFACE_H_
#define SNLIB_TRANSFORM_SHADER_INTERFACE_H_

#include <crtdbg.h>
#include <d3dx9.h>

/// @namespace snlib
namespace snlib {

/// @class TransformShaderInterface
class TransformShaderInterface {
public:
	/// @fn TransformShaderInterface
	/// @brife デフォルトコンストラクタ
	/// @param[in] constant_table 定数テーブル
	TransformShaderInterface(LPD3DXCONSTANTTABLE constant_table)
	 : constant_table_(constant_table) {
		world_handle_ = constant_table_->GetConstantByName(nullptr, "WorldMatrix");
		view_handle_ = constant_table_->GetConstantByName(nullptr, "ViewMatrix");
		proj_handle_ = constant_table_->GetConstantByName(nullptr, "ProjectionMatrix");
	}

	/// @fn ~TransformShaderInterface
	/// @brife デフォルトデストラクタ
	virtual ~TransformShaderInterface() {}

	/// @fn SetWorldMatrix
	/// @brief ワールド行列設定
	/// @param[in] world ワールド行列
	void SetWorldMatrix(const D3DXMATRIX& world) {
		world_ = world;
	}

	/// @fn SetViewMatrix
	/// @brief ビュー行列設定
	/// @param[in] view ビュー行列
	void SetViewMatrix(const D3DXMATRIX& view) {
		view_ = view;
	}

	/// @fn SetProjectionMatrix
	/// @brief プロジェクション行列設定
	/// @param[in] projection プロジェクション行列
	void SetProjectionMatrix(const D3DXMATRIX& projection) {
		proj_ = projection;
	}

	/// @fn Apply
	/// @brief コンスタントテーブルに値適応
	/// @param[in] device デバイス
	void Apply(LPDIRECT3DDEVICE9 device) {
		_ASSERT_EXPR(constant_table_, L"snlib TransformShaderInterhace error "
			L"初期化されずに使用されている");
		constant_table_->SetMatrix(device, world_handle_, &world_);
		constant_table_->SetMatrix(device, view_handle_, &view_);
		constant_table_->SetMatrix(device, proj_handle_, &proj_);
	}

protected:
private:
	LPD3DXCONSTANTTABLE constant_table_;

	D3DXMATRIX world_;
	D3DXMATRIX view_;
	D3DXMATRIX proj_;

	D3DXHANDLE world_handle_;
	D3DXHANDLE view_handle_;
	D3DXHANDLE proj_handle_;
};

} // namespace snlib

#endif // SNLIB_TRANSFORM_SHADER_INTERFACE_H_

//EOF