#include "test_scene.h"

/// @brief コンストラクタ
TestScene::TestScene() {
}

/// @brief デストラクタ
TestScene::~TestScene() {
}

/// @brief 初期化
void TestScene::Initialize(LPDIRECT3DDEVICE9 device) {
  plane_ = new Plane();
  plane_->Initialize(device);

  model_ = new XModel();
  model_->Initialize(device, "res/kuma.x");

  vs_ = new VertexShader(device, "res/shader/test_vs.cso");
  ps_ = new PixelShader(device, "res/shader/test_ps.cso");
}

/// @brief 終了
void TestScene::Finalize() {
  delete vs_;
  delete ps_;

  model_->Finalize();
  delete model_;

  plane_->Finalize();
  delete plane_;

}

/// @brief 更新
void TestScene::Update() {
}

/// @brief 描画
void TestScene::Draw(LPDIRECT3DDEVICE9 device) {
  D3DXMATRIX world;
  D3DXMatrixScaling(&world, 1, 1, 1);
  device->SetTransform(D3DTS_PROJECTION, &perth_.CreatePerthMatrix());
  device->SetTransform(D3DTS_VIEW, &view_.CreateViewMatrix());
  device->SetTransform(D3DTS_WORLD, &world);

  LPD3DXCONSTANTTABLE vs_const = vs_->GetConstantTable();
  vs_const->SetMatrix(device, "ProjectionMatrix", &perth_.CreatePerthMatrix());
  vs_const->SetMatrix(device, "ViewMatrix", &view_.CreateViewMatrix());
  vs_const->SetMatrix(device, "WorldMatrix", &world);

  vs_->SetVertexShader(device);
  ps_->SetPixelShader(device);

  plane_->Draw(device);

  model_->Draw(device);
}

// EOF