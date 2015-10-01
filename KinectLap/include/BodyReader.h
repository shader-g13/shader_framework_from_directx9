/// @file BodyReader.h
/// @brief �{�f�B�[���[�_�[
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
  /// @brief �R���X�g���N�^
  BodyReader(IBodyFrameSource* source);

  /// @fn ~BodyReader
  /// @brief �f�X�g���N�^
  virtual ~BodyReader();

  /// @fn Release
  /// @breaf �J��
  void Release();

  IBodyFrameReader* _body_reader;
};

//EOF