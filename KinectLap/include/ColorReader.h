/// @file ColorReader.h
/// @brief カラーーリーダー
/// @date 2015/10/01
/// @author syuki nishida
#pragma once

#include <Kinect.h>

/// @class ColorReader
class ColorReader {
  friend class KinectLap;
public:
protected:
private:
  /// @fn ColorReader
  /// @brief コンストラクタ
  ColorReader(IColorFrameSource* source);

  /// @fn ~ColorReader
  /// @brief デストラクタ
  virtual ~ColorReader();

  /// @fn Release
  /// @breaf 開放
  void Release();

  IColorFrameReader* _color_reader;
};

//EOF