/// @fn SceneInterface.h
/// @brief シーンインターフェース
/// @date 2015/04/18
/// @author syuki nishida

#pragma once
#ifndef SNLIB_SCENE_INTERFACE_H_
#define SNLIB_SCENE_INTERFACE_H_

#include <mutex>

/// @namespace snlib
namespace snlib {

/// @brief 前方宣言
class SceneSwitcher;

/// @class SceneInterface
class SceneInterface {
public:
	/// @fn SceneInterface
	/// @brief デフォルトコンストラクタ
	SceneInterface() : switcher_(nullptr), scene_mutex_(new std::mutex) {}

	/// @fn ~SceneInterface
	/// @brief デフォルトデストラクタ
	virtual ~SceneInterface() { delete scene_mutex_; }

	/// @fn Initialize
	/// @brief 初期化
	/// @return 成功：true
	virtual bool Initialize() = 0;

	/// @fn Finalize
	/// @brief 終了
	virtual void Finalize() = 0;

	/// @fn Update
	/// @brief 更新
	virtual void Update() = 0;

	/// @fn SetSwitcher
	/// @brief スイッチャー設定
	/// @param[in] switcher スイッチャーへのポインタ
	__forceinline void SetSwitcher(SceneSwitcher* switcher) { switcher_ = switcher; }

	/// @fn CreateSceneMutex
	/// @brief ミューテックス作成
	__forceinline void CreateSceneMutex() {
		if (!scene_mutex_) scene_mutex_ = new std::mutex;
	}

	/// @fn DeleteSceneMutex
	/// @brief ミューテックス削除
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