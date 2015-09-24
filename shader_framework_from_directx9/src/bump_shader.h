/// @file bump_shader.h
/// @brief �o���v
/// @date 2015/09/17
/// @author syuki nishida
#pragma once

#include "shader_adapter_base.h"
#include <DirectX9Framework/src/TransformShaderInterface.h>
#include <DirectX9Framework/src/LightShaderInterface.h>
#include <DirectX9Framework/src/MaterialShaderInterface.h>

/// @class BumpShader
class BumpShader :
  public ShaderAdapterBase,
  public snlib::TransformShaderInterface,
  public snlib::LightShaderInterface,
  public snlib::MaterialShaderInterface {
public:
  /// @fn BumpShader
  /// @brief �R���X�g���N�^
  BumpShader(LPDIRECT3DDEVICE9 device) :
    ShaderAdapterBase(
    device,
    "res/shader/specular_vs.cso",
    "res/shader/bump_ps.cso"),
    snlib::TransformShaderInterface(vertex_shader_->GetConstantTable()),
    snlib::LightShaderInterface(vertex_shader_->GetConstantTable()),
    snlib::MaterialShaderInterface(vertex_shader_->GetConstantTable()) {}

  /// @fn ~BumpShader
  /// @brief �f�X�g���N�^
  virtual ~BumpShader() {}

  /// @fn Apply
  /// @brief �萔�e�[�u���֓K��
  void Apply(LPDIRECT3DDEVICE9 device) {
    snlib::TransformShaderInterface::Apply(device);
    snlib::LightShaderInterface::Apply(device);
    snlib::MaterialShaderInterface::Apply(device);
  }

protected:
private:
};

//EOF