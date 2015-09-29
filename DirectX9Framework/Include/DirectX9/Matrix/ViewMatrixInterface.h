/// @file ViewMatrixInterface.h
/// @brief �r���[�s��C���^�[�t�F�[�X
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
/// @brief �r���[�s��C���^�[�t�F�[�X
class ViewMatrixInterface {
public:
	/// @fn ViewMatixInterface
	/// @brief �R���X�g���N�^
	ViewMatrixInterface() : eye_(0, 0, -1), at_(0, 0, 0), up_(0, 1, 0) {
		D3DXMatrixIdentity(&view_);
	}

	/// @fn ~ViewMatrixInterface
	/// @brief �f�X�g���N�^
	virtual ~ViewMatrixInterface() {}

	/// @fn CreateView
	/// @brief �r���[�s��쐬
	/// @return �r���[�s��
	const D3DXMATRIX CreateView() {
		D3DXMatrixLookAtLH(&view_, &eye_, &at_, &up_);
		return view_;
	}

	/// @fn SetEye
	/// @brief ���_�ݒ�
	/// @param[in] eye �ݒ肵�������_
	void SetEye(const D3DXVECTOR3& eye) { eye_ = eye; }

	/// @fn SetAt
	/// @brief �����_�ݒ�
	/// @param[in] at �ݒ肵���������_
	void SetAt(const D3DXVECTOR3& at) { at_ = at; }

	/// @fn SetUp
	/// @brief ������ݒ�
	/// @param[in] up �ݒ肵���������
	void SetUp(const D3DXVECTOR3& up) { up_ = up; }

	/// @fn GetEye
	/// @brief ���_�擾
	/// @return ���_
	const D3DXVECTOR3& GetEye() { return eye_; }

	/// @fn GetAt
	/// @brief �����_�擾
	/// @return �����_
	const D3DXVECTOR3& GetAt() { return at_; }

	/// @fn GetUp
	/// @brief ������擾
	/// @return �����
	const D3DXVECTOR3& GetUp() { return up_; }

	/// @fn D3DXMATRIX
	/// @brief D3DXMATRIX�̃I�y���[�^
	/// @retunr �r���[�s��
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