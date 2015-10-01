/// @file KinectLap.cpp
/// @brief Kinect v2 SDK���b�v�N���X
/// @date 2015/10/01
/// @author syuki nishida

#include "KinectLap.h"
#include <crtdbg.h>
#include "BodyReader.h"
#include "ColorReader.h"

template<class t>  void SafeRelease(t *& a) {
  if (a != nullptr) {
    ULONG count = a->Release();
    _ASSERT_EXPR(count, L"�J���~�X���Ă�");
    a = nullptr;
  }
}

/// @fn KinectLap
/// @brief �R���X�g���N�^
KinectLap::KinectLap() {
  HRESULT ret;

  ret = GetDefaultKinectSensor(&_sensor);
  _ASSERT_EXPR(SUCCEEDED(ret), L"KinectLap : �Z���T�[�擾�Ɏ��s");

  ret = _sensor->Open();
  _ASSERT_EXPR(SUCCEEDED(ret), L"KinectLap : �Z���T�[���J���Ȃ�");
}

/// @fn ~KinectLap
/// @brief �f�X�g���N�^
KinectLap::~KinectLap() {
  HRESULT ret;

  ret = _sensor->Close();
  _ASSERT_EXPR(SUCCEEDED(ret), L"KinectLap : �Z���T�[�������܂���");
  SafeRelease(_sensor);
}

/// @fn CreateColorReader
/// @brief �J���[���[�_�[�쐬
/// @return �J���[���[�_�[�ւ̃|�C���^
ColorReader* KinectLap::CreateColorReader() {
  IColorFrameSource* source;
  HRESULT ret;
  ret = _sensor->get_ColorFrameSource(&source);
  _ASSERT_EXPR(SUCCEEDED(ret), L"KinectLap : ColorSource�̎擾�Ɏ��s");
  ColorReader* instance = new ColorReader(source);
  source->Release();
  return instance;
}

/// @fn CreateBodyReader
/// @brief �{�f�B�[���[�_�[�쐬
/// @return �{�f�B�[���[�_�[�ւ̃|�C���^
BodyReader* KinectLap::CreateBodyReader() {
  IBodyFrameSource* source;
  HRESULT ret;
  ret = _sensor->get_BodyFrameSource(&source);
  _ASSERT_EXPR(SUCCEEDED(ret), L"KinectLap : BodySource�̎擾�Ɏ��s");
  BodyReader* instance = new BodyReader(source);
  source->Release();
  return instance;
}

//EOF