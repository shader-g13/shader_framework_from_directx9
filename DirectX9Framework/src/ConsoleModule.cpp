/// @fn ConsoleModule.h
/// @brief コンソールモジュール
/// @date 2015/04/24
/// @author syuki nishida

#include "ConsoleModule.h"
#include <consoleapi.h>

/// @namespace snlib
namespace snlib {

/// @fn ConsoleModule
/// @brief デフォルトコンストラクタ
ConsoleModule::ConsoleModule() : visible_(false) {
#ifdef _DEBUG
	CreateConsole();
	visible_ = true;
#endif
}

/// @fn ~ConsoleModule
/// @brife デフォルトデストラクタ
ConsoleModule::~ConsoleModule() {
	DeleteConsole();
}

/// @fn CreateConsole
/// @brief コンソール出す
void ConsoleModule::CreateConsole() {
	if (visible_) return;
	visible_ = true;
	AllocConsole();
	freopen_s(&fp_out_, "CON", "w", stdout);
	freopen_s(&fp_in_, "CON", "r", stdin);
}

/// @fn DeleteConsole
/// @brief コンソール消す
void ConsoleModule::DeleteConsole() {
	if (!visible_) return;
	visible_ = false;
	fclose(fp_out_);
	fclose(fp_in_);
	FreeConsole();
}

/// @fn SwitchVisible
/// @brief 表示切り替え
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