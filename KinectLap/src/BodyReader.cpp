/// @file BodyReader.cpp
/// @brief ボディーリーダー
/// @date 2015/10/01
/// @author syuki nishida

#include "BodyReader.h"
#include <crtdbg.h>

  /// @fn BodyReader
  /// @brief コンストラクタ
BodyReader::BodyReader(IBodyFrameSource* source) {
  HRESULT ret;
  ret = source->OpenReader(&_body_reader);
  _ASSERT_EXPR(SUCCEEDED(ret), L"BodyReader : ソースが開けません");
}

  /// @fn ~BodyReader
  /// @brief デストラクタ
BodyReader::~BodyReader() {
  ULONG count;
  count = _body_reader->Release();
  _ASSERT_EXPR(count, L"BodyReader : 開放できません");
}

/// @fn Release
/// @breaf 開放
void BodyReader::Release() {
  delete this;
}

//EOF