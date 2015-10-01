/// @file BodyReader.h
/// @brief ボディーリーダー
/// @date 2015/10/01
/// @author syuki nishida
#pragma once

#include <Kinect.h>

/// @class BodyReader
class BodyReader {
  friend class KinectLap;
public:
protected:
private:
  /// @fn BodyReader
  /// @brief コンストラクタ
  BodyReader(IBodyFrameSource* source);

  /// @fn ~BodyReader
  /// @brief デストラクタ
  virtual ~BodyReader();

  /// @fn Release
  /// @breaf 開放
  void Release();

  IBodyFrameReader* _body_reader;
};

//EOF