/// @file SceneSwitcher.cpp
/// @brief シーンスイッチャー
/// @date 2015/04/18
/// @author syuki nishida

#include <Util/SceneSwitcherr.h>
#include <Util/SceneInterface.h>

/// @namespace snlib
namespace snlib {

/// @fn SceneSwitcher
/// @brief デフォルトコンストラクタ
SceneSwitcher::SceneSwitcher() : now_scene_(nullptr) {
}

/// @fn Update
/// @brief 更新
void SceneSwitcher::Update() {
	if (!now_scene_) return;
	now_scene_->Update();
}

/// @fn RegistScene
/// @brief シーン登録
/// @param[in] scene_name シーンネーム
/// @param[in] scene シーン
/// @return 成功：true
bool SceneSwitcher::RegistScene(const char* scene_name, SceneInterface* scene) {
	if (scene_container_.count(scene_name)) return false;

	std::pair<std::string, SceneInterface*> pair(scene_name, scene);
	scene_container_.insert(pair);
	scene->SetSwitcher(this);
	return true;
}

/// @fn UnregistScene
/// @brief シーン削除
/// @param[in] scene_name 消すシーン名
/// @return 成功：true
bool SceneSwitcher::UnregistScene(const char* scene_name) {
	if (!scene_container_.count(scene_name)) return false;
	scene_container_[scene_name]->SetSwitcher(nullptr);
	scene_container_.erase(scene_name);
	return true;
}

/// @fn ClearScene
/// @brief シーン全消し
void SceneSwitcher::ClearScene() {
	for (auto it : scene_container_) {
		it.second->SetSwitcher(nullptr);
	}
	scene_container_.clear();
}

/// @fn StartScene
/// @brief シーンスタート
/// @param[in] scene_name 始めたいシーン名
void SceneSwitcher::StartScene(const char* scene_name) {
	now_scene_name_ = scene_name;
	now_scene_ = scene_container_[now_scene_name_];

	bool ret = now_scene_->Initialize();
	_ASSERT_EXPR(ret, L"snlib SceneWsitcher error "
		L"シーンの初期化に失敗");
}

/// @fn EndScene
/// @brief シーンエンド
void SceneSwitcher::EndScene() {
	if (now_scene_) {
		now_scene_->Finalize();
	}
}

/// @fn SwitchScene
/// @brief シーン切り替え
/// @param[in] scene_name 切り替え先シーン名
void SceneSwitcher::SwitchScene(const char* scene_name) {
	now_scene_->Finalize();
	now_scene_name_ = scene_name;
	now_scene_ = scene_container_[now_scene_name_];
	_ASSERT_EXPR(now_scene_, L"snlib SceneSwitcher error "
		L"指定されたシーンが登録されていません");
	if (!now_scene_) return;
	bool ret = now_scene_->Initialize();
	_ASSERT_EXPR(ret, L"snlib SceneWsitcher error "
		L"シーンの初期化に失敗");
}

} // namespace snlib

//EOF