/// @file Logger.cpp
/// @brief ロガー
/// @date 2015/04/27
/// @author syuki nishida

#include "Logger.h"
#include <stdio.h>
#include <iostream>
#include <time.h>

/// @namespace snib
namespace snlib {

Logger* Logger::singleton_ = nullptr;

/// @fn Start
/// @brief ログ出力開始
void Logger::Start() {
	if (singleton_) return;
	singleton_ = new Logger();

	singleton_->_Log(LOG_INFO, "Start log");
}

/// @fn End
/// @brief ログ出力終了
void Logger::End() {
	if (!singleton_) return;

	singleton_->_Log(LOG_INFO, "End log");

	delete singleton_;
}

/// @fn IsLogging
/// @brief ログとってるか
/// @return とってる：true
bool Logger::isLogging() {
	return singleton_ ? true : false;
}

/// @fn Log
/// @brief ログ出力
/// @param[in] type タイプ
/// @param[in] format 書式
void Logger::Log(LogType type, const char* format, ...) {
	if (!singleton_) {
		return;
	}
	singleton_->_Log(type, format);
}

/// @fn Logger
/// @brief デフォルトコンストラクタ
Logger::Logger() {

	sprintf_s(log_type_str_[0], "  ERROR  ");
	sprintf_s(log_type_str_[1], " WARNING ");
	sprintf_s(log_type_str_[2], "  INFO   ");
	sprintf_s(log_type_str_[3], " DEBUG   ");
	sprintf_s(log_type_str_[4], "VERRBOSE ");

	time_t buf = time(nullptr);
	tm date;
	localtime_s(&date, &buf);

	char file_name[17];

	sprintf_s(file_name, sizeof(file_name), LOG_DIR"%4d%02d%02d.log",
		date.tm_year + 1900, date.tm_mon + 1, date.tm_mday);

	outfile_ = new std::ofstream(file_name, std::ios::app);
}

/// @fn ~Logger
/// @brief デフォルトデストラクタ
Logger::~Logger() {
	delete outfile_;
	outfile_ = nullptr;
}

/// @fn _Log
/// @brief ログ出力のロジック
/// @param[in] type タイプ
/// @param[in] format 書式
void Logger::_Log(LogType type, const char* format, ...) {
	va_list arg;
	int arg_len;

	_crt_va_start(arg, format);
	arg_len = vsprintf_s(buffer_, format, arg);
	_crt_va_end(arg);

	memcpy_s(message_, sizeof(message_),
		log_type_str_[type], sizeof(log_type_str_[type]));

	time_t buf = time(nullptr);
	tm date;
	localtime_s(&date, &buf);

	sprintf_s(time_buf_, sizeof(time_buf_), "%02d:%02d:%02d ",
		date.tm_hour, date.tm_min, date.tm_sec);

	strcat_s(message_, sizeof(message_), time_buf_);

	strcat_s(message_, sizeof(message_), buffer_);

	(*outfile_) << message_ << std::endl;
	printf("%s\n", message_);
}

} // namespace snlib

//EOF