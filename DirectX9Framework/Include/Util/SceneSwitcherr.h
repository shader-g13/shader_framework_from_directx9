/// @file SceneSwtcher.h
/// @brief シーンスイッチャー
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
	/// @brief デフォルトコンストラクタ
	SceneSwitcher();

	/// @fn Update
	/// @brief 更新
	void Update();

	/// @fn RegistScene
	/// @brief シーン登録
	/// @param[in] scene_name シーンネーム
	/// @param[in] scene シーン
	/// @return 成功：true
	bool RegistScene(const char* scene_name, SceneInterface* scene);

	/// @fn UnregistScene
	/// @brief シーン削除
	/// @param[in] scene_name 消すシーン名
	/// @return 成功：true
	bool UnregistScene(const char* scene_name);

	/// @fn ClearScene
	/// @brief シーン全消し
	void ClearScene();

	/// @fn StartScene
	/// @brief シーンスタート
	/// @param[in] scene_name 始めたいシーン名
	void StartScene(const char* scene_name);

	/// @fn EndScene
	/// @brief シーンエンド
	void EndScene();

	/// @fn SwitchScene
	/// @brief シーン切り替え
	/// @param[in] scene_name 切り替え先シーン名
	void SwitchScene(const char* scene_name);

	/// @fn GetScene
	/// @brief シーン取得
	/// @param[in] scnene_name 取りたいシーン名
	/// @return シーンへのポインタ
	__forceinline const SceneInterface* GetScene(const char* scene_name) {
		return scene_container_[scene_name];
	}

	/// @fn GetSceneName
	/// @brief 今のシーン名取得
	/// @return シーン名
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