/// @file SoloPlane.h
/// @brief ���ʈꖇ
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
	/// @brief ������
	/// @param[in] device �f�o�C�X
	static void Used(LPDIRECT3DDEVICE9 device);

	/// @fn Unused
	/// @brief �I��
	static void Unused();

	/// @fn Draw
	/// @brief �`��
	/// @param[in] device �f�o�C�X
	static void Draw(LPDIRECT3DDEVICE9 device);

protected:

private:
	/// @fn SoloPlane
	/// @brief �f�t�H���g�R���X�^���g
	SoloPlane() {}

	/// @fn ~SoloPlane
	/// @brief �f�t�H���g�f�X�g���N�^
	virtual ~SoloPlane() {}

	static VertexBuffer* vertex_buffer_;
	static LPDIRECT3DVERTEXDECLARATION9 declaration_;
};

} // namespace snlib

#endif // SNLIB_SOLO_PLANE_H_

// EOF