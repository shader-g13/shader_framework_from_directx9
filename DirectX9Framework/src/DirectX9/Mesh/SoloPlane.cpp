/// @file SoloPlane.cpp
/// @brief 平面一枚
/// @date 2015/05/07
/// @author syuki nishida

#include <DirectX9/Mesh/SoloPlane.h>
#include <Util/SafeDelete.h>

/// @namespace snlib
namespace snlib {

VertexBuffer* SoloPlane::vertex_buffer_(nullptr);
LPDIRECT3DVERTEXDECLARATION9 SoloPlane::declaration_(nullptr);

/// @fn Used
/// @brief 初期化
/// @param[in] device デバイス
void SoloPlane::Used(LPDIRECT3DDEVICE9 device) {
	if (vertex_buffer_) return;

	D3DVERTEXELEMENT9 element[] = {
			{ 0, 0, D3DDECLTYPE_FLOAT3, 0, D3DDECLUSAGE_POSITION, 0 },
			{ 0, 12, D3DDECLTYPE_FLOAT3, 0, D3DDECLUSAGE_NORMAL, 0 },
			{ 0, 24, D3DDECLTYPE_FLOAT1, 0, D3DDECLUSAGE_TEXCOORD, 0 },
			D3DDECL_END()
	};
	device->CreateVertexDeclaration(element, &declaration_);

	float vertex_data[] = {
		// position      // normal // texcoord
		-0.5f, +0.5f, 0, 0, 0, -1, 0,
		+0.5f, +0.5f, 0, 0, 0, -1, 1,
		-0.5f, -0.5f, 0, 0, 0, -1, 2,
		+0.5f, -0.5f, 0, 0, 0, -1, 3,
	};

	vertex_buffer_ = new snlib::VertexBuffer(device, sizeof(vertex_data), 0);

	vertex_buffer_->SetData(0, sizeof(vertex_data), vertex_data);
	vertex_buffer_->SetStride(sizeof(float) * 7);
}

/// @fn Unused
/// @brief 終了
void SoloPlane::Unused() {
	if (!vertex_buffer_) return;

	SafeDelete(vertex_buffer_);

	declaration_->Release();
	declaration_ = nullptr;
}

/// @fn Draw
/// @brief 描画
/// @param[in] device デバイス
void SoloPlane::Draw(LPDIRECT3DDEVICE9 device) {
	vertex_buffer_->SetStreamSource(device, 0, 0);
	device->SetVertexDeclaration(declaration_);
	device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

} // namespace snlib

//EOF