#pragma once

#include <d3dx9.h>

class ViewMatrix {
public:
	/// @brief コンストラクタ
  ViewMatrix() :
		eye_(0, 100, -100),
		at_(0, 0, 0),
		up_(0, 1, 0) {
	}

	/// @brief デストラクタ
  virtual ~ViewMatrix() {}

	/// @brief セッター
	void SetEye(D3DXVECTOR3 eye) { eye_ = eye; }
	void SetAt(D3DXVECTOR3 at) { at_ = at; }
	void SetUp(D3DXVECTOR3 up) { up_ = up; }

	/// @brief ゲッター
	D3DXVECTOR3& GetEye() { return eye_; }
	D3DXVECTOR3& GetAt() { return at_; }
	D3DXVECTOR3& GetUp() { return up_; }

	/// @brief 行列作成
	D3DXMATRIX& CreateViewMatrix() {
		D3DXMatrixLookAtLH(&matrix_, &eye_, &at_ ,&up_);
		return matrix_;
	}

protected:
private:
	D3DXMATRIX matrix_;

	D3DXVECTOR3 eye_;
	D3DXVECTOR3 at_;
	D3DXVECTOR3 up_;
};