/// @file Logger.h
/// @brief ロガー
/// @date 2015/04/27
/// @author syuki nishida

#pragma once
#ifndef SNLIB_LOGGER_H_
#define SNLIB_LOGGER_H_

#define LOG_DIR "log/"

#include <fstream>

/// @namespace snlib
namespace snlib {

/// @class Logger
class Logger {
public:
	enum LogType {
		LOG_ERROR,
		LOG_WARN,
		LOG_INFO,
		LOG_DEBUG,
		LOG_VERRBOSE,
	};

	/// @fn Start
	/// @brief ログ出力開始
	static void Start();

	/// @fn End
	/// @brief ログ出力終了
	static void End();

	/// @fn Log
	/// @brief ログ出力
	/// @param[in] type タイプ
	/// @param[in] format 書式
	static void Log(LogType type, const char* format, ...);

	/// @fn IsLogging
	/// @brief ログとってるか
	/// @return とってる：true
	static bool isLogging();

protected:
private:
	static Logger* singleton_;

	char buffer_[1024 - 10 - 10];
	char time_buf_[10];
	char message_[1024];

	char log_type_str_[5][10];

	std::ofstream* outfile_;

	/// @fn Logger
	/// @brief デフォルトコンストラクタ
	Logger();

	/// @fn ~Logger
	/// @brief デフォルトデストラクタ
	virtual ~Logger();

	/// @fn _Log
	/// @brief ログ出力のロジック
	/// @param[in] type タイプ
	/// @param[in] format 書式
	void _Log(LogType type, const char* format, ...);

};

} // namespace snlib

#endif // SNLIB_LOGGER_H_

//EOF