/// @file KinectLap.h
/// @brief Kinect v2 SDK���b�v�N���X
/// @date 2015/10/01
/// @author syuki nishida
#pragma once

#include <Kinect.h>
class ColorReader;
class BodyReader;

class KinectLap {
public:
  /// @fn KinectLap
  /// @brief �R���X�g���N�^
  KinectLap();

  /// @fn ~KinectLap
  /// @brief �f�X�g���N�^
  virtual ~KinectLap();

  /// @fn CreateColorReader
  /// @brief �J���[���[�_�[�쐬
  /// @return �J���[���[�_�[�ւ̃|�C���^
  ColorReader* CreateColorReader();

  /// @fn CreateBodyReader
  /// @brief �{�f�B�[���[�_�[�쐬
  /// @return �{�f�B�[���[�_�[�ւ̃|�C���^
  BodyReader* CreateBodyReader();

protected:
private:
  // sensor
  IKinectSensor* _sensor;
};

//EOF