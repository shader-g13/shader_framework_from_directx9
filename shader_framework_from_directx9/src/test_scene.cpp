#include "test_scene.h"
#include <DirectX9/Mesh/SoloPlane.h>

using namespace snlib;

/// @brief �R���X�g���N�^
TestScene::TestScene() {
}

/// @brief �f�X�g���N�^
TestScene::~TestScene() {
}

/// @brief ������
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
}

/// @brief �I��
void TestScene::Finalize() {
  delete vs_;
  delete ps_;

  model_->Finalize();
  delete model_;
}

/// @brief �X�V
void TestScene::Update() {
}

/// @brief �`��
void TestScene::Draw(LPDIRECT3DDEVICE9 device) {
  D3DXMATRIX world;
  D3DXMatrixScaling(&world, 1, 1, 1);
  device->SetTransform(D3DTS_PROJECTION, &perth_.CreatePerth());
  device->SetTransform(D3DTS_VIEW, &view_.CreateView());
  device->SetTransform(D3DTS_WORLD, &world);

  LPD3DXCONSTANTTABLE vs_const = vs_->GetConstantTable();
  vs_const->SetMatrix(device, "ProjectionMatrix", &perth_.CreatePerth());
  vs_const->SetMatrix(device, "ViewMatrix", &view_.CreateView());
  vs_const->SetMatrix(device, "WorldMatrix", &world);

  vs_->SetVertexShader(device);
  ps_->SetPixelShader(device);

  SoloPlane::Draw(device);

  model_->Draw(device);
}

// EOF