//=============================================================================
//
// ƒ‰ƒCƒgŠÇ—ˆ— [LightManager.cpp]
// Author : Naritada Suzuki
//
//=============================================================================
#include <Util/SafeDelete.h>
#include "LightManager.h"

snlib::LightManager::LightManager(LPD3DXCONSTANTTABLE constant_table)
{
 for(int i = 0; i < kLightMax;++i)
 {
  _lightshader[i] = new LightShaderInterface(constant_table);
 }
}

snlib::LightManager::~LightManager()
{
 for(int i = 0; i < kLightMax;++i)
 {
  snlib::SafeDelete(_lightshader[i]);
 }
}
