/// @file VertexBuffer.cpp
/// @brief 頂点バッファ
/// @date 2015/04/21
/// @author syuki nishida

#include "VertexBuffer.h"
#include <crtdbg.h>
#include <stdio.h>

/// @namespace snlib
namespace snlib {

/// @fn VertexBuffer
/// @brief デフォルトコンストラクタ
/// @param[in] device デバイス
/// @param[in] size バッファサイズ
/// @param[in] format 頂点フォーマット
VertexBuffer::VertexBuffer(LPDIRECT3DDEVICE9 device, UINT size, DWORD format) {
	HRESULT result;
	result = device->CreateVertexBuffer(size, D3DUSAGE_WRITEONLY, format, D3DPOOL_MANAGED, &vertex_buffer_, nullptr);
	_ASSERT_EXPR(SUCCEEDED(result),
		L"snlib VertexBuffer error "
		L"頂点バッファの作成に失敗");
#ifdef _DEBUG
	static UINT buffer_sun = 0;
	buffer_sun += size;
	printf("allocate buffer size if %d\n", size);
	printf("using buffer size is %d\n", buffer_sun);
#endif
}

/// @fn ~VertexBuffer
/// @brief デストラクタ
VertexBuffer::~VertexBuffer() {
	vertex_buffer_->Release();
}

/// @fn SetData
/// @brief データ設定
/// @param[in] offset オフセット
/// @param[in] size サイズ
/// @param[in] data 詰めるデータ
void VertexBuffer::SetData(UINT offset, UINT size, const void* data) {
	void* access = nullptr;
	vertex_buffer_->Lock(offset, size, &access, 0);
	memcpy_s(access, size, data, size);
	vertex_buffer_->Unlock();
}

/// @fn GetData
/// @brief データ取得（信頼性低い）
/// @param[in] offset オフセット
/// @param[in] size 取得するサイズ
/// @param[out] ptr データを入れるポインタ
void VertexBuffer::GetData(UINT offset, UINT size, void** data) {
	void* access = nullptr;
	vertex_buffer_->Lock(offset, size, &access, D3DLOCK_READONLY);
	memcpy_s(*data, size, access, size);
	vertex_buffer_->Unlock();
}

} // namespace snlib

//EOF