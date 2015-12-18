#include "plane.h"
#include <crtdbg.h>

/// @brief コンストラクタ
Plane::Plane():
vertex_(nullptr) {
}

/// @brief デストラクタ
Plane::~Plane() {
}

/// @brief 初期化
void Plane::Initialize(LPDIRECT3DDEVICE9 device) {
	if (vertex_) return;

	VertexFormat vertex_data[4]
 = {
  {D3DXVECTOR3(-0.5f,+0.5f,0),D3DXVECTOR3(0,0,-1),D3DXCOLOR(1,1,1,1),D3DXVECTOR2(0,0)},
		{ D3DXVECTOR3(+0.5f, +0.5f, 0), D3DXVECTOR3(0, 0, -1), D3DXCOLOR(1, 1, 1, 1),D3DXVECTOR2(1,0) },
		{ D3DXVECTOR3(-0.5f, -0.5f, 0), D3DXVECTOR3(0, 0, -1), D3DXCOLOR(1, 1, 1, 1),D3DXVECTOR2(0,1) },
		{ D3DXVECTOR3(+0.5f, -0.5f, 0), D3DXVECTOR3(0, 0, -1), D3DXCOLOR(1, 1, 1, 1),D3DXVECTOR2(1,1) },
	};

	HRESULT ret;
	ret = device->CreateVertexBuffer(sizeof(vertex_data),
		D3DUSAGE_WRITEONLY,
		0,
		D3DPOOL_MANAGED,
		&vertex_,
		nullptr);
	_ASSERT_EXPR(SUCCEEDED(ret), L"頂点作れん");

	VertexFormat* access;
	vertex_->Lock(0, 0, (void**)&access, 0);

	memcpy_s(access, sizeof(vertex_data), vertex_data, sizeof(vertex_data));

	vertex_->Unlock();

	D3DVERTEXELEMENT9 element[] = {
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
  {0,24,D3DDECLTYPE_D3DCOLOR,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_COLOR,0},
  {0,28,D3DDECLTYPE_FLOAT2,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_TEXCOORD,0},
		D3DDECL_END()
	};

	device->CreateVertexDeclaration(element, &declaration_);

}

/// @brief 終了
void Plane::Finalize() {
	if (!vertex_) return;

	declaration_->Release();

	vertex_->Release();
	vertex_ = nullptr;
}

/// @brief 描画
void Plane::Draw(LPDIRECT3DDEVICE9 device) {
	device->SetVertexDeclaration(declaration_);
	device->SetStreamSource(0, vertex_, 0, sizeof(VertexFormat));
	device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
