/// @file Transform.hlsli
/// @brief 行列変換
/// @date 2015/05/10
/// @author syuki nishida

#ifndef SNLIB_TRANSFORM_HLSLI_
#define SNLIB_TRANSFORM_HLSLI_

/// @brief 定数
float4x4 WorldMatrix;
float4x4 ViewMatrix;
float4x4 ProjectionMatrix;

/// @fn Transform
/// @brief 行列変換
/// @param[in] pos 変換する頂点
/// @return 変換後の頂点
float4 Transform(float3 pos) {
	return mul(float4(pos, 1), mul(mul(WorldMatrix, ViewMatrix), ProjectionMatrix));
}

/// @fn GetWorldMatrix
/// @brief ワールド行列取得
/// @return ワールド行列
float4x4 GetWorldMatrix() {
	return WorldMatrix;
}

/// @fn GetViewMatrix
/// @brief ビュー行列取得
/// @return ビュー行列
float4x4 GetViewMatrix() {
	return ViewMatrix;
}

/// @fn GetProjectionMatrix
/// @brief プロジェクション行列取得
/// @return プロジェクション行列
float4x4 GetProjectionMatrix() {
	return ProjectionMatrix;
}

#endif // SNLIB_TRANSFORM_HLSLI_

//EOF