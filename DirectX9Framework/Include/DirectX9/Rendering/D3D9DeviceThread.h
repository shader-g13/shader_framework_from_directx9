/// @file D3DDeviceThread.h
/// @brief D3D9�f�o�C�X�X���b�h
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
	/// @brief �f�o�C�X�^�X�N
	struct DeviceTask {
		std::function<void(const LPDIRECT3DDEVICE9)> task;
		std::mutex** task_mutex;
		/// @fn DeviceTask
		/// @brief �R���X�g���N�^
		/// @param[in] task �f�o�C�X���g���^�X�N
		/// @param[in] task_resource_mutex �^�X�N�ň������\�[�X�̃~���[�e�b�N�X
		DeviceTask(
			const std::function<void(const LPDIRECT3DDEVICE9)>& task,
			std::mutex** task_resource_mutex)
			 : task(task),
			   task_mutex(task_resource_mutex) {}
	};

	/// @fn D3D9DeviceThread
	/// @brief �f�t�H���g�R���X�g���N�^
	/// @param[in] device �f�o�C�X
	D3D9DeviceThread(LPDIRECT3DDEVICE9 device);

	/// @fn ~D3D9DeviceThread
	/// @brief �f�t�H���g�f�X�g���N�^
	virtual ~D3D9DeviceThread();

	/// @fn DrawCall
	/// @brief �`��R�[�� �`�撆�������ꍇ�̓X�L�b�v����
	void DrawCall();

	/// @fn TheadEnd
	/// @brief �X���b�h�I��
	void ThreadEnd();

	/// @fn SetDeviceTast
	/// @brief �f�o�C�X�^�X�N��ݒ�
	/// @param[in] tast �C����^�X�N
	/// @param[in] resource_mutex �^�X�N�Ŏg�����\�[�X�̃~���[�e�b�N�X
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
	/// @brief �`��^�X�N��ݒ�
	/// @param[in] tast �C����^�X�N
	/// @param[in] resource_mutex �^�X�N�Ŏg�����\�[�X�̃~���[�e�b�N�X
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
	/// @brief �N���A�o�b�t�@�̃t���O�ݒ�
	/// @param[in] frags �ݒ肵�����t���O
	__forceinline void SetClearFrags(DWORD frags) {
		clear_flag_ = frags;
	}

	/// @fn SetClearColor
	/// @brief �N���A�J���[�ݒ�
	/// @param[in] color �ݒ肵�����F
	__forceinline void SetClearColor(D3DCOLOR& color) {
		clear_color_ = color;
	}

	/// @fn SetClearDepthValue
	/// @brief �N���A���̐[�x�o�b�t�@�̒l�ݒ�
	/// @param[in] z �ݒ肵�����[�x
	__forceinline void SetClearDepthValue(float z) {
		clear_z_ = z;
	}

	/// @fn SetClearStencil
	/// @brief �N���A���̃X�e���V���l�ݒ�
	/// @param[in] stencil �ݒ肵�����X�e���V���l
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