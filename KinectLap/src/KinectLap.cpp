/// @file KinectLap.cpp
/// @brief Kinect v2 SDKラップクラス
/// @date 2015/10/01
/// @author syuki nishida

#include "KinectLap.h"
#include <crtdbg.h>
#include "BodyReader.h"
#include "ColorReader.h"

template<class t>  void SafeRelease(t *& a) {
  if (a != nullptr) {
    ULONG count = a->Release();
    _ASSERT_EXPR(count, L"開放ミスってる");
    a = nullptr;
  }
}

/// @fn KinectLap
/// @brief コンストラクタ
KinectLap::KinectLap() {
  HRESULT ret;

  ret = GetDefaultKinectSensor(&_sensor);
  _ASSERT_EXPR(SUCCEEDED(ret), L"KinectLap : センサー取得に失敗");

  ret = _sensor->Open();
  _ASSERT_EXPR(SUCCEEDED(ret), L"KinectLap : センサーが開けない");
}

/// @fn ~KinectLap
/// @brief デストラクタ
KinectLap::~KinectLap() {
  HRESULT ret;

  ret = _sensor->Close();
  _ASSERT_EXPR(SUCCEEDED(ret), L"KinectLap : センサーが閉じられません");
  SafeRelease(_sensor);
}

/// @fn CreateColorReader
/// @brief カラーリーダー作成
/// @return カラーリーダーへのポインタ
ColorReader* KinectLap::CreateColorReader() {
  IColorFrameSource* source;
  HRESULT ret;
  ret = _sensor->get_ColorFrameSource(&source);
  _ASSERT_EXPR(SUCCEEDED(ret), L"KinectLap : ColorSourceの取得に失敗");
  ColorReader* instance = new ColorReader(source);
  source->Release();
  return instance;
}

/// @fn CreateBodyReader
/// @brief ボディーリーダー作成
/// @return ボディーリーダーへのポインタ
BodyReader* KinectLap::CreateBodyReader() {
  IBodyFrameSource* source;
  HRESULT ret;
  ret = _sensor->get_BodyFrameSource(&source);
  _ASSERT_EXPR(SUCCEEDED(ret), L"KinectLap : BodySourceの取得に失敗");
  BodyReader* instance = new BodyReader(source);
  source->Release();
  return instance;
}

//EOF