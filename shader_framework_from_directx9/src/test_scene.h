#pragma once

#include <d3d9.h>
#include <DirectX9/Matrix/PerthMatrixInterface.h>
#include <DirectX9/Matrix/ViewMatrixInterface.h>
#include <DirectX9/Shader/VertexShader.h>
#include <DirectX9/Shader/PixelShader.h>
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
  snlib::VertexShader* vs_;
  snlib::PixelShader* ps_;

  snlib::PerthMatrixInterface perth_;
  snlib::ViewMatrixInterface view_;

  XModel* model_;
};