#pragma once

#include <d3dx9.h>

class Perth {
public:
	/// @brief コンストラクタ
	Perth():
		fov_(D3DXToRadian(45.f)),
		aspect_(4.f / 3.f),
		znear_(0.1f),
		zfar_(1000.f) {
	}

	/// @brief デストラクタ
	virtual ~Perth() {}

	/// @brief セッター
	void SetFov(float fov) { fov_ = fov; }
	void SetAsect(float aspect) { aspect_ = aspect; }
	void SetNear(float znear) { znear_ = znear; }
	void SetFar(float zfar) { zfar_ = zfar; }

	/// @brief ゲッター
	float GetFov() { return fov_; }
	float GetAsect() { return aspect_; }
	float GetNear() { return znear_; }
	float GetFar() { return zfar_; }

	/// @brief 行列作成
	D3DXMATRIX& CreatePerthMatrix() {
		D3DXMatrixPerspectiveFovLH(&matrix_, fov_, aspect_, znear_, zfar_);
		return matrix_;
	}

protected:
private:

	D3DXMATRIX matrix_;

	float fov_;
	float aspect_;
	float znear_;
	float zfar_;
};