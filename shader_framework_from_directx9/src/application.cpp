
#include "application.h"

/// @brief �R���X�g���N�^
Application::Application() :
is_initialize_(false),
renderer_(nullptr),
plane_(nullptr),
model_(nullptr) {
}

/// @brief �f�X�g���N�^
Application::~Application() {
}

/// @brief ������
void Application::Initialize(HWND window_handle) {
	if (is_initialize_) return;
	is_initialize_ = true;

	window_handle_ = window_handle;

	// �����_���[������
	renderer_ = new Renderer();
	renderer_->Initialize(window_handle_, 800, 600);

	LPDIRECT3DDEVICE9 device = renderer_->GetDevice();

	plane_ = new Plane();
	plane_->Initialize(device);

	model_ = new XModel();
	model_->Initialize(device, "res/kuma.x");

	vs_ = new VertexShader(device, "res/shader/test_vs.cso");
	ps_ = new PixelShader(device, "res/shader/test_ps.cso");
}

/// @brief �I��
void Application::Finalize() {
	if (!is_initialize_) return;
	is_initialize_ = false;

	delete vs_;
	delete ps_;

	model_->Finalize();
	delete model_;

	plane_->Finalize();
	delete plane_;

	// �����_���[�I��
	renderer_->Finalize();
	delete renderer_;
	renderer_ = nullptr;
}

/// @brief �X�V
void Application::Update() {
}

/// @brief �`��
void Application::Draw() {
	renderer_->BegenDraw();

	LPDIRECT3DDEVICE9 device = renderer_->GetDevice();

	D3DXMATRIX world;
	D3DXMatrixScaling(&world, 1, 1, 1);
	device->SetTransform(D3DTS_PROJECTION, &perth_.CreatePerthMatrix());
	device->SetTransform(D3DTS_VIEW, &view_.CreateViewMatrix());
	device->SetTransform(D3DTS_WORLD, &world);

	LPD3DXCONSTANTTABLE vs_const = vs_->GetConstantTable();
	vs_const->SetMatrix(device, "ProjectionMatrix", &perth_.CreatePerthMatrix());
	vs_const->SetMatrix(device, "ViewMatrix", &view_.CreateViewMatrix());
	vs_const->SetMatrix(device, "WorldMatrix", &world);

	vs_->SetVertexShader(device);
	ps_->SetPixelShader(device);

	plane_->Draw(device);

	model_->Draw(device);

	renderer_->EndDraw();
}
