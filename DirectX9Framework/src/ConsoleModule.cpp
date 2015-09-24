/// @fn ConsoleModule.h
/// @brief �R���\�[�����W���[��
/// @date 2015/04/24
/// @author syuki nishida

#include "ConsoleModule.h"
#include <consoleapi.h>

/// @namespace snlib
namespace snlib {

/// @fn ConsoleModule
/// @brief �f�t�H���g�R���X�g���N�^
ConsoleModule::ConsoleModule() : visible_(false) {
#ifdef _DEBUG
	CreateConsole();
	visible_ = true;
#endif
}

/// @fn ~ConsoleModule
/// @brife �f�t�H���g�f�X�g���N�^
ConsoleModule::~ConsoleModule() {
	DeleteConsole();
}

/// @fn CreateConsole
/// @brief �R���\�[���o��
void ConsoleModule::CreateConsole() {
	if (visible_) return;
	visible_ = true;
	AllocConsole();
	freopen_s(&fp_out_, "CON", "w", stdout);
	freopen_s(&fp_in_, "CON", "r", stdin);
}

/// @fn DeleteConsole
/// @brief �R���\�[������
void ConsoleModule::DeleteConsole() {
	if (!visible_) return;
	visible_ = false;
	fclose(fp_out_);
	fclose(fp_in_);
	FreeConsole();
}

/// @fn SwitchVisible
/// @brief �\���؂�ւ�
void ConsoleModule::SwitchVisible() {
	visible_ ^= true;

	if (visible_) {
		CreateConsole();
	}
	else {
		DeleteConsole();
	}
}

} // namespace snlib

//EOF