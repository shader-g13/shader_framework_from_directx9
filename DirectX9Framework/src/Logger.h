/// @file Logger.h
/// @brief ���K�[
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
	/// @brief ���O�o�͊J�n
	static void Start();

	/// @fn End
	/// @brief ���O�o�͏I��
	static void End();

	/// @fn Log
	/// @brief ���O�o��
	/// @param[in] type �^�C�v
	/// @param[in] format ����
	static void Log(LogType type, const char* format, ...);

	/// @fn IsLogging
	/// @brief ���O�Ƃ��Ă邩
	/// @return �Ƃ��Ă�Ftrue
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
	/// @brief �f�t�H���g�R���X�g���N�^
	Logger();

	/// @fn ~Logger
	/// @brief �f�t�H���g�f�X�g���N�^
	virtual ~Logger();

	/// @fn _Log
	/// @brief ���O�o�͂̃��W�b�N
	/// @param[in] type �^�C�v
	/// @param[in] format ����
	void _Log(LogType type, const char* format, ...);

};

} // namespace snlib

#endif // SNLIB_LOGGER_H_

//EOF