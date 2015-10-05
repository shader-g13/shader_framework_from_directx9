#pragma once

#include <d3d9.h>
#include "perth_matrix.h"
#include "view_matrix.h"
#include "vertex_shader.h"
#include "pixel_shader.h"
#include "plane.h"
#include "xmodel.h"

class TestScene {
public:
  /// @brief コンストラクタ
  TestScene();

  /// @brief デストラクタ
  virtual ~TestScene();

  /// @brief 初期化
  void Initialize(LPDIRECT3DDEVICE9 device);

  /// @brief 終了
  void Finalize();

  /// @brief 更新
  void Update();

  /// @brief 描画
  void Draw(LPDIRECT3DDEVICE9 device);

protected:
private:
  VertexShader* vs_;
  PixelShader* ps_;

  PerthMatrix perth_;
  ViewMatrix view_;

  Plane* plane_;
  XModel* model_;
  LPDIRECT3DTEXTURE9 texBase_;
  LPDIRECT3DTEXTURE9 texBmp_;
  D3DXVECTOR3 rot_;
};