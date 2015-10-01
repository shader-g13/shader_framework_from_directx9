/// @file BodyReader.cpp
/// @brief �{�f�B�[���[�_�[
/// @date 2015/10/01
/// @author syuki nishida

#include "BodyReader.h"
#include <crtdbg.h>

  /// @fn BodyReader
  /// @brief �R���X�g���N�^
BodyReader::BodyReader(IBodyFrameSource* source) {
  HRESULT ret;
  ret = source->OpenReader(&_body_reader);
  _ASSERT_EXPR(SUCCEEDED(ret), L"BodyReader : �\�[�X���J���܂���");
}

  /// @fn ~BodyReader
  /// @brief �f�X�g���N�^
BodyReader::~BodyReader() {
  ULONG count;
  count = _body_reader->Release();
  _ASSERT_EXPR(count, L"BodyReader : �J���ł��܂���");
}

/// @fn Release
/// @breaf �J��
void BodyReader::Release() {
  delete this;
}

//EOF