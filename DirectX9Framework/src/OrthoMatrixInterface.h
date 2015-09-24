/// @file OrthoMatrixInterface.h
/// @brief �I���\�[�s��C���^�[�t�F�[�X
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
/// @brief �I���\�[�s��C���^�[�t�F�[�X
class OrthoMatrixInterface {
public:
	///@fn OrthoMatixInterface
	/// @brief �R���X�g���N�^
	OrthoMatrixInterface() {
		D3DXMatrixIdentity(&ortho_);
	}

	/// @fn ~OrthoMatrixInterface
	/// @brief �f�X�g���N�^
	virtual ~OrthoMatrixInterface() {}

	/// @fn CreateOrtho
	/// @brief �I���\�[�s��쐬
	/// @return �I���\�[�s��
	const D3DXMATRIX CreateOrtho() {
		D3DXMatrixOrthoLH(&ortho_, width_, height_, near_, far_);
		return ortho_;
	}

	/// @fn SetWidth
	/// @brief ���ݒ�
	/// @param[in] width �ݒ肵������
	void SetWidth(float width) { width_ = width; }

	/// @fn SetHeight
	/// @brief ���ݒ�
	/// @param[in] height �ݒ肵��������
	void SetHeight(float height) { height_ = height; }

	/// @fn SetNear
	/// @brief �߃N���b�v�ݒ�
	/// @param[in] znear �ݒ肵�����߃N���b�v
	void SetNear(float znear) { near_ = znear; }

	/// @fn SetFar
	/// @brief ���N���b�v�ݒ�
	/// @param[in] zfar �ݒ肵�������N���b�v
	void SetFar(float zfar) { far_ = zfar; }

	/// @fn GetWidth
	/// @brief ���擾
	/// @return ��
	float GetWidth() { return width_; }

	/// @fn GetHeight
	/// @brief �����擾
	/// @return ����
	float GetHeight() { return height_; }

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
	/// @return �I���\�[�s��
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