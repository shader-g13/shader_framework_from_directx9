/// @file D3DDeviceThread.cpp
/// @brief D3D9�f�o�C�X�X���b�h
/// @date 2015/06/26
/// @author syuki nishida

#include "D3D9DeviceThread.h"

/// @namespace snlib
namespace snlib {

/// @fn D3D9DeviceThread
/// @brief �f�t�H���g�R���X�g���N�^
D3D9DeviceThread::D3D9DeviceThread(LPDIRECT3DDEVICE9 device)
 : device_(device),
   thread_life_(true),
	 clear_flag_(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL),
	 clear_color_(D3DCOLOR_RGBA(50, 0, 50, 0)),
	 clear_z_(1),
	 clear_stencil_(0) {
	auto function = [&] {

		while (thread_life_) {
			std::unique_lock<std::mutex> lock(condition_mutex_);
			condition_.wait(lock);

			if (!thread_life_) return;

			device_task_mutex_.lock();
			while (!device_task_.empty()) {
				if (!*device_task_.front().task_mutex) {
					device_task_.pop();
					continue;
				}

				(*device_task_.front().task_mutex)->lock();
				device_task_.front().task(device_);
				(*device_task_.front().task_mutex)->unlock();
				device_task_.pop();
			}
			device_task_mutex_.unlock();

			device_->Clear(0, nullptr,
				clear_flag_,
				clear_color_,
				clear_z_,
				clear_stencil_);
			if (FAILED(device_->BeginScene())) {
				continue;
			}

			draw_task_mutex_.lock();
			while (!draw_task_.empty()) {
				if (!*draw_task_.front().task_mutex) {
					draw_task_.pop();
					continue;
				}

				(*draw_task_.front().task_mutex)->lock();
				draw_task_.front().task(device_);
				(*draw_task_.front().task_mutex)->unlock();

				draw_task_.pop();
			}
			draw_task_mutex_.unlock();

			device_->EndScene();
			device_->Present(nullptr, nullptr, nullptr, nullptr);
		}
	};

	std::thread buff(function);
	device_thread_.swap(buff);
}

/// @fn ~D3D9DeviceThread
/// @brief �f�t�H���g�f�X�g���N�^
D3D9DeviceThread::~D3D9DeviceThread() {
	ThreadEnd();
}

/// @fn DrawCall
/// @brief �`��R�[���@�`�撆�������ꍇ�̓X�L�b�v����
void D3D9DeviceThread::DrawCall() {
	std::unique_lock<std::mutex> lock(condition_mutex_);
	condition_.notify_one();
}

/// @fn TheadEnd
/// @brief �X���b�h�I��
void D3D9DeviceThread::ThreadEnd() {
	if (!thread_life_) return;

	std::lock(device_task_mutex_, draw_task_mutex_);

	while (!device_task_.empty() || !draw_task_.empty()) {
		if (!device_task_.empty()) {
			device_task_.pop();
		}
		if (!draw_task_.empty()) {
			draw_task_.pop();
		}
	}
	device_task_mutex_.unlock();
	draw_task_mutex_.unlock();

	DrawCall();
	thread_life_ = false;
	while (!device_thread_.joinable()) {
		DrawCall();
	}
	device_thread_.join();
}

} // namespace snlib

//EOF