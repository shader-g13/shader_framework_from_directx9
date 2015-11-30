#include "main.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CLASS_NAME		"AppClass"				// ウインドウのクラス名
#define WINDOW_NAME		"DX11ポリゴン描画"	// ウインドウのキャプション名


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

void InitPolygon(void);
void UninitPolygon(void);
void UpdatePolygon(void);
void DrawPolygon(void);

using namespace DirectX;
using namespace SimpleMath;
//*****************************************************************************
// グローバル変数:
//*****************************************************************************
D3D_FEATURE_LEVEL       g_FeatureLevel = D3D_FEATURE_LEVEL_11_0;

ID3D11Device*           g_pD3DDevice = NULL;
ID3D11DeviceContext*    g_pImmediateContext = NULL;
IDXGISwapChain*         g_pSwapChain = NULL;
ID3D11RenderTargetView* g_pRenderTargetView = NULL;

ID3D11VertexShader*     g_pVertexShader = NULL;
ID3D11PixelShader*      g_pPixelShader = NULL;

ID3D11InputLayout*      g_pVertexLayout = NULL;
ID3D11Buffer*           g_pVertexBuffer = NULL;

ID3D11ShaderResourceView* g_pShaderResView = NULL;

ID3D11Buffer*			g_pConstantBuffer = NULL;


//=============================================================================
// メイン関数
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};
	HWND hWnd;
	MSG msg;

	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// ウィンドウの作成
	hWnd = CreateWindowEx(0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2),
		(SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION)),
		NULL,
		NULL,
		hInstance,
		NULL);

	// 初期化処理(ウィンドウを作成してから行う)
	if(FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}

	// ウインドウの表示(初期化処理の後に行う)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// メッセージループ
	while(1)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{// Windowsの処理
			if(msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				// メッセージの翻訳と送出
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{// DirectXの処理
			// 更新処理
			Update();

			// 描画処理
			Draw();
		}
	}

	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// 終了処理
	Uninit();

	return (int)msg.wParam;
}


