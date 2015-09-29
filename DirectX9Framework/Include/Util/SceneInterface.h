/// @fn SceneInterface.h
/// @brief �V�[���C���^�[�t�F�[�X
/// @date 2015/04/18
/// @author syuki nishida

#pragma once
#ifndef SNLIB_SCENE_INTERFACE_H_
#define SNLIB_SCENE_INTERFACE_H_

#include <mutex>

/// @namespace snlib
namespace snlib {

/// @brief �O���錾
class SceneSwitcher;

/// @class SceneInterface
class SceneInterface {
public:
	/// @fn SceneInterface
	/// @brief �f�t�H���g�R���X�g���N�^
	SceneInterface() : switcher_(nullptr), scene_mutex_(new std::mutex) {}

	/// @fn ~SceneInterface
	/// @brief �f�t�H���g�f�X�g���N�^
	virtual ~SceneInterface() { delete scene_mutex_; }

	/// @fn Initialize
	/// @brief ������
	/// @return �����Ftrue
	virtual bool Initialize() = 0;

	/// @fn Finalize
	/// @brief �I��
	virtual void Finalize() = 0;

	/// @fn Update
	/// @brief �X�V
	virtual void Update() = 0;

	/// @fn SetSwitcher
	/// @brief �X�C�b�`���[�ݒ�
	/// @param[in] switcher �X�C�b�`���[�ւ̃|�C���^
	__forceinline void SetSwitcher(SceneSwitcher* switcher) { switcher_ = switcher; }

	/// @fn CreateSceneMutex
	/// @brief �~���[�e�b�N�X�쐬
	__forceinline void CreateSceneMutex() {
		if (!scene_mutex_) scene_mutex_ = new std::mutex;
	}

	/// @fn DeleteSceneMutex
	/// @brief �~���[�e�b�N�X�폜
	__forceinline void DeleteSceneMutex() {
		if (!scene_mutex_) return;
		while (!scene_mutex_->try_lock());
		scene_mutex_->unlock();
		delete scene_mutex_;
		scene_mutex_ = nullptr;
	}

protected:
	SceneSwitcher* switcher_;
	std::mutex* scene_mutex_;
private:
};

} // namespace snlib

#endif // SNLIB_SCENE_INTERFACE_H_

//EOF