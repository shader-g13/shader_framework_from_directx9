/// @file ColorReader.cpp
/// @brief �{�f�B�[���[�_�[
/// @date 2015/10/01
/// @author syuki nishida

#include "ColorReader.h"
#include <crtdbg.h>

/// @fn ColorReader
/// @brief �R���X�g���N�^
ColorReader::ColorReader(IColorFrameSource* source) {
  HRESULT ret;
  ret = source->OpenReader(&_color_reader);
  _ASSERT_EXPR(SUCCEEDED(ret), L"ColorReader : �\�[�X���J���܂���");
}

/// @fn ~ColorReader
/// @brief �f�X�g���N�^
ColorReader::~ColorReader() {
  ULONG count;
  count = _color_reader->Release();
  _ASSERT_EXPR(count, L"ColorReader : �J���ł��܂���");
}

/// @fn Release
/// @breaf �J��
void ColorReader::Release() {
  delete this;
}

//EOF