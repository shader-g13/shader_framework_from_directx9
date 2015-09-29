/// @file SceneSwitcher.cpp
/// @brief �V�[���X�C�b�`���[
/// @date 2015/04/18
/// @author syuki nishida

#include <Util/SceneSwitcherr.h>
#include <Util/SceneInterface.h>

/// @namespace snlib
namespace snlib {

/// @fn SceneSwitcher
/// @brief �f�t�H���g�R���X�g���N�^
SceneSwitcher::SceneSwitcher() : now_scene_(nullptr) {
}

/// @fn Update
/// @brief �X�V
void SceneSwitcher::Update() {
	if (!now_scene_) return;
	now_scene_->Update();
}

/// @fn RegistScene
/// @brief �V�[���o�^
/// @param[in] scene_name �V�[���l�[��
/// @param[in] scene �V�[��
/// @return �����Ftrue
bool SceneSwitcher::RegistScene(const char* scene_name, SceneInterface* scene) {
	if (scene_container_.count(scene_name)) return false;

	std::pair<std::string, SceneInterface*> pair(scene_name, scene);
	scene_container_.insert(pair);
	scene->SetSwitcher(this);
	return true;
}

/// @fn UnregistScene
/// @brief �V�[���폜
/// @param[in] scene_name �����V�[����
/// @return �����Ftrue
bool SceneSwitcher::UnregistScene(const char* scene_name) {
	if (!scene_container_.count(scene_name)) return false;
	scene_container_[scene_name]->SetSwitcher(nullptr);
	scene_container_.erase(scene_name);
	return true;
}

/// @fn ClearScene
/// @brief �V�[���S����
void SceneSwitcher::ClearScene() {
	for (auto it : scene_container_) {
		it.second->SetSwitcher(nullptr);
	}
	scene_container_.clear();
}

/// @fn StartScene
/// @brief �V�[���X�^�[�g
/// @param[in] scene_name �n�߂����V�[����
void SceneSwitcher::StartScene(const char* scene_name) {
	now_scene_name_ = scene_name;
	now_scene_ = scene_container_[now_scene_name_];

	bool ret = now_scene_->Initialize();
	_ASSERT_EXPR(ret, L"snlib SceneWsitcher error "
		L"�V�[���̏������Ɏ��s");
}

/// @fn EndScene
/// @brief �V�[���G���h
void SceneSwitcher::EndScene() {
	if (now_scene_) {
		now_scene_->Finalize();
	}
}

/// @fn SwitchScene
/// @brief �V�[���؂�ւ�
/// @param[in] scene_name �؂�ւ���V�[����
void SceneSwitcher::SwitchScene(const char* scene_name) {
	now_scene_->Finalize();
	now_scene_name_ = scene_name;
	now_scene_ = scene_container_[now_scene_name_];
	_ASSERT_EXPR(now_scene_, L"snlib SceneSwitcher error "
		L"�w�肳�ꂽ�V�[�����o�^����Ă��܂���");
	if (!now_scene_) return;
	bool ret = now_scene_->Initialize();
	_ASSERT_EXPR(ret, L"snlib SceneWsitcher error "
		L"�V�[���̏������Ɏ��s");
}

} // namespace snlib

//EOF