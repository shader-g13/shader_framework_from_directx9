/// @file LightManager.h
/// @brief 複数のライトシェーダのインターフェース
/// @date 2015/09/24
/// @author naritada suzuki

#pragma once
#ifndef SNLIB_LIGHT_MANAGER_H_
#define SNLIB_LIGHT_MANAGER_H_

#include "LightShaderInterface.h"
namespace snlib
{

 class LightManager
 {
  public:
  LightManager(LPD3DXCONSTANTTABLE constant_table);
  ~LightManager();
  const snlib::LightShaderInterface* lightShader(short lightNum){ return _lightshader[lightNum]; }

  private:
  static const short kLightMax = 3;
  snlib::LightShaderInterface* _lightshader[kLightMax];
 };
}
#endif