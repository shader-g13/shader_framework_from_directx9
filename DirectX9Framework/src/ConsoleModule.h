/// @fn ConsoleModule.h
/// @brief �R���\�[�����W���[��
/// @date 2015/04/24
/// @author syuki nishida

#pragma once
#ifndef SNLIB_CONSOLE_MODUKE_H_
#define SNLIB_CONSOLE_MODULE_H_

#include <stdio.h>

/// @namespace snlib
namespace snlib {

/// @class ConsoleModule
class ConsoleModule {
public:
	/// @fn ConsoleModule
	/// @brief �f�t�H���g�R���X�g���N�^
	ConsoleModule();

	/// @fn ~ConsoleModule
	/// @brife �f�t�H���g�f�X�g���N�^
	virtual ~ConsoleModule();

	/// @fn CreateConsole
	/// @brief �R���\�[���o��
	void CreateConsole();

	/// @fn DeleteConsole
	/// @brief �R���\�[������
	void DeleteConsole();

	/// @fn SwitchVisible
	/// @brief �\���؂�ւ�
	void SwitchVisible();

protected:
private:
	FILE *fp_out_;
	FILE *fp_in_;

	bool visible_;
};

} // namespace snlib

#endif // SNLID_CONSOLE_MODULE_H_

//EOF