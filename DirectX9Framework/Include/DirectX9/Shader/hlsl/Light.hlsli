/// @file Light.hlsli
/// @brief ライト
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
/// @brief ライト取得
/// @return ライト
Light GetLight() {
	Light ret;
	ret.direction_ = LightDirection.xyz;
	ret.diffuse_ = LightDiffuse.xyz;
	ret.ambient_ = LightAmbient.xyz;

	return ret;
}

/// @fn DirectionalLighting
/// @brief 平行光源ライティング
/// @return 平行光源色
/// @param[in] direction ライトの向き
/// @param[in] normal 法線
float3 DirectionalLighting(float3 direction, float3 normal) {
	return max(dot(normal, -direction), 0);
}

/// @fn HalfLambertLighting
/// @brief ハーフランバートライティング色取得
/// @param[in] direction ライトの向き
/// @param[in] normal 法線
float3 HalfLambertLighting(float3 direction, float3 normal) {
	return dot(normal, -direction) * 0.5f + 0.5f;
}

/// @fn MuraseLimLighting
/// @brief ムラセリムライティング
/// @param[in] direction ライトの向き
/// @param[in] normal 法線
float3 MuraseLimLighting(float3 direction, float3 normal) {
	return 1.f - abs(dot(direction, normal)) * 1.2;
}

#endif // SNLIB_LIGHT_HLSLI_

//EOF