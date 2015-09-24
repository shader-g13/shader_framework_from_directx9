#include "xmodel.h"
#include <d3dx9.h>
#include <crtdbg.h>

/// @brief コンストラクタ
XModel::XModel():
mesh_(nullptr) {
}

/// @brief デストラクタ
XModel::~XModel() {
}

/// @brief 初期化
void XModel::Initialize(LPDIRECT3DDEVICE9 device, char* filename) {
	if (mesh_) return;

	LPD3DXMESH		original_mesh;
	LPD3DXBUFFER	material_data;
	LPD3DXBUFFER	adjcency;

	HRESULT ret;
	ret = D3DXLoadMeshFromX(filename, D3DXMESH_MANAGED, device, &adjcency,
		&material_data, nullptr, &material_count_, &original_mesh);
	_ASSERT_EXPR(SUCCEEDED(ret), L"Xファイル読めん");

	ret = original_mesh->OptimizeInplace(D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE,
		(DWORD*)adjcency->GetBufferPointer(), nullptr, nullptr, nullptr);
	_ASSERT_EXPR(SUCCEEDED(ret), L"オプティマイズできん");
	adjcency->Release();

	D3DVERTEXELEMENT9 element[] = {
  {0,0,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_POSITION,0},
  {0,12,D3DDECLTYPE_FLOAT2,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_TEXCOORD,0},
  {0,20,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_NORMAL,0},
  {0,32,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_TANGENT,0},
  {0,44,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_BINORMAL,0},
  D3DDECL_END()
 };
	ret = device->CreateVertexDeclaration(element, &declaration_);
	_ASSERT_EXPR(SUCCEEDED(ret), L"デクラレーション作れん");

	ret = original_mesh->CloneMesh(D3DXMESH_MANAGED, element, device, &mesh_);
	_ASSERT_EXPR(SUCCEEDED(ret), L"クローンできん");
	original_mesh->Release();

	//D3DXComputeNormals(mesh_, nullptr);

	D3DXMATERIAL* material_access = (D3DXMATERIAL*)material_data->GetBufferPointer();

	material_ = new Material[material_count_];
	for (UINT i = 0; i < material_count_; i++) {	
		material_[i].material = material_access[i].MatD3D;
		material_[i].texture = nullptr;
		D3DXCreateTextureFromFile(device, material_access[i].pTextureFilename, &material_[i].texture);
	}
	material_data->Release();
}

/// @brief 終了
void XModel::Finalize() {
	if (!mesh_) return;

	delete[] material_;

	mesh_->Release();
	mesh_ = nullptr;

	declaration_->Release();
	declaration_ = nullptr;
}

/// @brief 描画
void XModel::Draw(LPDIRECT3DDEVICE9 device) {
	D3DMATERIAL9 original_material;

	device->GetMaterial(&original_material);
	device->SetVertexDeclaration(declaration_);

	for (UINT i = 0; i < material_count_; i++) {
		device->SetMaterial(&material_[i].material);
		device->SetTexture(0, material_[i].texture);
		mesh_->DrawSubset(i);
	}

	device->SetMaterial(&original_material);
}
// 3頂点とUV値から指定座標でのU軸（Tangent）及びV軸（Binormal）を算出
//
// p0, p1, p2    : ローカル空間での頂点座標（ポリゴン描画順にすること）
// uv0, uv1, uv2 : 各頂点のUV座標
// outTangent    : U軸（Tangent）出力
// outBinormal   : V軸（Binormal）出力

void XModel::CalcTangentAndBinormal(
 D3DXVECTOR3* p0,D3DXVECTOR2* uv0,
 D3DXVECTOR3* p1,D3DXVECTOR2* uv1,
 D3DXVECTOR3* p2,D3DXVECTOR2* uv2,
 D3DXVECTOR3* outTangent,D3DXVECTOR3* outBinormal
 ) {
 // 5次元→3次元頂点に
 D3DXVECTOR3 CP0[3] = {
  D3DXVECTOR3(p0->x,uv0->x,uv0->y),
  D3DXVECTOR3(p0->y,uv0->x,uv0->y),
  D3DXVECTOR3(p0->z,uv0->x,uv0->y),
 };
 D3DXVECTOR3 CP1[3] = {
  D3DXVECTOR3(p1->x,uv1->x,uv1->y),
  D3DXVECTOR3(p1->y,uv1->x,uv1->y),
  D3DXVECTOR3(p1->z,uv1->x,uv1->y),
 };
 D3DXVECTOR3 CP2[3] = {
  D3DXVECTOR3(p2->x,uv2->x,uv2->y),
  D3DXVECTOR3(p2->y,uv2->x,uv2->y),
  D3DXVECTOR3(p2->z,uv2->x,uv2->y),
 };

 // 平面パラメータからUV軸座標算出
 float U[3],V[3];
 for(int i = 0; i < 3; ++i) {
  D3DXVECTOR3 V1 = CP1[i] - CP0[i];
  D3DXVECTOR3 V2 = CP2[i] - CP1[i];
  D3DXVECTOR3 ABC;
  D3DXVec3Cross(&ABC,&V1,&V2);

  if(ABC.x == 0.0f) {
   // やばいす！
   // ポリゴンかUV上のポリゴンが縮退してます！
   _ASSERT(0);
   memset(outTangent,0,sizeof(D3DXVECTOR3));
   memset(outBinormal,0,sizeof(D3DXVECTOR3));
   return;
  }
  U[i] = -ABC.y / ABC.x;
  V[i] = -ABC.z / ABC.x;
 }

 memcpy(outTangent,U,sizeof(float) * 3);
 memcpy(outBinormal,V,sizeof(float) * 3);

 // 正規化します
 D3DXVec3Normalize(outTangent,outTangent);
 D3DXVec3Normalize(outBinormal,outBinormal);
}