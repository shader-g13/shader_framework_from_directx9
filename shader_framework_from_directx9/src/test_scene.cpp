#include "test_scene.h"
#include <DirectX9/Mesh/SoloPlane.h>
#include <Kinect.h>

using namespace snlib;

IKinectSensor* sensor;
IColorFrameSource* color_source;
IColorFrameReader* color_reader;
IFrameDescription* description;
IColorFrame* color_frame;
unsigned char* buffer;
LPDIRECT3DTEXTURE9 tex;
unsigned int buffer_size;

/// @brief コンストラクタ
TestScene::TestScene() {
}

/// @brief デストラクタ
TestScene::~TestScene() {
}

/// @brief 初期化
void TestScene::Initialize(LPDIRECT3DDEVICE9 device) {
  model_ = new XModel();
  model_->Initialize(device, "res/kuma.x");

  vs_ = new VertexShader(device, "res/shader/test_vs.cso");
  ps_ = new PixelShader(device, "res/shader/test_ps.cso");

  perth_.SetFov(D3DXToRadian(45.f));
  perth_.SetAspect(4.f / 3.f);
  perth_.SetNear(0.1f);
  perth_.SetFar(1000.f);

  view_.SetEye(D3DXVECTOR3(0, 100, -100));
  view_.SetAt(D3DXVECTOR3(0, 0, 0));
  view_.SetUp(D3DXVECTOR3(0, 1, 0));
  HRESULT ret;

  ret = GetDefaultKinectSensor(&sensor);
  _ASSERT_EXPR(SUCCEEDED(ret), L"ERROR");
  sensor->Open();
  ret = sensor->get_ColorFrameSource(&color_source);
  _ASSERT_EXPR(SUCCEEDED(ret), L"ERROR");
  ret = color_source->OpenReader(&color_reader);
  _ASSERT_EXPR(SUCCEEDED(ret), L"ERROR");
  ret = color_source->get_FrameDescription(&description);
  _ASSERT_EXPR(SUCCEEDED(ret), L"ERROR");

  int width;
  int height;
  description->get_Width(&width);
  description->get_Height(&height);

  buffer_size = width * height * 4;
  buffer = new unsigned char[buffer_size];

  device->CreateTexture(width, height, 1, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &tex, nullptr);
  D3DLOCKED_RECT rect;
  tex->LockRect(0, &rect, nullptr, 0);
  memcpy_s(rect.pBits, buffer_size, buffer, buffer_size);
  tex->UnlockRect(0);

}

/// @brief 終了
void TestScene::Finalize() {
  delete vs_;
  delete ps_;

  model_->Finalize();
  delete model_;
}

/// @brief 更新
void TestScene::Update() {
  HRESULT tret = color_reader->AcquireLatestFrame(&color_frame);
  if (color_frame) {
    color_frame->CopyConvertedFrameDataToArray(
      buffer_size,
      buffer,
      ColorImageFormat::ColorImageFormat_Bgra);
  }
  D3DLOCKED_RECT rect;
  tex->LockRect(0, &rect, nullptr, 0);
  memcpy_s(rect.pBits, buffer_size, buffer, buffer_size);
  tex->UnlockRect(0);
  if (color_frame)
  color_frame->Release();
}

/// @brief 描画
void TestScene::Draw(LPDIRECT3DDEVICE9 device) {
  D3DXMATRIX world;
  D3DXMatrixScaling(&world, 100, 100, 100);

  LPD3DXCONSTANTTABLE vs_const = vs_->GetConstantTable();
  vs_const->SetMatrix(device, "ProjectionMatrix", &perth_.CreatePerth());
  vs_const->SetMatrix(device, "ViewMatrix", &view_.CreateView());
  vs_const->SetMatrix(device, "WorldMatrix", &world);

  vs_->SetVertexShader(device);
  ps_->SetPixelShader(device);

  device->SetTexture(0, tex);

  SoloPlane::Draw(device);
}

// EOF