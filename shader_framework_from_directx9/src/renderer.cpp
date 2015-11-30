
#include "renderer.h"
#include <crtdbg.h>

#pragma comment (lib,"d3d9.lib")
#pragma comment (lib,"d3dx9.lib")

/// @brief コンストラクタ
Renderer::Renderer() :
device_(nullptr) {
}

/// @brief デストラクタ
Renderer::~Renderer() {
}

/// @brief 初期化
void Renderer::Initialize(HWND window_handle, UINT buffer_width, UINT buffer_heignt, bool windable) {
	if (device_) return;

	window_handle_ = window_handle;
	buffer_width_ = buffer_width;
	buffer_height_ = buffer_heignt;
	windable_ = windable;

	HRESULT ret;

	direct3d_ = Direct3DCreate9(D3D_SDK_VERSION);
	_ASSERT_EXPR(direct3d_, L"Direct3D作れんかった");

	D3DDISPLAYMODE display_mode;
	ret = direct3d_->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &display_mode);
	_ASSERT_EXPR(SUCCEEDED(ret), L"ディスプレイモードとれん");

	// デバイスのプレゼンテーションパラメータの設定
	D3DPRESENT_PARAMETERS present_param = {0};
	present_param.BackBufferCount  = 1;						// バックバッファの数
	present_param.BackBufferWidth  = buffer_width_;			// ゲーム画面サイズ(幅)
	present_param.BackBufferHeight = buffer_height_;		// ゲーム画面サイズ(高さ)
	present_param.BackBufferFormat = D3DFMT_UNKNOWN;		// バックバッファのフォーマットは現在設定されているものを使う
	present_param.SwapEffect       = D3DSWAPEFFECT_DISCARD;	// 映像信号に同期してフリップする
	present_param.Windowed         = windable_;				// ウィンドウモード
	present_param.EnableAutoDepthStencil = true;			// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
 present_param.AutoDepthStencilFormat = D3DFMT_D24S8;		// D3DFMT_D24S8 デプスバッファとして16bitを使う

	if (windable_) {// ウィンドウモード
		present_param.BackBufferFormat = D3DFMT_UNKNOWN;					// バックバッファ
		present_param.FullScreen_RefreshRateInHz = 0;						// リフレッシュレート
		present_param.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	// インターバル
	}
	else {// フルスクリーンモード
		present_param.BackBufferFormat = D3DFMT_R5G6B5;						// バックバッファ
		present_param.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// リフレッシュレート
		present_param.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// インターバル
	}

	// デバイス作成
	ret = direct3d_->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
		window_handle_, D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&present_param, &device_);
	_ASSERT_EXPR(SUCCEEDED(ret), L"デバイス作れない");

	//レンダーステートパラメータの処理
	device_->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	device_->SetRenderState(D3DRS_ZENABLE, TRUE);
	device_->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	device_->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	device_->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//device_->SetRenderState(D3DRS_FILLMODE,D3DFILL_WIREFRAME);
	device_->SetRenderState(D3DRS_LIGHTING, false);

	// サンプラーステートパラメータの設定
	device_->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(U値)を設定
	device_->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(V値)を設定
	device_->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// テクスチャ縮小フィルタモードを設定
	device_->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// テクスチャ拡大フィルタモードを設定

	// テクスチャステージステートの設定
	device_->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// アルファブレンディング処理を設定
	device_->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// 最初のアルファ引数
	device_->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// ２番目のアルファ引数
}

/// @biref 終了
void Renderer::Finalize() {
	if (!device_) return;

	ULONG ref_count;
	ref_count = device_->Release();
	_ASSERT_EXPR(!ref_count, L"開放忘れあるよ");
	device_ = nullptr;

	ref_count = direct3d_->Release();
	_ASSERT_EXPR(!ref_count, L"開放忘れあるよ");
	direct3d_ = nullptr;
}

/// @brief 描画開始
void Renderer::BegenDraw() {
	device_->Clear(0, nullptr,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0),
		1.0f, 0);

	device_->BeginScene();
}

/// @brief 描画終了
void Renderer::EndDraw() {
	device_->EndScene();
	device_->Present(NULL, NULL, NULL, NULL);
}
