/// @file RenderStateManager.cpp
/// @brief レンダーステートマネージャ
/// @date 2015/06/26
/// @author syuki nishida

#include "RenderStateManager.h"

/// @namespace snlib
namespace snlib {

/// @fn RenderStateManager
/// @brief デフォルトコンストラクタ
RenderStateManager::RenderStateManager(LPDIRECT3DDEVICE9 device)
 : device_(device) {
}

/// @fn SetParameterToContainer
/// @brief パラメータ設定
/// @param[in] name パラメータセット識別子
/// @param[in] parameter パラメータ
void RenderStateManager::SetParameterToContainer(const char* name,
	const ParameterSet& parameter) {
	parameter_set_container_[name].push_back(parameter);
}

/// @fn DeleteParameterToContainer
/// @brief パラメータの削除
/// @param[in] name パラメータセット識別子
/// @param[in] parameter 消したいパラメータ
/// @return 消せた：true
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
/// @パラメータ即時適応
/// @parameter[in] parameter パラメータ
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
/// @brief パラメータ適応
/// @param[in] name 適応するパラメータセット識別子
void RenderStateManager::ApplyParameters(const char* name) {
	if (!parameter_set_container_.count(name)) return;
	for (auto it : parameter_set_container_[name]) {
		SetParameter(it);
	}
}

} // namespace snlib

//EOF