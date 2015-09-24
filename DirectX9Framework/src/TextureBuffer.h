/// @file TextureBuffer.h
/// @brief �e�N�X�`���o�b�t�@
/// @date 2015/05/11
/// @author syuki nishida

#pragma once
#ifndef SNLIB_TEXTURE_BUFFER_H_
#define SNLIB_TEXTURE_BUFFER_H_

#include <d3d9.h>
#include <map>
#include <string>

/// @namespace snlib
namespace snlib {

/// @class TextueBuffer
class TextureBuffer {
public:
	/// @fn TextureBuffer
	/// @brief �f�t�H���g�R���X�g���N�^
	TextureBuffer();

	/// @fn TextureBuffer
	/// @brief ���X�g���烍�[�h
	/// @param[in] key �L�[
	TextureBuffer(const char* key);

	/// @fn ~TextureBuffer
	/// @brief �f�t�H���g�f�X�g���N�^
	virtual ~TextureBuffer();

	/// @fn Load
	/// @brief ���X�g���烍�[�h
	/// @param[in] key �L�[
	/// @return ���[�h�ł����Ftrue
	bool Load(const char* key);

	/// @fn GetLoadFileName
	/// @brief �ǂ񂾃t�@�C�����擾
	/// @return �t�@�C����
	__forceinline const char* GetLoadFileName() { return key_; }

	/// @fn operator
	/// @brief �I�y���[�^
	__forceinline operator LPDIRECT3DTEXTURE9() {
		return buffer_ ? *buffer_ : nullptr;
	}

	/// @fn RegistTextureFromFile
	/// @brief �e�N�X�`�����t�@�C������ǂ�œo�^
	/// @param[in] device �f�o�C�X
	/// @param[in] filename �t�@�C����
	/// @return �o�^���Ă���Ffalse
	static bool RegistTextureFromFile(LPDIRECT3DDEVICE9 device, const char* filename);

	/// @fn UnregistTexture
	/// @brief �e�N�X�`�������X�g�������
	/// @param[in] key �����e�N�X�`���̃L�[
	/// @return �c��̎Q�Ɛ� ���̂��Ȃ��Ȃ�UINT_MAX
	static UINT UnregistTexture(const char* key);

	/// @fn Clear
	/// @brief ���X�g�̃e�N�X�`���S������
	static void Clear();

	/// @fn Restore
	/// @brief �e�N�X�`�����A
	/// @param[in] device �f�o�C�X
	static void Restore(LPDIRECT3DDEVICE9 device);

protected:
private:
	LPDIRECT3DTEXTURE9* buffer_;
	char key_[128];

	static std::map<std::string, std::pair<LPDIRECT3DTEXTURE9, UINT>> textures_;
};

} // namespace snlib

#endif // SNLIB_TEXTURE_BUFFER_H_

//EOF