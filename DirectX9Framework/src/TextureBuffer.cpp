/// @file TextureBuffer.cpp
/// @brief テクスチャバッファ
/// @date 2015/05/11
/// @author syuki nishida

#include "TextureBuffer.h"
#include <d3dx9.h>

/// @namespace snlib
namespace snlib {

std::map<std::string, std::pair<LPDIRECT3DTEXTURE9, UINT>> TextureBuffer::textures_;

/// @fn TextureBuffer
/// @brief デフォルトコンストラクタ
TextureBuffer::TextureBuffer()
 : buffer_(nullptr) {
}

/// @fn TextureBuffer
/// @brief リストからロード
/// @param[in] key キー
TextureBuffer::TextureBuffer(const char* key) {
	bool ret = Load(key);
	_ASSERT_EXPR(ret, L"snlib TextureBuffer error "
		L"対象のテクスチャがない");
}

/// @fn ~TextureBuffer
/// @brief デフォルトデストラクタ
TextureBuffer::~TextureBuffer() {
	UnregistTexture(key_);
}

/// @fn Load
/// @brief リストからロード
/// @param[in] key キー
/// @return ロードできた：true
bool TextureBuffer::Load(const char* key) {
	// ロード対象確認
	if (!textures_.count(key)) return false;

  if (buffer_) {
    textures_[key].second--;
  }

	// バッファに格納
	buffer_ = &textures_[key].first;
	strcpy_s<128>(key_, key);

	// リファレンス加算
	textures_[key].second++;

	return true;
}

/// @fn RegistTextureFromFile
/// @brief テクスチャをファイルから読んで登録
/// @param[in] device デバイス
/// @param[in] filename ファイル名
/// @return 登録してある：false
bool TextureBuffer::RegistTextureFromFile(LPDIRECT3DDEVICE9 device, const char* filename) {
	// 登録してあったら終わる
	if (textures_.count(filename)) return false;

	// ファイル名が空
	if (!filename[0]) return false;

	std::pair<LPDIRECT3DTEXTURE9, UINT> data(nullptr, 1);
	HRESULT ret;

	ret = D3DXCreateTextureFromFileExA(device, filename, 0, 0, 1, 0, D3DFMT_A8B8G8R8, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, nullptr, nullptr, &data.first);
	_ASSERT_EXPR(SUCCEEDED(ret),
		L"snlib TextureBuffer error "
		L"テクスチャがファイルから作成できなかった");

	std::pair<std::string, std::pair<LPDIRECT3DTEXTURE9, UINT>> pair(filename, data);
	textures_.insert(pair);

	return true;
}

/// @fn UnregistTexture
/// @brief テクスチャをリストから消す
/// @param[in] key 消すテクスチャのキー
/// @return 残りの参照数
UINT TextureBuffer::UnregistTexture(const char* key) {
	// 消すものがそもそもない
	if (!textures_.count(key)) return UINT_MAX;

	textures_[key].second--;
	if (textures_[key].second) {
		return textures_[key].second;
	}

	// 解放
	ULONG ref_cnt = textures_[key].first->Release();
	_ASSERT_EXPR(!ref_cnt,
		L"snlib TextureBuffer error "
		L"テクスチャが正常に解放できなかった");
	textures_.erase(key);

	return 0;
}

/// @fn Clear
/// @brief リストのテクスチャ全部消す
void TextureBuffer::Clear() {
	// コンテン徘徊
	for (auto it : textures_) {
		// テクスチャのポインタがあるか
		if (!it.second.first) continue;
		// 解放
		ULONG ref_cnt = it.second.first->Release();
		_ASSERT_EXPR(!ref_cnt,
			L"snlib TextureBuffer error "
			L"テクスチャが正常に解放できなかった");
	}
	// コンテナ空
	textures_.clear();
}

/// @fn Restore
/// @brief テクスチャ復帰
/// @param[in] device デバイス
void TextureBuffer::Restore(LPDIRECT3DDEVICE9 device) {
	// コンテナ徘徊
	for (auto it = textures_.begin(); it != textures_.end(); ++it) {
		// 値があるか
		if (!it->second.first) continue;
		// 今あるテクスチャ開放
		it->second.first->Release();
		// テクスチャ読み直し
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
			L"テクスチャがファイルから作成できなかった");
	}
}

} // namespace snlib

//EOF