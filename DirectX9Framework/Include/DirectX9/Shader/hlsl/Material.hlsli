/// @file Material.hlsli
/// @brief マテリアル
/// @date 2015/05/10
/// @author syuki nishida

#ifndef SNLIB_MATERIAL_HLSLI_
#define SNLIB_MATERIAL_HLSLI_

float4 MaterialDiffuse;
float4 MaterialAmbient;

/// @fn GetMaterialAmbientColor
/// @brief マテリアルのアンビエント取得
/// @return マテリアルのアンビエント色
float4 GetMaterialAmbientColor() {
	return MaterialAmbient;
}

/// @fn GetMaterialDiffuseColor
/// @brief マテリアルのディフューズ色取得
/// @return マテリアルのディフューズ色
float4 GetMaterialDiffuseColor() {
	return MaterialDiffuse;
}

#endif // SNLIB_MATERIAL_HLSLI_

// EOF