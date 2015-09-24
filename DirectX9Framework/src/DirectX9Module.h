/// @file DirectX9Module.h
/// @brief DirectX9���W���[��
/// @data 2015/04/16
/// @author syuki nishida

#pragma once
#ifndef SNLIB_DIRECTX9_MODULE_H_
#define SNLIB_DIRECTX9_MODULE_H_

#include <d3d9.h>

/// @namespace snlib
namespace snlib {

/// @class DirectX9Module
class DirectX9Module {
public:
	/// @fn DirectX9Module
	/// @brief �f�t�H���g�R���X�g���N�^
	/// @param[in] window_handle �E�B���h�E�n���h��
	/// @param[in] windable �E�B���h�E���[�h��
	DirectX9Module(HWND window_handle, bool windable = true);

	/// @fn Initialize
	/// @brief ������
	/// @return �����Ftrue
	bool Initialize();

	/// @fn Finalize
	/// @brief �I��
	void Finalize();

	/// @fn BeginScene
	/// @brief �`��J�n
	/// @return �`��J�n�Ftrue
	bool BeginScene();

	/// @fn EndScene
	/// @brief �`��I��
	void EndScene();

	/// @fn SwitchWindowMode
	/// @brief �E�B���h�E���[�h�؂�ւ�
	void SwitchWindowMode();

	/// @fn GetDevice
	/// @brief �f�o�C�X�擾
	/// @return �f�o�C�X
	__forceinline const LPDIRECT3DDEVICE9 GetDevice() {
		return device_;
	}

	/// @fn GetBufferWidth
	/// @brief �o�b�t�@���擾
	/// @return �o�b�t�@��
	__forceinline UINT GetBufferWidth() {
		return present_params_.BackBufferWidth;
	}

	/// @fn GetBufferHeight
	/// @brief �o�b�t�@�����擾
	/// @return �o�b�t�@����
	__forceinline UINT GetBufferHeight() {
		return present_params_.BackBufferHeight;
	}

private:
	HWND window_handle_;
	bool windable_;
	D3DPRESENT_PARAMETERS present_params_;

	LPDIRECT3D9       direct3d9_;
	D3DDISPLAYMODE    display_mode_;
	LPDIRECT3DDEVICE9 device_;

protected:
};

} // namespace snlib

#endif // SNLIB_DIRECTX9_MODULE_H_

//EOF