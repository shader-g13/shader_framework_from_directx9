#pragma once

#include <d3d9.h>
#include <DirectX9/Matrix/PerthMatrixInterface.h>
#include <DirectX9/Matrix/ViewMatrixInterface.h>
#include <DirectX9/Shader/VertexShader.h>
#include <DirectX9/Shader/PixelShader.h>
#include "xmodel.h"

class TestScene {
public:
  /// @brief �R���X�g���N�^
  TestScene();

  /// @brief �f�X�g���N�^
  virtual ~TestScene();

  /// @brief ������
  void Initialize(LPDIRECT3DDEVICE9 device);

  /// @brief �I��
  void Finalize();

  /// @brief �X�V
  void Update();

  /// @brief �`��
  void Draw(LPDIRECT3DDEVICE9 device);

protected:
private:
  snlib::VertexShader* vs_;
  snlib::PixelShader* ps_;

  snlib::PerthMatrixInterface perth_;
  snlib::ViewMatrixInterface view_;

  XModel* model_;
};