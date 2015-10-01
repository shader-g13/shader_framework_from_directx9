/// @file KinectLap.h
/// @brief Kinect v2 SDKラップクラス
/// @date 2015/10/01
/// @author syuki nishida
#pragma once

#include <Kinect.h>
class ColorReader;
class BodyReader;

class KinectLap {
public:
  /// @fn KinectLap
  /// @brief コンストラクタ
  KinectLap();

  /// @fn ~KinectLap
  /// @brief デストラクタ
  virtual ~KinectLap();

  /// @fn CreateColorReader
  /// @brief カラーリーダー作成
  /// @return カラーリーダーへのポインタ
  ColorReader* CreateColorReader();

  /// @fn CreateBodyReader
  /// @brief ボディーリーダー作成
  /// @return ボディーリーダーへのポインタ
  BodyReader* CreateBodyReader();

protected:
private:
  // sensor
  IKinectSensor* _sensor;
};

//EOF