//=============================================================================
// ウインドウプロシージャ
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	switch(uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


//=============================================================================
// 初期化処理
// hInstance : インスタンスのハンドル
// hWnd      : ウインドウのハンドル
// bWindow   : ウインドウモードにするかどうか
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	HRESULT hr = S_OK;

	// デバイス、スワップチェーン、コンテキスト生成
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory( &sd, sizeof( sd ) );
	sd.BufferCount = 1;
	sd.BufferDesc.Width = SCREEN_WIDTH;
	sd.BufferDesc.Height = SCREEN_HEIGHT;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	hr = D3D11CreateDeviceAndSwapChain( NULL,
										D3D_DRIVER_TYPE_WARP,
										NULL,
										0,
										NULL,
										0,
										D3D11_SDK_VERSION,
										&sd,
										&g_pSwapChain,
										&g_pD3DDevice,
										&g_FeatureLevel,
										&g_pImmediateContext );
	if( FAILED( hr ) )
		return hr;


	// レンダーターゲットビュー生成、設定
	ID3D11Texture2D* pBackBuffer = NULL;
	g_pSwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&pBackBuffer );
	g_pD3DDevice->CreateRenderTargetView( pBackBuffer, NULL, &g_pRenderTargetView );
	pBackBuffer->Release();
	g_pImmediateContext->OMSetRenderTargets( 1, &g_pRenderTargetView, NULL );


	// ビューポート設定
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)SCREEN_WIDTH;
	vp.Height = (FLOAT)SCREEN_HEIGHT;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	g_pImmediateContext->RSSetViewports( 1, &vp );

	// 頂点シェーダコンパイル・生成
	ID3DBlob* pErrorBlob;
	ID3DBlob* pVSBlob = NULL;
	hr = D3DCompileFromFile( L"shader.hlsl", NULL, NULL, "VertexShaderPolygon", "vs_4_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, &pVSBlob, &pErrorBlob);
	if( FAILED(hr) )
	{
		MessageBox( NULL , (char*)pErrorBlob->GetBufferPointer(), "VS", MB_OK | MB_ICONERROR );
	}

	g_pD3DDevice->CreateVertexShader( pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, &g_pVertexShader );

	// 入力レイアウト生成
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
  {"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
  {"NORMAL",0,DXGI_FORMAT_R32G32B32_FLOAT,0,4 * 3,D3D11_INPUT_PER_VERTEX_DATA,0},
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 4 * 3 * 2, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = ARRAYSIZE( layout );

	g_pD3DDevice->CreateInputLayout( layout,
		numElements,
		pVSBlob->GetBufferPointer(),
		pVSBlob->GetBufferSize(),
		&g_pVertexLayout );

	pVSBlob->Release();


	// ピクセルシェーダコンパイル・生成
	ID3DBlob* pPSBlob = NULL;
 hr = D3DCompileFromFile(L"shader.hlsl",NULL,NULL,"PixelShaderPolygon","ps_4_0",D3DCOMPILE_ENABLE_STRICTNESS,0,&pPSBlob,&pErrorBlob);
	if( FAILED(hr) )
	{
		MessageBox( NULL , (char*)pErrorBlob->GetBufferPointer(), "PS", MB_OK | MB_ICONERROR );
	}

	g_pD3DDevice->CreatePixelShader( pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, &g_pPixelShader );
	
	pPSBlob->Release();

	// 定数バッファ生成
	D3D11_BUFFER_DESC hBufferDesc;
	hBufferDesc.ByteWidth = sizeof(ConstantBuffer);
	hBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	hBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	hBufferDesc.CPUAccessFlags = 0;
	hBufferDesc.MiscFlags = 0;
	hBufferDesc.StructureByteStride = sizeof(float);

	if( FAILED( g_pD3DDevice->CreateBuffer( &hBufferDesc, NULL, &g_pConstantBuffer ) ) )
	{
		MessageBox(hWnd, "Create ConstantBuffer", "Err", MB_ICONSTOP);
	}


	// ポリゴンの初期化処理
	InitPolygon();


	return S_OK;
}


//=============================================================================
// 終了処理
//=============================================================================
void Uninit(void)
{
	// ポリゴン終了処理
	UninitPolygon();

	// オブジェクト解放
	if( g_pImmediateContext )	g_pImmediateContext->ClearState();
	if( g_pVertexLayout )		g_pVertexLayout->Release();
	if( g_pVertexShader )		g_pVertexShader->Release();
	if( g_pPixelShader )		g_pPixelShader->Release();
	if( g_pRenderTargetView )	g_pRenderTargetView->Release();
	if( g_pSwapChain )			g_pSwapChain->Release();
	if( g_pImmediateContext )	g_pImmediateContext->Release();
	if( g_pD3DDevice )			g_pD3DDevice->Release();

}


//=============================================================================
// 更新処理
//=============================================================================
void Update(void)
{
	// ポリゴン更新
	UpdatePolygon();
}


//=============================================================================
// 描画処理
//=============================================================================
void Draw(void)
{
	// バックバッファクリア
	float ClearColor[4] = { 0.0f, 0.5f, 0.0f, 1.0f };
	g_pImmediateContext->ClearRenderTargetView( g_pRenderTargetView, ClearColor );

	// ポリゴン描画
	DrawPolygon();

	// バックバッファ、フロントバッファ入れ替え
	g_pSwapChain->Present( 0, 0 );
}


//=============================================================================
// 初期化処理
//=============================================================================
void InitPolygon(void)
{
	HRESULT hr = S_OK;


	// 頂点バッファ生成
	Vertex3D *vertex = new Vertex3D[4];

	vertex[0].Position = Vector3( -0.5f, 0.5f, 0.0f );
 vertex[0].Normal = Vector3(0.0f,0.0f,-1.0f);
 vertex[0].TexCoord = Vector2(0.0f,0.0f);

 vertex[1].Position = Vector3(0.5f,0.5f,0.0f);
 vertex[1].Normal = Vector3(0.0f,0.0f,-1.0f);
 vertex[1].TexCoord = Vector2(1.0f,0.0f);

 vertex[2].Position = Vector3(-0.5f,-0.5f,0.0f);
 vertex[2].Normal = Vector3(0.0f,0.0f,-1.0f);
 vertex[2].TexCoord = Vector2(0.0f,1.0f);

 vertex[3].Position = Vector3(0.5f,-0.5f,0.0f);
 vertex[3].Normal = Vector3(0.0f,0.0f,-1.0f);
 vertex[3].TexCoord = Vector2(1.0f,1.0f);

	D3D11_BUFFER_DESC bd;
	ZeroMemory( &bd, sizeof(bd) );
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof( Vertex3D ) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory( &sd, sizeof(sd) );
	sd.pSysMem = vertex;

	hr = g_pD3DDevice->CreateBuffer( &bd, &sd, &g_pVertexBuffer );

	delete[] vertex;

 TexMetadata meta;
 ScratchImage image;
	// テクスチャ生成
 hr = LoadFromDDSFile(L"data/field004.dds",
                 0,
                 &meta,
                 image);
 
 _ASSERT_EXPR(SUCCEEDED(hr),L"LoadFromWICFile失敗");

 hr = CreateShaderResourceView(g_pD3DDevice,image.GetImages(),image.GetImageCount(),image.GetMetadata(),&g_pShaderResView);
 _ASSERT_EXPR(SUCCEEDED(hr),L"CreateShaderResourceView失敗");

}


//=============================================================================
// 終了処理
//=============================================================================
void UninitPolygon(void)
{
	if( g_pVertexBuffer )	g_pVertexBuffer->Release();
	if( g_pShaderResView )	g_pShaderResView->Release();
}


//=============================================================================
// 更新処理
//=============================================================================
void UpdatePolygon(void)
{

}


//=============================================================================
// 描画処理
//=============================================================================
void DrawPolygon(void)
{
	// 頂点バッファ設定
	UINT stride = sizeof( Vertex3D );
	UINT offset = 0;
	g_pImmediateContext->IASetVertexBuffers( 0, 1, &g_pVertexBuffer, &stride, &offset );

	// プリミティブタイプ設定
	g_pImmediateContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );

	// 入力レイアウト設定
	g_pImmediateContext->IASetInputLayout( g_pVertexLayout );

	// シェーダ設定
	g_pImmediateContext->VSSetShader( g_pVertexShader, NULL, 0 );
	g_pImmediateContext->PSSetShader( g_pPixelShader, NULL, 0 );



	// マトリクス設定
	Matrix world, view, projection,camera_rot;
 //下準備
 static Vector3 box_rot(0,0,0);
 static float cam_rot = 0;
 cam_rot += 0.001f;
 ConstantBuffer cb;
 g_pImmediateContext->VSSetConstantBuffers(0,1,&g_pConstantBuffer);
 g_pImmediateContext->PSSetConstantBuffers(0,1,&g_pConstantBuffer);
 world = Matrix::Identity;
 camera_rot = Matrix::CreateRotationY(cam_rot);
 view = Matrix::CreateLookAt(Vector3::Transform(Vector3(0.0f,2.0f,-3.0f),camera_rot),
                             Vector3(0.0f,0.0f,0.0f),
                             Vector3(0.0f,1.0f,0.0f));
	projection = Matrix::CreatePerspectiveFieldOfView( 1.0f, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f );
 float box_scl = 1.0f;
 Vector3 box_pos(0,0.5,0);
 box_rot.x += 0.005f;
 box_rot.y += 0.005f;
 Matrix box_offse = Matrix::CreateTranslation(0,0,-0.5f);
 cb.LightCol = Vector4(1,1,1,1);
 cb.LightVec = Vector4(-1,-1,1,1);
 cb.LightVec.Normalize(cb.LightVec);
 //床
 world = Matrix::CreateScale(10.0f) * Matrix::CreateRotationX(XMConvertToRadians(90)) * Matrix::CreateTranslation(Vector3(0,0,0));
 cb.WorldViewProjection = world * view * projection;
 cb.NormalMtx = ( world.Invert() ).Transpose();
 g_pImmediateContext->UpdateSubresource(g_pConstantBuffer,0,NULL,&cb,0,0);
 // テクスチャ設定
 g_pImmediateContext->PSSetShaderResources(0,1,&g_pShaderResView);
 // ポリゴン描画
	g_pImmediateContext->Draw( 4, 0 );

 //上面
 world = box_offse * Matrix::CreateScale(box_scl) * Matrix::CreateRotationX(XMConvertToRadians(90)) * Matrix::CreateFromYawPitchRoll(box_rot.y,box_rot.x,box_rot.z) * Matrix::CreateTranslation(box_pos);
 cb.WorldViewProjection = world * view * projection;
 cb.NormalMtx = ( world.Invert() ).Transpose();
 g_pImmediateContext->UpdateSubresource(g_pConstantBuffer,0,NULL,&cb,0,0);
 // テクスチャ設定
 g_pImmediateContext->PSSetShaderResources(0,1,&g_pShaderResView);
 // ポリゴン描画
 g_pImmediateContext->Draw(4,0);

 //底面
 world = box_offse * Matrix::CreateScale(box_scl) * Matrix::CreateRotationX(XMConvertToRadians(-90)) * Matrix::CreateFromYawPitchRoll(box_rot.y,box_rot.x,box_rot.z) * Matrix::CreateTranslation(box_pos);
 cb.WorldViewProjection = world * view * projection;
 cb.NormalMtx = ( world.Invert() ).Transpose();
 g_pImmediateContext->UpdateSubresource(g_pConstantBuffer,0,NULL,&cb,0,0);
 // テクスチャ設定
 g_pImmediateContext->PSSetShaderResources(0,1,&g_pShaderResView);
 // ポリゴン描画
 g_pImmediateContext->Draw(4,0);

 //前面
 world = box_offse * Matrix::CreateScale(box_scl) * Matrix::CreateRotationX(XMConvertToRadians(0)) * Matrix::CreateFromYawPitchRoll(box_rot.y,box_rot.x,box_rot.z) * Matrix::CreateTranslation(box_pos);
 cb.WorldViewProjection = world * view * projection;
 cb.NormalMtx = ( world.Invert() ).Transpose();
 g_pImmediateContext->UpdateSubresource(g_pConstantBuffer,0,NULL,&cb,0,0);
 // テクスチャ設定
 g_pImmediateContext->PSSetShaderResources(0,1,&g_pShaderResView);
 // ポリゴン描画
 g_pImmediateContext->Draw(4,0);

 //前面
 world = box_offse * Matrix::CreateScale(box_scl) * Matrix::CreateRotationY(XMConvertToRadians(180)) * Matrix::CreateFromYawPitchRoll(box_rot.y,box_rot.x,box_rot.z) * Matrix::CreateTranslation(box_pos);
 cb.WorldViewProjection = world * view * projection;
 cb.NormalMtx = ( world.Invert() ).Transpose();
 g_pImmediateContext->UpdateSubresource(g_pConstantBuffer,0,NULL,&cb,0,0);
 // テクスチャ設定
 g_pImmediateContext->PSSetShaderResources(0,1,&g_pShaderResView);
 // ポリゴン描画
 g_pImmediateContext->Draw(4,0);

 //右面
 world = box_offse * Matrix::CreateScale(box_scl) * Matrix::CreateRotationY(XMConvertToRadians(90)) * Matrix::CreateFromYawPitchRoll(box_rot.y,box_rot.x,box_rot.z) * Matrix::CreateTranslation(box_pos);
 cb.WorldViewProjection = world * view * projection;
 cb.NormalMtx = ( world.Invert() ).Transpose();
 g_pImmediateContext->UpdateSubresource(g_pConstantBuffer,0,NULL,&cb,0,0);
 // テクスチャ設定
 g_pImmediateContext->PSSetShaderResources(0,1,&g_pShaderResView);
 // ポリゴン描画
 g_pImmediateContext->Draw(4,0);

 //左面
 world = box_offse * Matrix::CreateScale(box_scl) * Matrix::CreateRotationY(XMConvertToRadians(-90)) * Matrix::CreateFromYawPitchRoll(box_rot.y,box_rot.x,box_rot.z) * Matrix::CreateTranslation(box_pos);
 cb.WorldViewProjection = world * view * projection;
 cb.NormalMtx = ( world.Invert() ).Transpose();
 g_pImmediateContext->UpdateSubresource(g_pConstantBuffer,0,NULL,&cb,0,0);
 // テクスチャ設定
 g_pImmediateContext->PSSetShaderResources(0,1,&g_pShaderResView);
 // ポリゴン描画
 g_pImmediateContext->Draw(4,0);

}

