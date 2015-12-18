#include "test_scene.h"
#include "input.h"
namespace{
 static const float kRotSpeed = 0.03f;
}
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
  model_->Initialize(device, "data/model/box.x");

  skyBox_ = new XModel();
  skyBox_->Initialize(device,"data/model/lobby_skybox.x");

  vs_ = new VertexShader(device,"data/shader/specularLight.cso");
  ps_ = new PixelShader(device,"data/shader/normalBump.cso");
  ps_texture = new PixelShader(device,"data/shader/texture.cso");

   D3DXCreateTextureFromFile(device,"data/texture/Base.bmp",&texBase_);
   D3DXCreateTextureFromFile(device,"data/texture/Metal_Normal.bmp",&texBmp_);
   D3DXCreateCubeTextureFromFile(device,"data/texture/LobbyCube.dds",&texCube_);
   _surface = new snlib::Surface(device,800,600,4);
   _surface->SaveCurrentSurface(device);
   _surface->BeginSurface(device);
   _surface->SetSaveSurface(device);
}

/// @brief 終了
void TestScene::Finalize() {
  delete vs_;
  delete ps_;
  delete ps_texture;
  skyBox_->Finalize();
  delete skyBox_;
  model_->Finalize();
  delete model_;

  plane_->Finalize();
  delete plane_;

  texBase_->Release();
  texBmp_->Release();
  texCube_->Release();

  if(_surface)
  {
   _surface->DeleteSaveSurface();
   delete _surface;
  }
}

/// @brief 更新
void TestScene::Update() {
 if(GetKeyPress(DIK_W))
 {
  rot_.x += kRotSpeed;
 }
 if(GetKeyPress(DIK_S))
 {
  rot_.x -= kRotSpeed;
 }
 if(GetKeyPress(DIK_A))
 {
  rot_.y += kRotSpeed;
 }
 if(GetKeyPress(DIK_D))
 {
  rot_.y -= kRotSpeed;
 }
 if(GetKeyPress(DIK_Q))
 {
  rot_.z += kRotSpeed;
 }
 if(GetKeyPress(DIK_E))
 {
  rot_.z -= kRotSpeed;
 }
}

