/// @file D3DXDebugFont.h
/// @brief �f�o�b�O�t�H���g
/// @date 2015/04/18
/// @author syuki nishida

#pragma once
#ifndef SNLIB_D3DX_DEBUG_FONT_H_
#define SNLIB_D3DX_DEBUG_FONT_H_

#include <d3d9.h>
#include <d3dx9.h>
#include <map>
#include <string>
#include <functional>

/// @namespace snlib
namespace snlib {

/// @class D3DXDebugFont
class D3DXDebugFont {
public:
	/// @fn D3DXDebugFont
	/// @brief �f�t�H���g�R���X�g���N�^
	D3DXDebugFont();

	/// @fn Initialize
	/// @brief ������
	/// @return �����Ftrue
	bool Initialize(const LPDIRECT3DDEVICE9 device);

	/// @fn Finalize
	/// @brief �I��
	void Finalize();

	/// @fn Draw
	/// @brief �`��
	void Draw();

	/// @fn SwitchVisible
	/// @brief �\���؂�ւ�
	__forceinline void SwitchVisible() { visible_ ^= true; }

	/// @fn IsVisible
	/// @brief �\���󋵊m�F
	/// @return �\�����Ftrue
	__forceinline bool IsVisible() { return visible_; }

	/// @fn SetCursor
	/// @brief �J�[�\���ړ�
	/// @param[in] x X��
	/// @param[in] y Y��
	void SetCursor(int x, int y);

	/// @fn PrintLine
	/// @brief ������\��
	/// @param[in] format ����
	/// @param[in] ... �����ɑΉ������ϐ�
	void PrintLine(const char* format, ...);

	/// @fn PrintRect
	/// @brief �o�b�t�@����`�ɕ\��
	/// @param[in] buf �\���������o�b�t�@
	/// @param[in] left �\�����������̈ʒu
	/// @param[in] top �\���������c�̈ʒu
	/// @param[in] width �o�b�t�@�̕�
	/// @param[in] height �o�b�t�@�̍���
	void PrintRect(const char* buf, UCHAR left, UCHAR top, UCHAR width, UCHAR height);

	/// @fn Clear
	/// @brief �\�����e�폜
	void Clear();

protected:
private:
	LPD3DXFONT font_;
	bool visible_;

	union CONSOLE_TEXT{
		char dimension1[2048];
		char dimension2[25][80];
	} console_text_;
	UCHAR cursor_x_;
	UCHAR cursor_y_;

	UCHAR font_width_;
	UCHAR font_height_;
	UCHAR buffer_width_;
	UCHAR buffer_height_;
};

} // namespace snlib

#endif // SNLIB_D3DX_DEBUG_FONT_H_

//EOF