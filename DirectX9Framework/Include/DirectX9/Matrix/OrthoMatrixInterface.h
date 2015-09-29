/// @file OrthoMatrixInterface.h
/// @brief オルソー行列インターフェース
/// @date 2015/06/11
/// @author syuki nishida

#pragma once
#ifndef SNLIB_ORTHO_MATRIX_INTERFACE_H_
#define SNLIB_ORTHO_MATRIX_INTERFACE_H_

#include <d3dx9.h>
#pragma comment(lib, "d3dx9.lib")

/// @namespace snlib
namespace snlib {

/// @class OrthoMatrixInerface
/// @brief オルソー行列インターフェース
class OrthoMatrixInterface {
public:
	///@fn OrthoMatixInterface
	/// @brief コンストラクタ
	OrthoMatrixInterface() {
		D3DXMatrixIdentity(&ortho_);
	}

	/// @fn ~OrthoMatrixInterface
	/// @brief デストラクタ
	virtual ~OrthoMatrixInterface() {}

	/// @fn CreateOrtho
	/// @brief オルソー行列作成
	/// @return オルソー行列
	const D3DXMATRIX CreateOrtho() {
		D3DXMatrixOrthoLH(&ortho_, width_, height_, near_, far_);
		return ortho_;
	}

	/// @fn SetWidth
	/// @brief 幅設定
	/// @param[in] width 設定したい幅
	void SetWidth(float width) { width_ = width; }

	/// @fn SetHeight
	/// @brief 幅設定
	/// @param[in] height 設定したい高さ
	void SetHeight(float height) { height_ = height; }

	/// @fn SetNear
	/// @brief 近クリップ設定
	/// @param[in] znear 設定したい近クリップ
	void SetNear(float znear) { near_ = znear; }

	/// @fn SetFar
	/// @brief 遠クリップ設定
	/// @param[in] zfar 設定したい遠クリップ
	void SetFar(float zfar) { far_ = zfar; }

	/// @fn GetWidth
	/// @brief 幅取得
	/// @return 幅
	float GetWidth() { return width_; }

	/// @fn GetHeight
	/// @brief 高さ取得
	/// @return 高さ
	float GetHeight() { return height_; }

	/// @fn GetNear
	/// @brief 近クリップ取得
	/// @return 近クリップ
	float GetNear() { return near_; }

	/// @fn GetFar
	/// @brief 遠クリップ取得
	// @return 遠クリップ
	float GetFar() { return far_; }

	/// @fn D3DXMATRIX
	/// @brief D3DXMATRIXのオペレータ
	/// @return オルソー行列
	operator const D3DXMATRIX&() { return ortho_; };

protected:
	float width_;
	float height_;
	float near_;
	float far_;

private:
	D3DXMATRIX ortho_;

};

} // namespace snlib

#endif // SNLIB_ORTHO_MATRIX_INTERFACE_H_

//EOF