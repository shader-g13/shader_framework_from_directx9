/// @file VertexBuffer.h
/// @brief ���_�o�b�t�@
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
	/// @brief �f�t�H���g�R���X�g���N�^
	/// @param[in] device �f�o�C�X
	/// @param[in] size �o�b�t�@�T�C�Y
	/// @param[in] format ���_�t�H�[�}�b�g
	VertexBuffer(LPDIRECT3DDEVICE9 device, UINT size, DWORD format);

	/// @fn ~VertexBuffer
	/// @brief �f�X�g���N�^
	virtual ~VertexBuffer();

	/// @fn SetData
	/// @brief �f�[�^�ݒ�
	/// @param[in] offset �I�t�Z�b�g
	/// @param[in] size �T�C�Y
	/// @param[in] data �l�߂�f�[�^
	void SetData(UINT offset, UINT size, const void* data);

	/// @fn GetData
	/// @brief �f�[�^�擾�i�M�����Ⴂ�j
	/// @param[in] offset �I�t�Z�b�g
	/// @param[in] size �擾����T�C�Y
	/// @param[out] ptr �f�[�^������|�C���^
	void GetData(UINT offset, UINT size, void** data);

	/// @fn SetStride
	/// @brief ��̒��_�T�C�Y�ݒ�
	/// @param[in] stride �X�g���C�h�T�C�Y
	__forceinline void SetStride(UINT stride) { stride_ = stride; }

	/// @fn SetStreamSource
	/// @brief �X�g���[���փf�[�^�𗬂�
	/// @param[in] device �f�o�C�X
	/// @param[in] stream �X�g���[���ԍ�
	/// @param[in] offset �I�t�Z�b�g
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