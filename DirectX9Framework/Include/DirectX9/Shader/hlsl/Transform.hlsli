/// @file Transform.hlsli
/// @brief �s��ϊ�
/// @date 2015/05/10
/// @author syuki nishida

#ifndef SNLIB_TRANSFORM_HLSLI_
#define SNLIB_TRANSFORM_HLSLI_

/// @brief �萔
float4x4 WorldMatrix;
float4x4 ViewMatrix;
float4x4 ProjectionMatrix;

/// @fn Transform
/// @brief �s��ϊ�
/// @param[in] pos �ϊ����钸�_
/// @return �ϊ���̒��_
float4 Transform(float3 pos) {
	return mul(float4(pos, 1), mul(mul(WorldMatrix, ViewMatrix), ProjectionMatrix));
}

/// @fn GetWorldMatrix
/// @brief ���[���h�s��擾
/// @return ���[���h�s��
float4x4 GetWorldMatrix() {
	return WorldMatrix;
}

/// @fn GetViewMatrix
/// @brief �r���[�s��擾
/// @return �r���[�s��
float4x4 GetViewMatrix() {
	return ViewMatrix;
}

/// @fn GetProjectionMatrix
/// @brief �v���W�F�N�V�����s��擾
/// @return �v���W�F�N�V�����s��
float4x4 GetProjectionMatrix() {
	return ProjectionMatrix;
}

#endif // SNLIB_TRANSFORM_HLSLI_

//EOF