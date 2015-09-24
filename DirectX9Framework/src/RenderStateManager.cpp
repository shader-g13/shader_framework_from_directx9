/// @file RenderStateManager.cpp
/// @brief �����_�[�X�e�[�g�}�l�[�W��
/// @date 2015/06/26
/// @author syuki nishida

#include "RenderStateManager.h"

/// @namespace snlib
namespace snlib {

/// @fn RenderStateManager
/// @brief �f�t�H���g�R���X�g���N�^
RenderStateManager::RenderStateManager(LPDIRECT3DDEVICE9 device)
 : device_(device) {
}

/// @fn SetParameterToContainer
/// @brief �p�����[�^�ݒ�
/// @param[in] name �p�����[�^�Z�b�g���ʎq
/// @param[in] parameter �p�����[�^
void RenderStateManager::SetParameterToContainer(const char* name,
	const ParameterSet& parameter) {
	parameter_set_container_[name].push_back(parameter);
}

/// @fn DeleteParameterToContainer
/// @brief �p�����[�^�̍폜
/// @param[in] name �p�����[�^�Z�b�g���ʎq
/// @param[in] parameter ���������p�����[�^
/// @return �������Ftrue
bool RenderStateManager::DeleteParameterToContainer(const char* name,
	const ParameterSet& parameter) {
	if (!parameter_set_container_.count(name)) return false;
	std::vector<ParameterSet>* param_array = &parameter_set_container_[name];

	for (auto it = param_array->begin(); it != param_array->end(); it++) {
		if ((*it) == parameter) {
			param_array->erase(it);
			return true;
		}
	}
	return false;
}

/// @fn SetParameter
/// @�p�����[�^�����K��
/// @parameter[in] parameter �p�����[�^
void RenderStateManager::SetParameter(const ParameterSet& arg) {
	if (arg.state_type_ == RENDER_STAGE) {
		device_->SetRenderState(arg.parameter_type_.render_, arg.value_);
	}
	else if (arg.state_type_ == SAMPLER_STATE) {
		device_->SetSamplerState(arg.index_, arg.parameter_type_.sampler_, arg.value_);
	}
	else if (arg.state_type_ == TEXTURE_STAGE_STATE) {
		device_->SetTextureStageState(arg.index_, arg.parameter_type_.texturestage_,
			arg.value_);
	}
}

/// @fn ApplyParameters
/// @brief �p�����[�^�K��
/// @param[in] name �K������p�����[�^�Z�b�g���ʎq
void RenderStateManager::ApplyParameters(const char* name) {
	if (!parameter_set_container_.count(name)) return;
	for (auto it : parameter_set_container_[name]) {
		SetParameter(it);
	}
}

} // namespace snlib

//EOF