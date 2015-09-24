#pragma once

#include <Windows.h>
#include "renderer.h"
#include "perth_matrix.h"
#include "view_matrix.h"
#include "vertex_shader.h"
#include "pixel_shader.h"
#include "plane.h"
#include "xmodel.h"

class Application {
public:
	/// @brief �R���X�g���N�^
	Application();

	/// @brief �f�X�g���N�^
	virtual ~Application();

	/// @brief ������
	void Initialize(HWND window_handle);

	/// @brief �I��
	void Finalize();

	/// @brief �X�V
	void Update();

	/// @brief �`��
	void Draw();

protected:
private:
	bool is_initialize_;
	Renderer* renderer_;

	HWND window_handle_;

	VertexShader* vs_;
	PixelShader* ps_;

	PerthMatrix perth_;
	ViewMatrix view_;

	Plane* plane_;
	XModel* model_;
};