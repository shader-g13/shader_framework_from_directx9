/// @file SafeDelete.h
/// @brief  セーフデリート
/// @date 2015/06/10
/// @author syuki nishida
#pragma once
#ifndef SNLIB_SAFE_DELETE_H_
#define SNLIB_SAFE_DELETE_H_

#include <functional>

/// @namespace snlib
namespace snlib {

/// @fn SafeDelete
/// @brief セーフデリート
/// @param[in] 消す物
template<class type> void SafeDelete(type& data) {
	if (data == nullptr) return;
	delete data;
	data = nullptr;
}

/// @fn SafeDelete
/// @brief 仕事付きセーフデリート
/// @param[in] data 消すもの
/// @param[in] task 最後の仕事
template<class type> void SafeDelete(type& data, std::function<void(type&)> task) {
	if (data == nullptr) return;
	task(data);
	delete data;
	data = nullptr;
}

} // namespace snlib

#endif // SNLIB_SAFE_DELETE_H_

//EOF