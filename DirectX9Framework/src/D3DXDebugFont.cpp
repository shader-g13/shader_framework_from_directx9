/// @file D3DXDebugFont.h
/// @brief �f�o�b�O�t�H���g
/// @date 2015/04/18
/// @author syuki nishida

#include "D3DXDebugFont.h"
#include <crtdbg.h>

#pragma comment(lib, "d3dx9.lib")

/// @namespace snlib
namespace snlib {

/// @fn D3DXDebugFont
/// @brief �f�t�H���g�R���X�g���N�^
D3DXDebugFont::D3DXDebugFont()
 : font_(nullptr), visible_(false) {
}

/// @fn Initialize
/// @brief ������
/// @param[in] device �f�o�C�X
/// @return �����Ftrue
bool D3DXDebugFont::Initialize(const LPDIRECT3DDEVICE9 device) {
	if (font_) return false;

	font_width_ = 8;
	font_height_ = 18;
	buffer_width_ = 80;
	buffer_height_ = 25;

	cursor_x_ = 0;
	cursor_y_ = 0;

	ZeroMemory(&console_text_, sizeof(console_text_));

	HRESULT result;
	result = D3DXCreateFontA(
		device, font_height_, font_width_, 0, 0, false,
		SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"Terminal", &font_);
	_ASSERT_EXPR(SUCCEEDED(result), L"snlib D3DXDebugFont error "
		L"create font to failed");

	if (FAILED(result)) {
		return false;
	}

	return true;
}

/// @fn Finalize
/// @brief �I��
void D3DXDebugFont::Finalize() {
	if (!font_) return;

	font_->Release();
	font_ = nullptr;
}

/// @fn Draw
/// @brief �`��
void D3DXDebugFont::Draw() {
	if (!visible_) return;

	RECT rect = { 1, 1,
		font_width_ * buffer_width_ + 1, font_height_ + 1 };
	for (auto i = 0; i < buffer_height_; i++) {
		font_->DrawTextA(nullptr, &console_text_.dimension2[i][0], buffer_width_,
			&rect, DT_NOCLIP | DT_SINGLELINE, D3DCOLOR_ARGB(0xff, 0x00, 0x00, 0x00));
		rect.top--; rect.left--; rect.bottom--; rect.right--;
		font_->DrawTextA(nullptr, &console_text_.dimension2[i][0], buffer_width_,
			&rect, DT_NOCLIP | DT_SINGLELINE, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
		rect.top++; rect.left++; rect.bottom++; rect.right++;
		rect.top += font_height_;
		rect.bottom += font_height_;
	}
}

/// @fn SetCursor
/// @brief �J�[�\���ړ�
/// @param[in] x X��
/// @param[in] y Y��
void D3DXDebugFont::SetCursor(int x, int y) {
	// �u-�v�͂��Ԃ񖳕ύX�̈Ӗ�
	if (cursor_x_ >= 0) {
		cursor_x_ = static_cast<UCHAR>(cursor_x_);
		cursor_y_ += cursor_x_ / buffer_width_;
		cursor_x_ = cursor_x_ % buffer_width_;
	}

	// �u-�v�͂��Ԃ񖳕ύX�̈Ӗ�
	if (cursor_y_ >= 0) {
		cursor_y_ = static_cast<UCHAR>(cursor_y_);
	}
	cursor_y_ = cursor_y_ > buffer_height_ ?
	buffer_height_ : cursor_y_;
}

/// @fn PrintLine
/// @brief ������\��
/// @param[in] format ����
/// @param[in] ... �����ɑΉ������ϐ�
void D3DXDebugFont::PrintLine(const char* format, ...) {
	va_list arg;
	int arg_len;
	char buf[1024];

	va_start(arg, format);
	arg_len = vsprintf_s(buf, format, arg);
	va_end(arg);

	if (cursor_x_ < buffer_width_
		&&  cursor_y_ < buffer_height_) {
		for (auto i = 0; i < arg_len; i++) {
			if (buf[i] == '\n') {
				cursor_x_ = 0;
				cursor_y_++;
				continue;
			}
			console_text_.dimension2[cursor_y_][cursor_x_] = buf[i];
			cursor_x_++;
			cursor_y_ += cursor_x_ / buffer_width_;
			cursor_x_ = cursor_x_ % buffer_width_;
		}
	}
}

/// @fn PrintRect
/// @brief �o�b�t�@����`�ɕ\��
/// @param[in] buf �\���������o�b�t�@
/// @param[in] left �\�����������̈ʒu
/// @param[in] top �\���������c�̈ʒu
/// @param[in] width �o�b�t�@�̕�
/// @param[in] height �o�b�t�@�̍���
void D3DXDebugFont::PrintRect(const char* buf,
	UCHAR left, UCHAR top, UCHAR width, UCHAR height) {
	for (auto i = 0; i < height; i++) {
		SetCursor(left, top + i);
		memcpy_s(&console_text_.dimension2[cursor_y_][cursor_x_],
			sizeof(console_text_), &buf[i * width], width);
	}
}

/// @fn Clear
/// @brief �\�����e�폜
void D3DXDebugFont::Clear() {
	ZeroMemory(&console_text_, sizeof(console_text_));
	SetCursor(0, 0);
}

} // namespace snlib

//EOF