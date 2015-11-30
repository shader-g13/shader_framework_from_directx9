/// @file Surface.cpp
/// @brief サーフェース
/// @date 2015/05/21
/// @author syuki nishida

#include "Surface.h"
#include <crtdbg.h>

/// @namespace snlib
namespace snlib {

LPDIRECT3DSURFACE9 Surface::default_color_surface_ = nullptr;
LPDIRECT3DSURFACE9 Surface::default_depth_surface_ = nullptr;

/// @fn Surface
/// @brief デフォルトコンストラクタ
/// @param[in] device デバイス
/// @param[in] width 幅
/// @param[in] height 高さ
/// @param[in] texture_count テクスチャ枚数
Surface::Surface(LPDIRECT3DDEVICE9 device, UINT width, UINT height, UINT texture_count)
 : clear_color_(0x00000000),
   texture_(nullptr),
   color_surface_(nullptr),
   depth_surface_(nullptr),
   width_(width),
   height_(height),
   texture_count_(texture_count) {

	HRESULT ret = 0;

	texture_ = new LPDIRECT3DTEXTURE9[texture_count_];
	color_surface_ = new LPDIRECT3DSURFACE9[texture_count_];

	for (UINT i = 0; i < texture_count_; i++) {
		ret = device->CreateTexture(width_, height_, 1, D3DUSAGE_RENDERTARGET,
			D3DFMT_A32B32G32R32F, D3DPOOL_DEFAULT, &texture_[i], nullptr);
		_ASSERT_EXPR(SUCCEEDED(ret), L"create surface texture failed");

		ret = texture_[i]->GetSurfaceLevel(0, &color_surface_[i]);
		_ASSERT_EXPR(SUCCEEDED(ret), L"get color surface failed");
	}

	ret = device->CreateDepthStencilSurface(width_, height_, D3DFMT_D24S8,
		D3DMULTISAMPLE_NONE, 0, true, &depth_surface_, nullptr);
	_ASSERT_EXPR(SUCCEEDED(ret), L"create depth surface failed");
}

/// @fn ~Surface
/// @brief デフォルトデストラクタ
Surface::~Surface() {
	for (UINT i = 0; i < texture_count_; i++) {
		texture_[i]->Release();
		color_surface_[i]->Release();
	}
	delete[] texture_;
	delete[] color_surface_;

	depth_surface_->Release();
}

} // namespace snlib

//EOF