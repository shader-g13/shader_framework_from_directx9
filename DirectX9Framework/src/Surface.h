/// @file Surface.h
/// @brief �T�[�t�F�[�X
/// @date 2015/05/21
/// @author syuki nishida

#pragma once
#ifndef SNLIB_SURFACE_H_
#define SNLIB_SURFACE_H_

#include <d3dx9.h>

/// @namespace snlib
namespace snlib {

/// @class Surface
class Surface {
public:
	/// @fn Surface
	/// @brief �f�t�H���g�R���X�g���N�^
	/// @param[in] device �f�o�C�X
	/// @param[in] width ��
	/// @param[in] height ����
	/// @param[in] texture_count �e�N�X�`������
	Surface(LPDIRECT3DDEVICE9 device, UINT width, UINT height, UINT texture_count);

	/// @fn ~Surface
	/// @brief �f�t�H���g�f�X�g���N�^
	virtual ~Surface();

	/// @fn SetSurface
	/// @brief �T�[�t�F�[�X�ݒ�
	__forceinline void SetSurface(LPDIRECT3DDEVICE9 device) {
		for (UINT i = 0; i < texture_count_; i++) {
			device->SetRenderTarget(i, color_surface_[i]);
		}
		device->SetDepthStencilSurface(depth_surface_);
	}

	/// @fn BeginSurface
	/// @brief �T�[�t�F�[�X�ւ̕`��J�n
	__forceinline void BeginSurface(LPDIRECT3DDEVICE9 device) {
		SetSurface(device);
		device->Clear(0, nullptr, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL),
			clear_color_, 1.0f, 0);
	}

	/// @fn GetTexture
	/// @brief �e�N�X�`���擾
	/// @param[in] index �~�����e�N�X�`��
	/// @return �e�N�X�`���ւ̃A�h���X
	__forceinline LPDIRECT3DTEXTURE9 GetTexture(UINT index) {
		return texture_[index];
	}

	/// @fn SetClearColor
	/// @brief �N���A�J���[�ݒ�
	/// @param[in] color �w�肵�����F
	__forceinline void SetClearColor(D3DCOLOR color) {
		clear_color_ = color;
	}

	/// @fn SaveCurrentSurface
	/// @brief ���̃T�[�t�F�[�X��ۑ�(��܂�)
	static void SaveCurrentSurface(LPDIRECT3DDEVICE9 device) {
		device->GetRenderTarget(0, &default_color_surface_);
		device->GetDepthStencilSurface(&default_depth_surface_);
	}

	/// @fn SetSaveSurface
	/// @brief �ۑ������T�[�t�F�[�X��ݒ�
	static void SetSaveSurface(LPDIRECT3DDEVICE9 device) {
		device->SetRenderTarget(0, default_color_surface_);
		device->SetDepthStencilSurface(default_depth_surface_);
	}

	/// @fn DeleteSaveSurface
	/// @brief �ۑ������T�[�t�F�[�X����
	static void DeleteSaveSurface() {
		default_color_surface_->Release();
		default_depth_surface_->Release();
	}

protected:
private:
	static LPDIRECT3DSURFACE9 default_color_surface_;
	static LPDIRECT3DSURFACE9 default_depth_surface_;

	D3DCOLOR clear_color_;

	LPDIRECT3DTEXTURE9* texture_;
	LPDIRECT3DSURFACE9* color_surface_;
	LPDIRECT3DSURFACE9 depth_surface_;

	UINT width_;
	UINT height_;
	UINT texture_count_;
};

} // namespace snlib

#endif // SNLIB_SURFACE_H_

//EOF