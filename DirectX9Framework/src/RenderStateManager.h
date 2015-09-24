/// @file RenderStateManager.h
/// @brief レンダーステートマネージャ
/// @date 2015/06/26
/// @author syuki nishida
#pragma once
#ifndef SNLIB_RENDER_STATE_MANAGER_H_
#define SNLIB_RENDER_STATE_MANAGER_H_

#include <d3d9.h>
#include <map>
#include <vector>

/// @namespace snlib
namespace snlib {

/// @class RenderStateManager
class RenderStateManager {
public:
	/// @enum StageType
	/// @brief ステートのタイプ
	enum StateType{
		RENDER_STAGE,
		SAMPLER_STATE,
		TEXTURE_STAGE_STATE,
	};

	/// @union ParameterType
	/// @brief 各タイプを一つの変数で扱う為
	union ParameterType{
		D3DRENDERSTATETYPE render_;
		D3DSAMPLERSTATETYPE sampler_;
		D3DTEXTURESTAGESTATETYPE texturestage_;

		ParameterType() : render_(D3DRS_ZENABLE){}
		ParameterType(D3DRENDERSTATETYPE render) : render_(render){}
		ParameterType(D3DSAMPLERSTATETYPE sampler) : sampler_(sampler){}
		ParameterType(D3DTEXTURESTAGESTATETYPE arg) : texturestage_(arg){}

		bool operator==(const ParameterType& arg) {
			return
				render_ != arg.render_ ? false :
				sampler_ != arg.sampler_ ? false :
				texturestage_ != arg.texturestage_ ? false :
				true;
		}

		bool operator!=(const ParameterType& arg) {
			return !operator==(arg);
		}
	};

	/// @struct ParameterSet
	/// @brief 設定を一つの変数に
	struct ParameterSet {
		StateType state_type_;
		DWORD index_;
		ParameterType parameter_type_;
		DWORD value_;

		bool operator==(const ParameterSet& arg) {
			return
				state_type_ != arg.state_type_ ? false :
				index_ != arg.index_ ? false :
				parameter_type_ != arg.parameter_type_ ? false :
				value_ != arg.value_ ? false :
				true;
		}

		bool operator!=(const ParameterSet& arg) {
			return !operator==(arg);
		}
	};

	/// @fn RenderStateManager
	/// @brief デフォルトコンストラクタ
	RenderStateManager(LPDIRECT3DDEVICE9 device);

	/// @fn SetParameter
	/// @brief パラメータ設定
	/// @param[in] name パラメータセット識別子
	/// @param[in] parameter パラメータ
	void SetParameterToContainer(const char* name, const ParameterSet& parameter);

	/// @fn DeleteParameter
	/// @brief パラメータの削除
	/// @param[in] name パラメータセット識別子
	/// @param[in] parameter 消したいパラメータ
	/// @return 消せた：true
	bool DeleteParameterToContainer(const char* name, const ParameterSet& parameter);

	/// @fn SetParameter
	/// @パラメータ即時適応
	/// @parameter[in] parameter パラメータ
	void SetParameter(const ParameterSet& parameter);

	/// @fn ApplyParameters
	/// @brief パラメータ適応
	/// @param[in] name 適応するパラメータセット識別子
	void ApplyParameters(const char* name);

private:
	LPDIRECT3DDEVICE9 device_;

	std::map<std::string, std::vector<ParameterSet>> parameter_set_container_;

protected:
};

} // namespace snlib

#endif // SNLIB_RENDER_STATE_MANAGER_H_

//EOF