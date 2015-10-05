#include "test_scene.h"
#include "input.h"
/// @brief コンストラクタ
TestScene::TestScene():
rot_(0,0,0)
{
}

/// @brief デストラクタ
TestScene::~TestScene() {
}

/// @brief 初期化
void TestScene::Initialize(LPDIRECT3DDEVICE9 device) {
  plane_ = new Plane();
  plane_->Initialize(device);

  model_ = new XModel();
  model_->Initialize(device, "res/box.x");

  vs_ = new VertexShader(device, "res/shader/specular_vs.cso");
  ps_ = new PixelShader(device, "res/shader/bump_ps.cso");

   D3DXCreateTextureFromFile(device,"res/Base.bmp",&texBase_);
   D3DXCreateTextureFromFile(device,"res/Metal_Normal.bmp",&texBmp_);
}

/// @brief 終了
void TestScene::Finalize() {
  delete vs_;
  delete ps_;

  model_->Finalize();
  delete model_;

  plane_->Finalize();
  delete plane_;

  texBase_->Release();
  texBmp_->Release();

}

/// @brief 更新
void TestScene::Update() {
 rot_.x += 0.01f;
 rot_.y += 0.01f;
 rot_.z += 0.01f;
}

/// @brief 描画
void TestScene::Draw(LPDIRECT3DDEVICE9 device) {
  D3DXMATRIX world,rot;
  D3DXMatrixScaling(&world, 80, 80, 80);
  device->SetTransform(D3DTS_PROJECTION, &perth_.CreatePerthMatrix());
  device->SetTransform(D3DTS_VIEW, &view_.CreateViewMatrix());
  D3DXMatrixRotationYawPitchRoll(&rot,rot_.y,rot_.x,rot_.z);
  D3DXMatrixMultiply(&world,&world,&rot);
  device->SetTransform(D3DTS_WORLD,&world);
  float specPower[] = 
  {
   3,2,1
  };

  D3DXVECTOR3 specColor[]=
  {
   D3DXVECTOR3(0.9f,0.6f,0.9f),
   D3DXVECTOR3(0.9f,0.9f,0.5f),
   D3DXVECTOR3(0.8f,0.9f,0.9f),
  };
  D3DXVECTOR3 lightVec[] =
  {
   D3DXVECTOR3(1,0,-1),
   D3DXVECTOR3(0,1,0),
   D3DXVECTOR3(0,-1,1),
  };
  D3DXVECTOR3 lightPos[] =
  {
   D3DXVECTOR3(10,0,1),
   D3DXVECTOR3(1,10,-10),
   D3DXVECTOR3(0,1,10),
  };

  LPD3DXCONSTANTTABLE vs_const = vs_->GetConstantTable();
  vs_const->SetMatrix(device, "ProjectionMatrix", &perth_.CreatePerthMatrix());
  vs_const->SetMatrix(device, "ViewMatrix", &view_.CreateViewMatrix());
  vs_const->SetMatrix(device, "WorldMatrix", &world);
  vs_const->SetVector(device,"MaterialDiffuse",&D3DXVECTOR4(1,1,1,1));
  LPD3DXCONSTANTTABLE ps_const = ps_->GetConstantTable();
  ps_const->SetFloatArray(device,"lightVec",(float*)lightVec,9);
  ps_const->SetFloatArray(device,"lightPos",(float*)lightPos,9);
  ps_const->SetFloatArray(device,"specPower",specPower,3);
  ps_const->SetFloatArray(device,"specCol",(float*)specColor,9);
  
  vs_->SetVertexShader(device);
  ps_->SetPixelShader(device);
  device->SetTexture(0,texBase_);
  device->SetTexture(1,texBmp_);

  plane_->Draw(device);

  model_->Draw(device);
}

// EOF