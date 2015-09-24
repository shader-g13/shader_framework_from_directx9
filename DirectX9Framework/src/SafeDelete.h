/// @file SafeDelete.h
/// @brief  �Z�[�t�f���[�g
/// @date 2015/06/10
/// @author syuki nishida
#pragma once
#ifndef SNLIB_SAFE_DELETE_H_
#define SNLIB_SAFE_DELETE_H_

#include <functional>

/// @namespace snlib
namespace snlib {

/// @fn SafeDelete
/// @brief �Z�[�t�f���[�g
/// @param[in] ������
template<class type> void SafeDelete(type& data) {
	if (data == nullptr) return;
	delete data;
	data = nullptr;
}

/// @fn SafeDelete
/// @brief �d���t���Z�[�t�f���[�g
/// @param[in] data ��������
/// @param[in] task �Ō�̎d��
template<class type> void SafeDelete(type& data, std::function<void(type&)> task) {
	if (data == nullptr) return;
	task(data);
	delete data;
	data = nullptr;
}

} // namespace snlib

#endif // SNLIB_SAFE_DELETE_H_

//EOF