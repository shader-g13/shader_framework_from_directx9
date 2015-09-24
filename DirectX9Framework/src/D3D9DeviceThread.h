/// @file D3DDeviceThread.h
/// @brief D3D9デバイススレッド
/// @date 2015/06/26
/// @author syuki nishida
#pragma once
#ifndef SNLIB_D3D_DEVICE_THREAD_H_
#define SNLIB_D3D_DEVICE_THREAD_H_

#include <d3d9.h>
#include <functional>
#include <mutex>
#include <thread>
#include <queue>
#include <condition_variable>
#include <atomic>

/// @namespace snlib
namespace snlib {

/// @class D3D9DeviceThread
class D3D9DeviceThread {
public:
	/// @struct DeviceTask
	/// @brief デバイスタスク
	struct DeviceTask {
		std::function<void(const LPDIRECT3DDEVICE9)> task;
		std::mutex** task_mutex;
		/// @fn DeviceTask
		/// @brief コンストラクタ
		/// @param[in] task デバイスを使うタスク
		/// @param[in] task_resource_mutex タスクで扱うリソースのミューテックス
		DeviceTask(
			const std::function<void(const LPDIRECT3DDEVICE9)>& task,
			std::mutex** task_resource_mutex)
			 : task(task),
			   task_mutex(task_resource_mutex) {}
	};

	/// @fn D3D9DeviceThread
	/// @brief デフォルトコンストラクタ
	/// @param[in] device デバイス
	D3D9DeviceThread(LPDIRECT3DDEVICE9 device);

	/// @fn ~D3D9DeviceThread
	/// @brief デフォルトデストラクタ
	virtual ~D3D9DeviceThread();

	/// @fn DrawCall
	/// @brief 描画コール 描画中だった場合はスキップする
	void DrawCall();

	/// @fn TheadEnd
	/// @brief スレッド終了
	void ThreadEnd();

	/// @fn SetDeviceTast
	/// @brief デバイスタスクを設定
	/// @param[in] tast 任せるタスク
	/// @param[in] resource_mutex タスクで使うリソースのミューテックス
	__forceinline void SetDeviceTask(
		const std::function<void(const LPDIRECT3DDEVICE9)>& task,
		std::mutex** resource_mutex) {
		if (!thread_life_) return;
		DeviceTask device_task(task, resource_mutex);
		std::thread push_thread([=] {
			device_task_mutex_.lock();
			device_task_.push(device_task);
			device_task_mutex_.unlock();
		});
		push_thread.detach();
	}

	/// @fn SetDrawTask
	/// @brief 描画タスクを設定
	/// @param[in] tast 任せるタスク
	/// @param[in] resource_mutex タスクで使うリソースのミューテックス
	__forceinline void SetDrawTask(
		const std::function<void(const LPDIRECT3DDEVICE9)>& task,
		std::mutex** resource_mutex) {
		if (!thread_life_) return;
		DeviceTask device_task(task, resource_mutex);
		draw_task_mutex_.lock();
		draw_task_.push(device_task);
		draw_task_mutex_.unlock();
	}

	/// @fn SetClearFrags
	/// @brief クリアバッファのフラグ設定
	/// @param[in] frags 設定したいフラグ
	__forceinline void SetClearFrags(DWORD frags) {
		clear_flag_ = frags;
	}

	/// @fn SetClearColor
	/// @brief クリアカラー設定
	/// @param[in] color 設定したい色
	__forceinline void SetClearColor(D3DCOLOR& color) {
		clear_color_ = color;
	}

	/// @fn SetClearDepthValue
	/// @brief クリア時の深度バッファの値設定
	/// @param[in] z 設定したい深度
	__forceinline void SetClearDepthValue(float z) {
		clear_z_ = z;
	}

	/// @fn SetClearStencil
	/// @brief クリア時のステンシル値設定
	/// @param[in] stencil 設定したいステンシル値
	__forceinline void SetClearStencil(DWORD stencil) {
		clear_stencil_ = stencil;
	}

protected:
private:
	LPDIRECT3DDEVICE9 device_;

	std::thread device_thread_;

	std::mutex device_task_mutex_;
	std::mutex draw_task_mutex_;
	std::mutex condition_mutex_;

	std::queue<DeviceTask> device_task_;
	std::queue<DeviceTask> draw_task_;

	std::condition_variable condition_;

	std::atomic<bool> thread_life_;

	DWORD clear_flag_;
	D3DCOLOR clear_color_;
	float clear_z_;
	DWORD clear_stencil_;
};

} // namespace snlib

#endif // SNLIB_D3D_DEVICE_THREAD_H_

//EOF