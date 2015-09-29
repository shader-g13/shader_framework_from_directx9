/// @file PerthMatrixInterface.h
/// @brief パース行列インターフェース
/// @date 2015/02/26
/// @author syuki nishida

#pragma once
#ifndef SNLIB_PERTH_MATRIX_INTERFACE_H_
#define SNLIB_PERTH_MATRIX_INTERFACE_H_

#include <d3dx9.h>
#pragma comment(lib, "d3dx9.lib")

/// @namespace snlib
namespace snlib {

/// @class PerthMatrixInerface
/// @brief パース行列インターフェース
class PerthMatrixInterface {
public:
	///@fn PerthMatixInterface
	/// @brief コンストラクタ
	PerthMatrixInterface() {
		D3DXMatrixIdentity(&perth_);
	}

	/// @fn ~PerthMatrixInterface
	/// @brief デストラクタ
	virtual ~PerthMatrixInterface() {}

	/// @fn CreatePerth
	/// @brief パース行列作成
	/// @return パース行列
	const D3DXMATRIX CreatePerth() {
		D3DXMatrixPerspectiveFovLH(&perth_, fov_, aspect_, near_, far_);
		return perth_;
	}

	/// @fn SetFov
	/// @brief 画角設定
	/// @param[in] fov 設定したい画角
	void SetFov(float fov) { fov_ = fov; }

	/// @fn SetAspect
	/// @brief 画面比設定
	/// @param[in] aspect 設定したい画面比率
	void SetAspect(float aspect) { aspect_ = aspect; }

	/// @fn SetNear
	/// @brief 近クリップ設定
	/// @param[in] znear 設定したい近クリップ
	void SetNear(float znear) { near_ = znear; }

	/// @fn SetFar
	/// @brief 遠クリップ設定
	/// @param[in] zfar 設定したい遠クリップ
	void SetFar(float zfar) { far_ = zfar; }

	/// @fn GetFov
	/// @brief 画角取得
	/// @return 画角
	float GetFov() { return fov_; }

	/// @fn GetAspect
	/// @brief 画面比率取得
	/// @return 画面比率
	float GetAspect() { return aspect_; }

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
	/// @return パース行列
	operator const D3DXMATRIX&() { return perth_; };

protected:
	float fov_;
	float aspect_;
	float near_;
	float far_;

private:
	D3DXMATRIX perth_;

};

} // namespace snlib

#endif // SNLIB_PERTH_MATRIX_INTERFACE_H_

//EOF