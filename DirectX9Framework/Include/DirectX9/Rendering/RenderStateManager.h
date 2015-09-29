/// @file RenderStateManager.h
/// @brief �����_�[�X�e�[�g�}�l�[�W��
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
	/// @brief �X�e�[�g�̃^�C�v
	enum StateType{
		RENDER_STAGE,
		SAMPLER_STATE,
		TEXTURE_STAGE_STATE,
	};

	/// @union ParameterType
	/// @brief �e�^�C�v����̕ϐ��ň�����
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
	/// @brief �ݒ����̕ϐ���
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
	/// @brief �f�t�H���g�R���X�g���N�^
	RenderStateManager(LPDIRECT3DDEVICE9 device);

	/// @fn SetParameter
	/// @brief �p�����[�^�ݒ�
	/// @param[in] name �p�����[�^�Z�b�g���ʎq
	/// @param[in] parameter �p�����[�^
	void SetParameterToContainer(const char* name, const ParameterSet& parameter);

	/// @fn DeleteParameter
	/// @brief �p�����[�^�̍폜
	/// @param[in] name �p�����[�^�Z�b�g���ʎq
	/// @param[in] parameter ���������p�����[�^
	/// @return �������Ftrue
	bool DeleteParameterToContainer(const char* name, const ParameterSet& parameter);

	/// @fn SetParameter
	/// @�p�����[�^�����K��
	/// @parameter[in] parameter �p�����[�^
	void SetParameter(const ParameterSet& parameter);

	/// @fn ApplyParameters
	/// @brief �p�����[�^�K��
	/// @param[in] name �K������p�����[�^�Z�b�g���ʎq
	void ApplyParameters(const char* name);

private:
	LPDIRECT3DDEVICE9 device_;

	std::map<std::string, std::vector<ParameterSet>> parameter_set_container_;

protected:
};

} // namespace snlib

#endif // SNLIB_RENDER_STATE_MANAGER_H_

//EOF