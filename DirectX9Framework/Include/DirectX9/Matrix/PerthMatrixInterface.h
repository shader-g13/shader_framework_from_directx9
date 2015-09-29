/// @file PerthMatrixInterface.h
/// @brief �p�[�X�s��C���^�[�t�F�[�X
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
/// @brief �p�[�X�s��C���^�[�t�F�[�X
class PerthMatrixInterface {
public:
	///@fn PerthMatixInterface
	/// @brief �R���X�g���N�^
	PerthMatrixInterface() {
		D3DXMatrixIdentity(&perth_);
	}

	/// @fn ~PerthMatrixInterface
	/// @brief �f�X�g���N�^
	virtual ~PerthMatrixInterface() {}

	/// @fn CreatePerth
	/// @brief �p�[�X�s��쐬
	/// @return �p�[�X�s��
	const D3DXMATRIX CreatePerth() {
		D3DXMatrixPerspectiveFovLH(&perth_, fov_, aspect_, near_, far_);
		return perth_;
	}

	/// @fn SetFov
	/// @brief ��p�ݒ�
	/// @param[in] fov �ݒ肵������p
	void SetFov(float fov) { fov_ = fov; }

	/// @fn SetAspect
	/// @brief ��ʔ�ݒ�
	/// @param[in] aspect �ݒ肵������ʔ䗦
	void SetAspect(float aspect) { aspect_ = aspect; }

	/// @fn SetNear
	/// @brief �߃N���b�v�ݒ�
	/// @param[in] znear �ݒ肵�����߃N���b�v
	void SetNear(float znear) { near_ = znear; }

	/// @fn SetFar
	/// @brief ���N���b�v�ݒ�
	/// @param[in] zfar �ݒ肵�������N���b�v
	void SetFar(float zfar) { far_ = zfar; }

	/// @fn GetFov
	/// @brief ��p�擾
	/// @return ��p
	float GetFov() { return fov_; }

	/// @fn GetAspect
	/// @brief ��ʔ䗦�擾
	/// @return ��ʔ䗦
	float GetAspect() { return aspect_; }

	/// @fn GetNear
	/// @brief �߃N���b�v�擾
	/// @return �߃N���b�v
	float GetNear() { return near_; }

	/// @fn GetFar
	/// @brief ���N���b�v�擾
	// @return ���N���b�v
	float GetFar() { return far_; }

	/// @fn D3DXMATRIX
	/// @brief D3DXMATRIX�̃I�y���[�^
	/// @return �p�[�X�s��
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