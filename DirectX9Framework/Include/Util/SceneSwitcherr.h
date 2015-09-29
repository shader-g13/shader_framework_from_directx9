/// @file SceneSwtcher.h
/// @brief �V�[���X�C�b�`���[
/// @date 2015/04/18
/// @author syuki nishida

#pragma once
#ifndef SNLIB_SCENE_SWITCHER_H_
#define SNLIB_SCENE_SWITCHER_H_

#include <string>
#include <map>

/// @namespace snlib
namespace snlib {

/// @class SceneInterface
class SceneInterface;

/// @class SceneSwitcher
class SceneSwitcher {
public:
	/// @fn SceneSwitcher
	/// @brief �f�t�H���g�R���X�g���N�^
	SceneSwitcher();

	/// @fn Update
	/// @brief �X�V
	void Update();

	/// @fn RegistScene
	/// @brief �V�[���o�^
	/// @param[in] scene_name �V�[���l�[��
	/// @param[in] scene �V�[��
	/// @return �����Ftrue
	bool RegistScene(const char* scene_name, SceneInterface* scene);

	/// @fn UnregistScene
	/// @brief �V�[���폜
	/// @param[in] scene_name �����V�[����
	/// @return �����Ftrue
	bool UnregistScene(const char* scene_name);

	/// @fn ClearScene
	/// @brief �V�[���S����
	void ClearScene();

	/// @fn StartScene
	/// @brief �V�[���X�^�[�g
	/// @param[in] scene_name �n�߂����V�[����
	void StartScene(const char* scene_name);

	/// @fn EndScene
	/// @brief �V�[���G���h
	void EndScene();

	/// @fn SwitchScene
	/// @brief �V�[���؂�ւ�
	/// @param[in] scene_name �؂�ւ���V�[����
	void SwitchScene(const char* scene_name);

	/// @fn GetScene
	/// @brief �V�[���擾
	/// @param[in] scnene_name ��肽���V�[����
	/// @return �V�[���ւ̃|�C���^
	__forceinline const SceneInterface* GetScene(const char* scene_name) {
		return scene_container_[scene_name];
	}

	/// @fn GetSceneName
	/// @brief ���̃V�[�����擾
	/// @return �V�[����
	__forceinline const char* GetSceneName() {
		return now_scene_name_.c_str();
	}

protected:
private:
	std::string now_scene_name_;
	SceneInterface* now_scene_;

	std::map<std::string, SceneInterface*> scene_container_;
};

} // namespace snlib

#endif // SNLIB_SCENE_SWITCH_H_

//EOF