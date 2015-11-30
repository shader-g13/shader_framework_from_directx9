#pragma once

#include <d3d9.h>
#include "perth_matrix.h"
#include "view_matrix.h"
#include "vertex_shader.h"
#include "pixel_shader.h"
#include "plane.h"
#include "xmodel.h"
#include <Surface.h>
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
  VertexShader* vs_;
  PixelShader* ps_;

  PerthMatrix perth_;
  ViewMatrix view_;

  Plane* plane_;
  XModel* model_;
  XModel* skyBox_;
  LPDIRECT3DTEXTURE9 texBase_;
  LPDIRECT3DTEXTURE9 texBmp_;
  D3DXVECTOR3 rot_;
  LPDIRECT3DCUBETEXTURE9 texCube_;
  snlib::Surface* _surface;
};