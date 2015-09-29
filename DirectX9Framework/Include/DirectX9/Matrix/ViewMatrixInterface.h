/// @file ViewMatrixInterface.h
/// @brief ビュー行列インターフェース
/// @date 2015/05/07
/// @author syuki nishida

#pragma once
#ifndef SNLIB_VIEW_MATRIX_INTERFACE_H_
#define SNLIB_VIEW_MATRIX_INTERFACE_H_

#include <d3dx9.h>
#pragma comment(lib, "d3dx9.lib")

/// @namespace snlib
namespace snlib {
/// @class ViewMatrixInerface
/// @brief ビュー行列インターフェース
class ViewMatrixInterface {
public:
	/// @fn ViewMatixInterface
	/// @brief コンストラクタ
	ViewMatrixInterface() : eye_(0, 0, -1), at_(0, 0, 0), up_(0, 1, 0) {
		D3DXMatrixIdentity(&view_);
	}

	/// @fn ~ViewMatrixInterface
	/// @brief デストラクタ
	virtual ~ViewMatrixInterface() {}

	/// @fn CreateView
	/// @brief ビュー行列作成
	/// @return ビュー行列
	const D3DXMATRIX CreateView() {
		D3DXMatrixLookAtLH(&view_, &eye_, &at_, &up_);
		return view_;
	}

	/// @fn SetEye
	/// @brief 視点設定
	/// @param[in] eye 設定したい視点
	void SetEye(const D3DXVECTOR3& eye) { eye_ = eye; }

	/// @fn SetAt
	/// @brief 注視点設定
	/// @param[in] at 設定したい注視点
	void SetAt(const D3DXVECTOR3& at) { at_ = at; }

	/// @fn SetUp
	/// @brief 上方向設定
	/// @param[in] up 設定したい上方向
	void SetUp(const D3DXVECTOR3& up) { up_ = up; }

	/// @fn GetEye
	/// @brief 視点取得
	/// @return 視点
	const D3DXVECTOR3& GetEye() { return eye_; }

	/// @fn GetAt
	/// @brief 注視点取得
	/// @return 注視点
	const D3DXVECTOR3& GetAt() { return at_; }

	/// @fn GetUp
	/// @brief 上方向取得
	/// @return 上方向
	const D3DXVECTOR3& GetUp() { return up_; }

	/// @fn D3DXMATRIX
	/// @brief D3DXMATRIXのオペレータ
	/// @retunr ビュー行列
	operator const D3DXMATRIX&() { return view_; }

protected:
	D3DXVECTOR3 eye_;
	D3DXVECTOR3 at_;
	D3DXVECTOR3 up_;

private:
	D3DXMATRIX view_;

};

} // namespace snlib

#endif // SNLIB_VIEW_MATRIX_INTERFACE_H_

//EOF