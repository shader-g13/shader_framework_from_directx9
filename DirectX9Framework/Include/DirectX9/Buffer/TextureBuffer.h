/// @file TextureBuffer.h
/// @brief テクスチャバッファ
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
	/// @brief デフォルトコンストラクタ
	TextureBuffer();

	/// @fn TextureBuffer
	/// @brief リストからロード
	/// @param[in] key キー
	TextureBuffer(const char* key);

	/// @fn ~TextureBuffer
	/// @brief デフォルトデストラクタ
	virtual ~TextureBuffer();

	/// @fn Load
	/// @brief リストからロード
	/// @param[in] key キー
	/// @return ロードできた：true
	bool Load(const char* key);

	/// @fn GetLoadFileName
	/// @brief 読んだファイル名取得
	/// @return ファイル名
	__forceinline const char* GetLoadFileName() { return key_; }

	/// @fn operator
	/// @brief オペレータ
	__forceinline operator LPDIRECT3DTEXTURE9() {
		return buffer_ ? *buffer_ : nullptr;
	}

	/// @fn RegistTextureFromFile
	/// @brief テクスチャをファイルから読んで登録
	/// @param[in] device デバイス
	/// @param[in] filename ファイル名
	/// @return 登録してある：false
	static bool RegistTextureFromFile(LPDIRECT3DDEVICE9 device, const char* filename);

	/// @fn UnregistTexture
	/// @brief テクスチャをリストから消す
	/// @param[in] key 消すテクスチャのキー
	/// @return 残りの参照数 ものがないならUINT_MAX
	static UINT UnregistTexture(const char* key);

	/// @fn Clear
	/// @brief リストのテクスチャ全部消す
	static void Clear();

	/// @fn Restore
	/// @brief テクスチャ復帰
	/// @param[in] device デバイス
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