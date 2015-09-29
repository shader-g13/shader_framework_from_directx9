/// @file Light.hlsli
/// @brief ���C�g
/// @date 2015/05/10
/// @author syuki nishida

#ifndef SNLIB_LIGHT_HLSLI_
#define SNLIB_LIGHT_HLSLI_

float4 LightDirection;
float4 LightDiffuse;
float4 LightAmbient;

/// @struct Light
struct Light {
	float3 direction_;
	float3 diffuse_;
	float3 ambient_;
};

/// @fn GetLight
/// @brief ���C�g�擾
/// @return ���C�g
Light GetLight() {
	Light ret;
	ret.direction_ = LightDirection.xyz;
	ret.diffuse_ = LightDiffuse.xyz;
	ret.ambient_ = LightAmbient.xyz;

	return ret;
}

/// @fn DirectionalLighting
/// @brief ���s�������C�e�B���O
/// @return ���s�����F
/// @param[in] direction ���C�g�̌���
/// @param[in] normal �@��
float3 DirectionalLighting(float3 direction, float3 normal) {
	return max(dot(normal, -direction), 0);
}

/// @fn HalfLambertLighting
/// @brief �n�[�t�����o�[�g���C�e�B���O�F�擾
/// @param[in] direction ���C�g�̌���
/// @param[in] normal �@��
float3 HalfLambertLighting(float3 direction, float3 normal) {
	return dot(normal, -direction) * 0.5f + 0.5f;
}

/// @fn MuraseLimLighting
/// @brief �����Z�������C�e�B���O
/// @param[in] direction ���C�g�̌���
/// @param[in] normal �@��
float3 MuraseLimLighting(float3 direction, float3 normal) {
	return 1.f - abs(dot(direction, normal)) * 1.2;
}

#endif // SNLIB_LIGHT_HLSLI_

//EOF