/// @brief 描画
void TestScene::Draw(LPDIRECT3DDEVICE9 device) {
 _surface->BeginSurface(device);
 D3DXMATRIX world,rot;
  D3DXMatrixScaling(&world, 70, 70, 70);
  device->SetTransform(D3DTS_PROJECTION, &perth_.CreatePerthMatrix());
  device->SetTransform(D3DTS_VIEW, &view_.CreateViewMatrix());
  D3DXMatrixRotationYawPitchRoll(&rot,rot_.y,rot_.x,rot_.z);
  D3DXMatrixMultiply(&world,&world,&rot);
  device->SetTransform(D3DTS_WORLD,&world);

  float specPower[] = 
  {
   5,5,5,3
  };

  D3DXVECTOR3 specColor[]=
  {
   D3DXVECTOR3(0.6f,0.3f,0.8f),
   D3DXVECTOR3(0.6f,0.9f,0.2f),
   D3DXVECTOR3(0.4f,0.6f,0.6f),
   D3DXVECTOR3(0.1f,0.2f,0.6f),
  };
  D3DXVECTOR3 lightVec[] =
  {
   D3DXVECTOR3(1,0,-1),
   D3DXVECTOR3(-1,1,0),
   D3DXVECTOR3(0,-1,1),
   D3DXVECTOR3(1,0,-1),
  };
  D3DXVECTOR3 lightPos[] =
  {
   D3DXVECTOR3(20,0,1),
   D3DXVECTOR3(-20,0,0),
   D3DXVECTOR3(0,-21,0),
   D3DXVECTOR3(40,10,1),
  };
  D3DXMATRIX WIT;
  D3DXMatrixInverse(&WIT,0,&world);
  D3DXMatrixTranspose(&WIT,&WIT);
  LPD3DXCONSTANTTABLE vs_const = vs_->GetConstantTable();
  vs_const->SetMatrix(device, "ProjectionMatrix", &perth_.CreatePerthMatrix());
  vs_const->SetMatrix(device, "ViewMatrix", &view_.CreateViewMatrix());
  vs_const->SetMatrix(device, "WorldMatrix", &world);
  vs_const->SetVector(device,"MaterialDiffuse",&D3DXVECTOR4(1,1,1,1));
  vs_const->SetMatrix(device,"WIT",&WIT);
  LPD3DXCONSTANTTABLE ps_const = ps_->GetConstantTable();
  ps_const->SetFloatArray(device,"lightVec",(float*)lightVec,12);
  ps_const->SetFloatArray(device,"lightPos",(float*)lightPos,12);
  ps_const->SetFloatArray(device,"specPower",specPower,4);
  ps_const->SetFloatArray(device,"specCol",(float*)specColor,12);
  ps_const->SetBool(device,"skybox",false);

  vs_->SetVertexShader(device);
  ps_->SetPixelShader(device);
  device->SetTexture(0,texBase_);
  device->SetTexture(1,texBmp_);
  device->SetTexture(ps_const->GetSamplerIndex("textureC"),texCube_);

  model_->Draw(device);
  D3DXMatrixIdentity(&world);
  device->SetTransform(D3DTS_WORLD,&world);
  vs_const->SetMatrix(device,"ProjectionMatrix",&perth_.CreatePerthMatrix());
  vs_const->SetMatrix(device,"ViewMatrix",&view_.CreateViewMatrix());
  skyBox_->Draw(device);
  _surface->SetSaveSurface(device);
  ps_const->SetBool(device,"skybox",true);

  D3DXMATRIX trans,scl;
  D3DXVECTOR2 dsize = D3DXVECTOR2(800 / 4,600 / 4);
  D3DXMATRIX proj;
  D3DXMatrixOrthoLH(&proj,800,600,8,15);
  device->SetTransform(D3DTS_PROJECTION,&proj);

  D3DXMatrixIdentity(&world);
  D3DXMatrixTranslation(&trans,dsize.x,dsize.y,0);
  D3DXMatrixMultiply(&world,&world,&trans);
  D3DXMatrixScaling(&scl,dsize.x,dsize.y,1);
  D3DXMatrixMultiply(&world,&world,&scl);
  device->SetTransform(D3DTS_WORLD,&world);
  _surface->SetSaveSurface(device);

  D3DXMATRIX identity,view;
  D3DXMatrixIdentity(&identity);
  D3DXMatrixScaling(&world,2.f,2.f,1);
  D3DXMatrixIdentity(&identity);
  D3DXMatrixLookAtLH(&view,&D3DXVECTOR3(0,0,-1),&D3DXVECTOR3(0,0,0),&D3DXVECTOR3(0,1,0));

  vs_const->SetMatrix(device,"ProjectionMatrix",&identity);
  vs_const->SetMatrix(device,"ViewMatrix",&identity);
  vs_const->SetMatrix(device,"WorldMatrix",&world);

  device->SetTexture(0,_surface->GetTexture(3));
  D3DXMatrixTranslation(&trans,-0.75f,-0.75f,0);
  D3DXMatrixScaling(&scl,0.5f,0.5f,0.5f);
  D3DXMatrixMultiply(&world,&scl,&trans);

  ps_texture->SetPixelShader(device);
  plane_->Draw(device);
  vs_const->SetMatrix(device,"WorldMatrix",&world);

  device->SetTexture(0,_surface->GetTexture(1));

  ps_texture->SetPixelShader(device);
  plane_->Draw(device);
  D3DXMatrixTranslation(&trans,-0.75f,-0.25f,0);
  D3DXMatrixMultiply(&world,&scl,&trans);
  vs_const->SetMatrix(device,"WorldMatrix",&world);
  device->SetTexture(0,_surface->GetTexture(2));
  plane_->Draw(device);
  D3DXMatrixTranslation(&trans,-0.75f,0.25f,0);
  D3DXMatrixMultiply(&world,&scl,&trans);
  vs_const->SetMatrix(device,"WorldMatrix",&world);
  device->SetTexture(0,_surface->GetTexture(0));
  plane_->Draw(device);

}



// EOF