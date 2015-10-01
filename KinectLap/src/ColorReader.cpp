/// @file ColorReader.cpp
/// @brief ボディーリーダー
/// @date 2015/10/01
/// @author syuki nishida

#include "ColorReader.h"
#include <crtdbg.h>

/// @fn ColorReader
/// @brief コンストラクタ
ColorReader::ColorReader(IColorFrameSource* source) {
  HRESULT ret;
  ret = source->OpenReader(&_color_reader);
  _ASSERT_EXPR(SUCCEEDED(ret), L"ColorReader : ソースが開けません");
}

/// @fn ~ColorReader
/// @brief デストラクタ
ColorReader::~ColorReader() {
  ULONG count;
  count = _color_reader->Release();
  _ASSERT_EXPR(count, L"ColorReader : 開放できません");
}

/// @fn Release
/// @breaf 開放
void ColorReader::Release() {
  delete this;
}

//EOF