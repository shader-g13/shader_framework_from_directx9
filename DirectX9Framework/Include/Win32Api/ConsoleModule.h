/// @fn ConsoleModule.h
/// @brief コンソールモジュール
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
	/// @brief デフォルトコンストラクタ
	ConsoleModule();

	/// @fn ~ConsoleModule
	/// @brife デフォルトデストラクタ
	virtual ~ConsoleModule();

	/// @fn CreateConsole
	/// @brief コンソール出す
	void CreateConsole();

	/// @fn DeleteConsole
	/// @brief コンソール消す
	void DeleteConsole();

	/// @fn SwitchVisible
	/// @brief 表示切り替え
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