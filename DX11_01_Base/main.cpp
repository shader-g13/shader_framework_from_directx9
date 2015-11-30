#include "main.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CLASS_NAME		"AppClass"				// �E�C���h�E�̃N���X��
#define WINDOW_NAME		"DX11�|���S���`��"	// �E�C���h�E�̃L���v�V������


//*****************************************************************************
// �v���g�^�C�v�錾
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
// �O���[�o���ϐ�:
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
// ���C���֐�
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

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �E�B���h�E�̍쐬
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

	// ����������(�E�B���h�E���쐬���Ă���s��)
	if(FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}

	// �E�C���h�E�̕\��(�����������̌�ɍs��)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// ���b�Z�[�W���[�v
	while(1)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{// Windows�̏���
			if(msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��Ƒ��o
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{// DirectX�̏���
			// �X�V����
			Update();

			// �`�揈��
			Draw();
		}
	}

	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// �I������
	Uninit();

	return (int)msg.wParam;
}


//=============================================================================
// �E�C���h�E�v���V�[�W��
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
// ����������
// hInstance : �C���X�^���X�̃n���h��
// hWnd      : �E�C���h�E�̃n���h��
// bWindow   : �E�C���h�E���[�h�ɂ��邩�ǂ���
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	HRESULT hr = S_OK;

	// �f�o�C�X�A�X���b�v�`�F�[���A�R���e�L�X�g����
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


	// �����_�[�^�[�Q�b�g�r���[�����A�ݒ�
	ID3D11Texture2D* pBackBuffer = NULL;
	g_pSwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&pBackBuffer );
	g_pD3DDevice->CreateRenderTargetView( pBackBuffer, NULL, &g_pRenderTargetView );
	pBackBuffer->Release();
	g_pImmediateContext->OMSetRenderTargets( 1, &g_pRenderTargetView, NULL );


	// �r���[�|�[�g�ݒ�
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)SCREEN_WIDTH;
	vp.Height = (FLOAT)SCREEN_HEIGHT;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	g_pImmediateContext->RSSetViewports( 1, &vp );

	// ���_�V�F�[�_�R���p�C���E����
	ID3DBlob* pErrorBlob;
	ID3DBlob* pVSBlob = NULL;
	hr = D3DCompileFromFile( L"shader.hlsl", NULL, NULL, "VertexShaderPolygon", "vs_4_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, &pVSBlob, &pErrorBlob);
	if( FAILED(hr) )
	{
		MessageBox( NULL , (char*)pErrorBlob->GetBufferPointer(), "VS", MB_OK | MB_ICONERROR );
	}

	g_pD3DDevice->CreateVertexShader( pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, &g_pVertexShader );

	// ���̓��C�A�E�g����
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


	// �s�N�Z���V�F�[�_�R���p�C���E����
	ID3DBlob* pPSBlob = NULL;
 hr = D3DCompileFromFile(L"shader.hlsl",NULL,NULL,"PixelShaderPolygon","ps_4_0",D3DCOMPILE_ENABLE_STRICTNESS,0,&pPSBlob,&pErrorBlob);
	if( FAILED(hr) )
	{
		MessageBox( NULL , (char*)pErrorBlob->GetBufferPointer(), "PS", MB_OK | MB_ICONERROR );
	}

	g_pD3DDevice->CreatePixelShader( pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, &g_pPixelShader );
	
	pPSBlob->Release();

	// �萔�o�b�t�@����
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


	// �|���S���̏���������
	InitPolygon();


	return S_OK;
}


