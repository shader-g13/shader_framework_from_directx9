/// @file VertexBuffer.cpp
/// @brief ���_�o�b�t�@
/// @date 2015/04/21
/// @author syuki nishida

#include "VertexBuffer.h"
#include <crtdbg.h>
#include <stdio.h>

/// @namespace snlib
namespace snlib {

/// @fn VertexBuffer
/// @brief �f�t�H���g�R���X�g���N�^
/// @param[in] device �f�o�C�X
/// @param[in] size �o�b�t�@�T�C�Y
/// @param[in] format ���_�t�H�[�}�b�g
VertexBuffer::VertexBuffer(LPDIRECT3DDEVICE9 device, UINT size, DWORD format) {
	HRESULT result;
	result = device->CreateVertexBuffer(size, D3DUSAGE_WRITEONLY, format, D3DPOOL_MANAGED, &vertex_buffer_, nullptr);
	_ASSERT_EXPR(SUCCEEDED(result),
		L"snlib VertexBuffer error "
		L"���_�o�b�t�@�̍쐬�Ɏ��s");
#ifdef _DEBUG
	static UINT buffer_sun = 0;
	buffer_sun += size;
	printf("allocate buffer size if %d\n", size);
	printf("using buffer size is %d\n", buffer_sun);
#endif
}

/// @fn ~VertexBuffer
/// @brief �f�X�g���N�^
VertexBuffer::~VertexBuffer() {
	vertex_buffer_->Release();
}

/// @fn SetData
/// @brief �f�[�^�ݒ�
/// @param[in] offset �I�t�Z�b�g
/// @param[in] size �T�C�Y
/// @param[in] data �l�߂�f�[�^
void VertexBuffer::SetData(UINT offset, UINT size, const void* data) {
	void* access = nullptr;
	vertex_buffer_->Lock(offset, size, &access, 0);
	memcpy_s(access, size, data, size);
	vertex_buffer_->Unlock();
}

/// @fn GetData
/// @brief �f�[�^�擾�i�M�����Ⴂ�j
/// @param[in] offset �I�t�Z�b�g
/// @param[in] size �擾����T�C�Y
/// @param[out] ptr �f�[�^������|�C���^
void VertexBuffer::GetData(UINT offset, UINT size, void** data) {
	void* access = nullptr;
	vertex_buffer_->Lock(offset, size, &access, D3DLOCK_READONLY);
	memcpy_s(*data, size, access, size);
	vertex_buffer_->Unlock();
}

} // namespace snlib

//EOF