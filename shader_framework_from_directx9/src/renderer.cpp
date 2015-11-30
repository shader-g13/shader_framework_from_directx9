
#include "renderer.h"
#include <crtdbg.h>

#pragma comment (lib,"d3d9.lib")
#pragma comment (lib,"d3dx9.lib")

/// @brief �R���X�g���N�^
Renderer::Renderer() :
device_(nullptr) {
}

/// @brief �f�X�g���N�^
Renderer::~Renderer() {
}

/// @brief ������
void Renderer::Initialize(HWND window_handle, UINT buffer_width, UINT buffer_heignt, bool windable) {
	if (device_) return;

	window_handle_ = window_handle;
	buffer_width_ = buffer_width;
	buffer_height_ = buffer_heignt;
	windable_ = windable;

	HRESULT ret;

	direct3d_ = Direct3DCreate9(D3D_SDK_VERSION);
	_ASSERT_EXPR(direct3d_, L"Direct3D���񂩂���");

	D3DDISPLAYMODE display_mode;
	ret = direct3d_->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &display_mode);
	_ASSERT_EXPR(SUCCEEDED(ret), L"�f�B�X�v���C���[�h�Ƃ��");

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	D3DPRESENT_PARAMETERS present_param = {0};
	present_param.BackBufferCount  = 1;						// �o�b�N�o�b�t�@�̐�
	present_param.BackBufferWidth  = buffer_width_;			// �Q�[����ʃT�C�Y(��)
	present_param.BackBufferHeight = buffer_height_;		// �Q�[����ʃT�C�Y(����)
	present_param.BackBufferFormat = D3DFMT_UNKNOWN;		// �o�b�N�o�b�t�@�̃t�H�[�}�b�g�͌��ݐݒ肳��Ă�����̂��g��
	present_param.SwapEffect       = D3DSWAPEFFECT_DISCARD;	// �f���M���ɓ������ăt���b�v����
	present_param.Windowed         = windable_;				// �E�B���h�E���[�h
	present_param.EnableAutoDepthStencil = true;			// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
 present_param.AutoDepthStencilFormat = D3DFMT_D24S8;		// D3DFMT_D24S8 �f�v�X�o�b�t�@�Ƃ���16bit���g��

	if (windable_) {// �E�B���h�E���[�h
		present_param.BackBufferFormat = D3DFMT_UNKNOWN;					// �o�b�N�o�b�t�@
		present_param.FullScreen_RefreshRateInHz = 0;						// ���t���b�V�����[�g
		present_param.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	// �C���^�[�o��
	}
	else {// �t���X�N���[�����[�h
		present_param.BackBufferFormat = D3DFMT_R5G6B5;						// �o�b�N�o�b�t�@
		present_param.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// ���t���b�V�����[�g
		present_param.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// �C���^�[�o��
	}

	// �f�o�C�X�쐬
	ret = direct3d_->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
		window_handle_, D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&present_param, &device_);
	_ASSERT_EXPR(SUCCEEDED(ret), L"�f�o�C�X���Ȃ�");

	//�����_�[�X�e�[�g�p�����[�^�̏���
	device_->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	device_->SetRenderState(D3DRS_ZENABLE, TRUE);
	device_->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	device_->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	device_->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//device_->SetRenderState(D3DRS_FILLMODE,D3DFILL_WIREFRAME);
	device_->SetRenderState(D3DRS_LIGHTING, false);

	// �T���v���[�X�e�[�g�p�����[�^�̐ݒ�
	device_->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(U�l)��ݒ�
	device_->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(V�l)��ݒ�
	device_->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���k���t�B���^���[�h��ݒ�
	device_->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���g��t�B���^���[�h��ݒ�

	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	device_->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// �A���t�@�u�����f�B���O������ݒ�
	device_->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// �ŏ��̃A���t�@����
	device_->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// �Q�Ԗڂ̃A���t�@����
}

/// @biref �I��
void Renderer::Finalize() {
	if (!device_) return;

	ULONG ref_count;
	ref_count = device_->Release();
	_ASSERT_EXPR(!ref_count, L"�J���Y�ꂠ���");
	device_ = nullptr;

	ref_count = direct3d_->Release();
	_ASSERT_EXPR(!ref_count, L"�J���Y�ꂠ���");
	direct3d_ = nullptr;
}

/// @brief �`��J�n
void Renderer::BegenDraw() {
	device_->Clear(0, nullptr,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0),
		1.0f, 0);

	device_->BeginScene();
}

/// @brief �`��I��
void Renderer::EndDraw() {
	device_->EndScene();
	device_->Present(NULL, NULL, NULL, NULL);
}
