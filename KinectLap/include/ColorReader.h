/// @file ColorReader.h
/// @brief �J���[�[���[�_�[
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
  /// @brief �R���X�g���N�^
  ColorReader(IColorFrameSource* source);

  /// @fn ~ColorReader
  /// @brief �f�X�g���N�^
  virtual ~ColorReader();

  /// @fn Release
  /// @breaf �J��
  void Release();

  IColorFrameReader* _color_reader;
};

//EOF