//=============================================================================
// �I������
//=============================================================================
void Uninit(void)
{
	// �|���S���I������
	UninitPolygon();

	// �I�u�W�F�N�g���
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
// �X�V����
//=============================================================================
void Update(void)
{
	// �|���S���X�V
	UpdatePolygon();
}


//=============================================================================
// �`�揈��
//=============================================================================
void Draw(void)
{
	// �o�b�N�o�b�t�@�N���A
	float ClearColor[4] = { 0.0f, 0.5f, 0.0f, 1.0f };
	g_pImmediateContext->ClearRenderTargetView( g_pRenderTargetView, ClearColor );

	// �|���S���`��
	DrawPolygon();

	// �o�b�N�o�b�t�@�A�t�����g�o�b�t�@����ւ�
	g_pSwapChain->Present( 0, 0 );
}


//=============================================================================
// ����������
//=============================================================================
void InitPolygon(void)
{
	HRESULT hr = S_OK;


	// ���_�o�b�t�@����
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
	// �e�N�X�`������
 hr = LoadFromDDSFile(L"data/field004.dds",
                 0,
                 &meta,
                 image);
 
 _ASSERT_EXPR(SUCCEEDED(hr),L"LoadFromWICFile���s");

 hr = CreateShaderResourceView(g_pD3DDevice,image.GetImages(),image.GetImageCount(),image.GetMetadata(),&g_pShaderResView);
 _ASSERT_EXPR(SUCCEEDED(hr),L"CreateShaderResourceView���s");

}


//=============================================================================
// �I������
//=============================================================================
void UninitPolygon(void)
{
	if( g_pVertexBuffer )	g_pVertexBuffer->Release();
	if( g_pShaderResView )	g_pShaderResView->Release();
}


//=============================================================================
// �X�V����
//=============================================================================
void UpdatePolygon(void)
{

}


//=============================================================================
// �`�揈��
//=============================================================================
void DrawPolygon(void)
{
	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof( Vertex3D );
	UINT offset = 0;
	g_pImmediateContext->IASetVertexBuffers( 0, 1, &g_pVertexBuffer, &stride, &offset );

	// �v���~�e�B�u�^�C�v�ݒ�
	g_pImmediateContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP );

	// ���̓��C�A�E�g�ݒ�
	g_pImmediateContext->IASetInputLayout( g_pVertexLayout );

	// �V�F�[�_�ݒ�
	g_pImmediateContext->VSSetShader( g_pVertexShader, NULL, 0 );
	g_pImmediateContext->PSSetShader( g_pPixelShader, NULL, 0 );



	// �}�g���N�X�ݒ�
	Matrix world, view, projection,camera_rot;
 //������
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
 //��
 world = Matrix::CreateScale(10.0f) * Matrix::CreateRotationX(XMConvertToRadians(90)) * Matrix::CreateTranslation(Vector3(0,0,0));
 cb.WorldViewProjection = world * view * projection;
 cb.NormalMtx = ( world.Invert() ).Transpose();
 g_pImmediateContext->UpdateSubresource(g_pConstantBuffer,0,NULL,&cb,0,0);
 // �e�N�X�`���ݒ�
 g_pImmediateContext->PSSetShaderResources(0,1,&g_pShaderResView);
 // �|���S���`��
	g_pImmediateContext->Draw( 4, 0 );

 //���
 world = box_offse * Matrix::CreateScale(box_scl) * Matrix::CreateRotationX(XMConvertToRadians(90)) * Matrix::CreateFromYawPitchRoll(box_rot.y,box_rot.x,box_rot.z) * Matrix::CreateTranslation(box_pos);
 cb.WorldViewProjection = world * view * projection;
 cb.NormalMtx = ( world.Invert() ).Transpose();
 g_pImmediateContext->UpdateSubresource(g_pConstantBuffer,0,NULL,&cb,0,0);
 // �e�N�X�`���ݒ�
 g_pImmediateContext->PSSetShaderResources(0,1,&g_pShaderResView);
 // �|���S���`��
 g_pImmediateContext->Draw(4,0);

 //���
 world = box_offse * Matrix::CreateScale(box_scl) * Matrix::CreateRotationX(XMConvertToRadians(-90)) * Matrix::CreateFromYawPitchRoll(box_rot.y,box_rot.x,box_rot.z) * Matrix::CreateTranslation(box_pos);
 cb.WorldViewProjection = world * view * projection;
 cb.NormalMtx = ( world.Invert() ).Transpose();
 g_pImmediateContext->UpdateSubresource(g_pConstantBuffer,0,NULL,&cb,0,0);
 // �e�N�X�`���ݒ�
 g_pImmediateContext->PSSetShaderResources(0,1,&g_pShaderResView);
 // �|���S���`��
 g_pImmediateContext->Draw(4,0);

 //�O��
 world = box_offse * Matrix::CreateScale(box_scl) * Matrix::CreateRotationX(XMConvertToRadians(0)) * Matrix::CreateFromYawPitchRoll(box_rot.y,box_rot.x,box_rot.z) * Matrix::CreateTranslation(box_pos);
 cb.WorldViewProjection = world * view * projection;
 cb.NormalMtx = ( world.Invert() ).Transpose();
 g_pImmediateContext->UpdateSubresource(g_pConstantBuffer,0,NULL,&cb,0,0);
 // �e�N�X�`���ݒ�
 g_pImmediateContext->PSSetShaderResources(0,1,&g_pShaderResView);
 // �|���S���`��
 g_pImmediateContext->Draw(4,0);

 //�O��
 world = box_offse * Matrix::CreateScale(box_scl) * Matrix::CreateRotationY(XMConvertToRadians(180)) * Matrix::CreateFromYawPitchRoll(box_rot.y,box_rot.x,box_rot.z) * Matrix::CreateTranslation(box_pos);
 cb.WorldViewProjection = world * view * projection;
 cb.NormalMtx = ( world.Invert() ).Transpose();
 g_pImmediateContext->UpdateSubresource(g_pConstantBuffer,0,NULL,&cb,0,0);
 // �e�N�X�`���ݒ�
 g_pImmediateContext->PSSetShaderResources(0,1,&g_pShaderResView);
 // �|���S���`��
 g_pImmediateContext->Draw(4,0);

 //�E��
 world = box_offse * Matrix::CreateScale(box_scl) * Matrix::CreateRotationY(XMConvertToRadians(90)) * Matrix::CreateFromYawPitchRoll(box_rot.y,box_rot.x,box_rot.z) * Matrix::CreateTranslation(box_pos);
 cb.WorldViewProjection = world * view * projection;
 cb.NormalMtx = ( world.Invert() ).Transpose();
 g_pImmediateContext->UpdateSubresource(g_pConstantBuffer,0,NULL,&cb,0,0);
 // �e�N�X�`���ݒ�
 g_pImmediateContext->PSSetShaderResources(0,1,&g_pShaderResView);
 // �|���S���`��
 g_pImmediateContext->Draw(4,0);

 //����
 world = box_offse * Matrix::CreateScale(box_scl) * Matrix::CreateRotationY(XMConvertToRadians(-90)) * Matrix::CreateFromYawPitchRoll(box_rot.y,box_rot.x,box_rot.z) * Matrix::CreateTranslation(box_pos);
 cb.WorldViewProjection = world * view * projection;
 cb.NormalMtx = ( world.Invert() ).Transpose();
 g_pImmediateContext->UpdateSubresource(g_pConstantBuffer,0,NULL,&cb,0,0);
 // �e�N�X�`���ݒ�
 g_pImmediateContext->PSSetShaderResources(0,1,&g_pShaderResView);
 // �|���S���`��
 g_pImmediateContext->Draw(4,0);

}

