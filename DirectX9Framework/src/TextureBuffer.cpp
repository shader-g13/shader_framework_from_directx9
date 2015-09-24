/// @file TextureBuffer.cpp
/// @brief �e�N�X�`���o�b�t�@
/// @date 2015/05/11
/// @author syuki nishida

#include "TextureBuffer.h"
#include <d3dx9.h>

/// @namespace snlib
namespace snlib {

std::map<std::string, std::pair<LPDIRECT3DTEXTURE9, UINT>> TextureBuffer::textures_;

/// @fn TextureBuffer
/// @brief �f�t�H���g�R���X�g���N�^
TextureBuffer::TextureBuffer()
 : buffer_(nullptr) {
}

/// @fn TextureBuffer
/// @brief ���X�g���烍�[�h
/// @param[in] key �L�[
TextureBuffer::TextureBuffer(const char* key) {
	bool ret = Load(key);
	_ASSERT_EXPR(ret, L"snlib TextureBuffer error "
		L"�Ώۂ̃e�N�X�`�����Ȃ�");
}

/// @fn ~TextureBuffer
/// @brief �f�t�H���g�f�X�g���N�^
TextureBuffer::~TextureBuffer() {
	UnregistTexture(key_);
}

/// @fn Load
/// @brief ���X�g���烍�[�h
/// @param[in] key �L�[
/// @return ���[�h�ł����Ftrue
bool TextureBuffer::Load(const char* key) {
	// ���[�h�Ώۊm�F
	if (!textures_.count(key)) return false;

  if (buffer_) {
    textures_[key].second--;
  }

	// �o�b�t�@�Ɋi�[
	buffer_ = &textures_[key].first;
	strcpy_s<128>(key_, key);

	// ���t�@�����X���Z
	textures_[key].second++;

	return true;
}

/// @fn RegistTextureFromFile
/// @brief �e�N�X�`�����t�@�C������ǂ�œo�^
/// @param[in] device �f�o�C�X
/// @param[in] filename �t�@�C����
/// @return �o�^���Ă���Ffalse
bool TextureBuffer::RegistTextureFromFile(LPDIRECT3DDEVICE9 device, const char* filename) {
	// �o�^���Ă�������I���
	if (textures_.count(filename)) return false;

	// �t�@�C��������
	if (!filename[0]) return false;

	std::pair<LPDIRECT3DTEXTURE9, UINT> data(nullptr, 1);
	HRESULT ret;

	ret = D3DXCreateTextureFromFileExA(device, filename, 0, 0, 1, 0, D3DFMT_A8B8G8R8, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, nullptr, nullptr, &data.first);
	_ASSERT_EXPR(SUCCEEDED(ret),
		L"snlib TextureBuffer error "
		L"�e�N�X�`�����t�@�C������쐬�ł��Ȃ�����");

	std::pair<std::string, std::pair<LPDIRECT3DTEXTURE9, UINT>> pair(filename, data);
	textures_.insert(pair);

	return true;
}

/// @fn UnregistTexture
/// @brief �e�N�X�`�������X�g�������
/// @param[in] key �����e�N�X�`���̃L�[
/// @return �c��̎Q�Ɛ�
UINT TextureBuffer::UnregistTexture(const char* key) {
	// �������̂����������Ȃ�
	if (!textures_.count(key)) return UINT_MAX;

	textures_[key].second--;
	if (textures_[key].second) {
		return textures_[key].second;
	}

	// ���
	ULONG ref_cnt = textures_[key].first->Release();
	_ASSERT_EXPR(!ref_cnt,
		L"snlib TextureBuffer error "
		L"�e�N�X�`��������ɉ���ł��Ȃ�����");
	textures_.erase(key);

	return 0;
}

/// @fn Clear
/// @brief ���X�g�̃e�N�X�`���S������
void TextureBuffer::Clear() {
	// �R���e���p�j
	for (auto it : textures_) {
		// �e�N�X�`���̃|�C���^�����邩
		if (!it.second.first) continue;
		// ���
		ULONG ref_cnt = it.second.first->Release();
		_ASSERT_EXPR(!ref_cnt,
			L"snlib TextureBuffer error "
			L"�e�N�X�`��������ɉ���ł��Ȃ�����");
	}
	// �R���e�i��
	textures_.clear();
}

/// @fn Restore
/// @brief �e�N�X�`�����A
/// @param[in] device �f�o�C�X
void TextureBuffer::Restore(LPDIRECT3DDEVICE9 device) {
	// �R���e�i�p�j
	for (auto it = textures_.begin(); it != textures_.end(); ++it) {
		// �l�����邩
		if (!it->second.first) continue;
		// ������e�N�X�`���J��
		it->second.first->Release();
		// �e�N�X�`���ǂݒ���
		HRESULT ret = D3DXCreateTextureFromFileExA(
			device,
			it->first.c_str(),
			0, 0, 1, 0,
			D3DFMT_A8B8G8R8, D3DPOOL_DEFAULT,
			D3DX_DEFAULT, D3DX_DEFAULT,
			0, nullptr, nullptr,
			&it->second.first);
		_ASSERT_EXPR(SUCCEEDED(ret),
			L"snlib TextureBuffer error "
			L"�e�N�X�`�����t�@�C������쐬�ł��Ȃ�����");
	}
}

} // namespace snlib

//EOF