/// @file VertexBuffer.h
/// @brief 頂点バッファ
/// @date 2015/04/21
/// @author syuki nishida

#pragma once
#ifndef SNLIB_VERTEX_BUFFER_H_
#define SNLIB_VERTEX_BUFFER_H_

#include <d3d9.h>

/// @namespace snlib
namespace snlib {

///@class VertexBuffer
class VertexBuffer {
public:
	/// @fn VertexBuffer
	/// @brief デフォルトコンストラクタ
	/// @param[in] device デバイス
	/// @param[in] size バッファサイズ
	/// @param[in] format 頂点フォーマット
	VertexBuffer(LPDIRECT3DDEVICE9 device, UINT size, DWORD format);

	/// @fn ~VertexBuffer
	/// @brief デストラクタ
	virtual ~VertexBuffer();

	/// @fn SetData
	/// @brief データ設定
	/// @param[in] offset オフセット
	/// @param[in] size サイズ
	/// @param[in] data 詰めるデータ
	void SetData(UINT offset, UINT size, const void* data);

	/// @fn GetData
	/// @brief データ取得（信頼性低い）
	/// @param[in] offset オフセット
	/// @param[in] size 取得するサイズ
	/// @param[out] ptr データを入れるポインタ
	void GetData(UINT offset, UINT size, void** data);

	/// @fn SetStride
	/// @brief 一つの頂点サイズ設定
	/// @param[in] stride ストライドサイズ
	__forceinline void SetStride(UINT stride) { stride_ = stride; }

	/// @fn SetStreamSource
	/// @brief ストリームへデータを流す
	/// @param[in] device デバイス
	/// @param[in] stream ストリーム番号
	/// @param[in] offset オフセット
	inline void SetStreamSource(LPDIRECT3DDEVICE9 device, UINT stream, UINT offset) {
		device->SetStreamSource(stream, vertex_buffer_, offset, stride_);
	}

protected:
private:
	LPDIRECT3DVERTEXBUFFER9 vertex_buffer_;
	UINT stride_;
};

} // namespace snlib

#endif // SNLIB_VERTEX_BUFFER_H_

//EOF