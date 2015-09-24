#pragma once

#include <d3d9.h>

class Renderer {
public:
	/// @brief �R���X�g���N�^
	Renderer();

	/// @brief �f�X�g���N�^
	virtual ~Renderer();

	/// @brief ������
	void Initialize(HWND window_handle, UINT buffer_width, UINT buffer_heignt, bool windable = true);

	/// @biref �I��
	void Finalize();

	/// @brief �`��J�n
	void BegenDraw();

	/// @brief �`��I��
	void EndDraw();

	/// @brief �f�o�C�X�擾
	LPDIRECT3DDEVICE9 GetDevice() { return device_; }

protected:
private:
	LPDIRECT3D9 direct3d_;
	LPDIRECT3DDEVICE9 device_;

	bool windable_;
	UINT buffer_width_;
	UINT buffer_height_;
	HWND window_handle_;
};