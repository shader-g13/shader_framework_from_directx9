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
 D3DXComputeTangentFrameEx(original_mesh,
                           D3DDECLUSAGE_TEXCOORD,
                           0,
                           D3DDECLUSAGE_TANGENT,
                           0,
                           D3DDECLUSAGE_BINORMAL,
                           0,
                           D3DDECLUSAGE_NORMAL,
                           0,
                           0,
                           nullptr,
                           0.01f,
                           0.25f,
                           0.01f,
                           &mesh_,
                           nullptr);

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

		mesh_->DrawSubset(i);
	}

	device->SetMaterial(&original_material);
}
