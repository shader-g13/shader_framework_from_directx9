/// @file Material.hlsli
/// @brief �}�e���A��
/// @date 2015/05/10
/// @author syuki nishida

#ifndef SNLIB_MATERIAL_HLSLI_
#define SNLIB_MATERIAL_HLSLI_

float4 MaterialDiffuse;
float4 MaterialAmbient;

/// @fn GetMaterialAmbientColor
/// @brief �}�e���A���̃A���r�G���g�擾
/// @return �}�e���A���̃A���r�G���g�F
float4 GetMaterialAmbientColor() {
	return MaterialAmbient;
}

/// @fn GetMaterialDiffuseColor
/// @brief �}�e���A���̃f�B�t���[�Y�F�擾
/// @return �}�e���A���̃f�B�t���[�Y�F
float4 GetMaterialDiffuseColor() {
	return MaterialDiffuse;
}

#endif // SNLIB_MATERIAL_HLSLI_

// EOF