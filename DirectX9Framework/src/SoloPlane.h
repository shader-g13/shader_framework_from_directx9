/// @file SoloPlane.h
/// @brief 平面一枚
/// @date 2015/05/07
/// @author syuki nishida

#pragma once
#ifndef SNLIB_SOLO_PLANE_H_
#define SNLIB_SOLO_PLANE_H_

#include "VertexBuffer.h"

/// @namespace snlib
namespace snlib {

/// @class SoloPlane
class SoloPlane {
public:
	/// @fn Used
	/// @brief 初期化
	/// @param[in] device デバイス
	static void Used(LPDIRECT3DDEVICE9 device);

	/// @fn Unused
	/// @brief 終了
	static void Unused();

	/// @fn Draw
	/// @brief 描画
	/// @param[in] device デバイス
	static void Draw(LPDIRECT3DDEVICE9 device);

protected:

private:
	/// @fn SoloPlane
	/// @brief デフォルトコンスタント
	SoloPlane() {}

	/// @fn ~SoloPlane
	/// @brief デフォルトデストラクタ
	virtual ~SoloPlane() {}

	static VertexBuffer* vertex_buffer_;
	static LPDIRECT3DVERTEXDECLARATION9 declaration_;
};

} // namespace snlib

#endif // SNLIB_SOLO_PLANE_H_

// EOF