/// @file DirectInput8Module.cpp
/// @brief DirectInputモジュール
/// @date 2015/04/17
/// @author syuki nishida

#include "DirectInput8Module.h"
#include <crtdbg.h>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

/// @namespace snlib
namespace snlib {

/// @fn DirectInput8Module
/// @brief デフォルトコンストラクタ
DirectInput8Module::DirectInput8Module(HINSTANCE instance_handle, HWND window_handle)
 : instance_handle_(instance_handle),
   window_handle_(window_handle),
   direct_input_(nullptr),
   keyboard_device_(nullptr),
   joystick_device_(nullptr),
   pulse_late_(0) {
}

/// @fn Initialize
/// @brief 初期化
/// @return 成功：true
bool DirectInput8Module::Initialize() {
	if (direct_input_)return false;

	HRESULT result;
	result = DirectInput8Create(instance_handle_,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		reinterpret_cast<void**>(&direct_input_),
		nullptr);

	_ASSERT_EXPR(SUCCEEDED(result), L"snlib DirectInput8Module error "
		L"DirectInput8Create is failed");

	if (FAILED(result)) return false;

	if (!InitializeKeyboard()) {
		direct_input_->Release();
		direct_input_ = nullptr;

		return false;
	}

	InitializeJoystick();

	return true;
}

/// @fn Finalize
/// @brief 終了
void DirectInput8Module::Finalize() {
	if (!direct_input_) return;

	direct_input_->Release();
	direct_input_ = nullptr;
}

/// @fn Update
/// @brief 更新
void DirectInput8Module::Update() {
	UpdateKeyboard();
	UpdateJoystick();
}

/// @fn GetKeyboardState
/// @brief キーボードの状態取得
/// @param[in] key 調べるキー
/// @param[in] type 調べるタイプ
/// @return 押されてる：true
bool DirectInput8Module::GetKeyboardState(UCHAR key, KeyCheckType type) {
	switch (type) {
	case PRESS:
		return keyboard_state_cur_[key] & 0x80 ? true : false;

	case TRIGG:
		return (keyboard_state_cur_[key] ^ keyboard_state_old_[key]) & keyboard_state_cur_[key] & 0x80 ? true : false;

	case RELEASE:
		return (keyboard_state_cur_[key] ^ keyboard_state_old_[key]) & keyboard_state_old_[key] & 0x80 ? true : false;

	case PULSE:
		if (!(keyboard_state_cur_[key] & 0x80)) return false;

		if (!(keyboard_state_old_[key] & 0x80)) {
			keyboard_pulse_counter_[key] = 0;
		}

		if (keyboard_pulse_counter_[key] >= pulse_late_) {
			keyboard_pulse_counter_[key] = 0;
			return true;
		}
		else {
			keyboard_pulse_counter_[key]++;
		}
		return false;
	}

	return false;
}

/// @fn GetJoystickButtonState
/// @brief ジョイスティックのボタン状態取得
/// @param[in] key 調べるキー
/// @param[in] type 調べるタイプ
/// @return 押されてる：true
bool DirectInput8Module::GetJoystickButtonState(UCHAR key, KeyCheckType type) {
	switch (type) {
	case PRESS:
		return joystick_state_cur_.rgbButtons[key] & 0x80 ? true : false;

	case TRIGG:
		return (joystick_state_cur_.rgbButtons[key] ^ joystick_state_old_.rgbButtons[key]) & joystick_state_cur_.rgbButtons[key] & 0x80 ? true : false;

	case RELEASE:
		return (joystick_state_cur_.rgbButtons[key] ^ joystick_state_old_.rgbButtons[key]) & joystick_state_old_.rgbButtons[key] & 0x80 ? true : false;

	case PULSE:
		if (!(joystick_state_cur_.rgbButtons[key] & 0x80)) return false;

		if (!(joystick_state_old_.rgbButtons[key] & 0x80)) {
			joystick_pulse_counter_button_[key] = 0;
		}

		if (joystick_pulse_counter_button_[key] >= pulse_late_) {
			joystick_pulse_counter_button_[key] = 0;
			return true;
		}
		else {
			joystick_pulse_counter_button_[key]++;
		}
		return false;
	}

	return false;
}

/// @fn GetJoystickPovState
/// @brief ジョイスティックの十字キー取得
/// @param[in] pov 調べるキー
/// @param[in] type 調べるタイプ
/// @return 押されてる：true
bool DirectInput8Module::GetJoystickPovState(CompassToPov pov, KeyCheckType type) {
	switch (type) {
	case PRESS:
		return joystick_state_cur_.rgdwPOV[0] == pov * 4500 ? true : false;

	case TRIGG:
		return ((joystick_state_cur_.rgdwPOV[0] ^ joystick_state_old_.rgdwPOV[0]) & joystick_state_cur_.rgdwPOV[0]) == pov * 4500 ? true : false;

	case RELEASE:
		return ((joystick_state_cur_.rgdwPOV[0] ^ joystick_state_old_.rgdwPOV[0]) & joystick_state_old_.rgdwPOV[0]) == pov * 4500 ? true : false;

	case PULSE:
		if (!(joystick_state_cur_.rgdwPOV[0] == pov * 4500)) return false;

		if (!(joystick_state_old_.rgdwPOV[0] == pov * 4500)) {
			joystick_pulse_counter_pov_[pov] = 0;
		}

		if (joystick_pulse_counter_pov_[pov] >= pulse_late_) {
			joystick_pulse_counter_pov_[pov] = 0;
			return true;
		}
		else {
			joystick_pulse_counter_pov_[pov]++;
		}
		return false;
	}

	return false;
}

/// @fn GetJoystickLeftAnalogState
/// @brief ジョイスティックの左アナログ
/// @param[in] direction 方向　斜めはだめ
/// @return 傾き
long DirectInput8Module::GetJoystickLeftAnalogState(CompassToPov direction) {
	switch (direction) {
	case POV_N:
		return -joystick_state_cur_.lY;
		break;

	case POV_E:
		return joystick_state_cur_.lX;
		break;

	case POV_S:
		return joystick_state_cur_.lY;
		break;

	case POV_W:
		return -joystick_state_cur_.lX;
		break;
	}

	return 0;
}

/// @fn GetJoystickRightAnalogState
/// @brief ジョイスティックの右アナログ
/// @param[in] direction 方向　斜めはだめ
/// @return 傾き
long DirectInput8Module::GetJoystickRightAnalogState(CompassToPov direction) {
	switch (direction) {
	case POV_N:
		return -joystick_state_cur_.lRz;
		break;

	case POV_E:
		return joystick_state_cur_.lZ;
		break;

	case POV_S:
		return joystick_state_cur_.lRz;
		break;

	case POV_W:
		return -joystick_state_cur_.lZ;
		break;
	}

	return 0;
}

/// @fn InitializeKeyboard
/// @brief キーボード初期化
/// @return 成功：ture
bool DirectInput8Module::InitializeKeyboard() {
	if (!direct_input_) return false;

	HRESULT result;
	result = direct_input_->CreateDevice(GUID_SysKeyboard,
		&keyboard_device_, nullptr);
	_ASSERT_EXPR(SUCCEEDED(result), L"DirectInput8Module error "
		L"keyboard device create is failed");

	if (FAILED(result)) return false;

	result = keyboard_device_->SetDataFormat(&c_dfDIKeyboard);
	_ASSERT_EXPR(SUCCEEDED(result), L"DirectInput8Module error "
		L"keyboard dataformat set is failsd");

	if (FAILED(result)) {
		FinalizeKeyboard();
		return false;
	}

	result = keyboard_device_->SetCooperativeLevel(
		window_handle_,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));

	if (FAILED(result)) {
		FinalizeKeyboard();
		return false;
	}

	keyboard_device_->Acquire();

	return true;
}

/// @fn FinalizeKeyboard
/// @brief キーボード終了
void DirectInput8Module::FinalizeKeyboard() {
	if (!keyboard_device_) return;

	keyboard_device_->Unacquire();
	keyboard_device_->Release();
	keyboard_device_ = nullptr;
}

/// @fn UpdateKeyboard
/// @brief キーボード更新
void DirectInput8Module::UpdateKeyboard() {
	if (!keyboard_device_) return;

	UCHAR current_state[256];

	HRESULT result;
	result = keyboard_device_->GetDeviceState(sizeof(current_state), current_state);
	if (FAILED(result)) {
		keyboard_device_->Acquire();
		return;
	}

	memcpy_s(keyboard_state_old_, sizeof(keyboard_state_old_),
		keyboard_state_cur_, sizeof(keyboard_state_cur_));

	memcpy_s(keyboard_state_cur_, sizeof(keyboard_state_cur_),
		current_state, sizeof(current_state));
}

/// @fn InitializeJoystick
/// @brief ジョイスティック初期化
/// @return 成功：true
bool DirectInput8Module::InitializeJoystick() {
	if (joystick_device_) return false;

	struct CallbackData {
		LPDIRECTINPUT8 direct_input_;
		LPDIRECTINPUTDEVICE8* joystick_device_;
	};
	CallbackData data = { direct_input_, &joystick_device_ };

	auto enum_joystick_devices_callback =
		[](LPCDIDEVICEINSTANCEA instance, LPVOID ptr) {
		CallbackData* data = static_cast<CallbackData*>(ptr);

		HRESULT result;
		result = data->direct_input_->CreateDevice(instance->guidInstance,
			data->joystick_device_, nullptr);
		if (FAILED(result)) return DIENUM_CONTINUE;

		return DIENUM_STOP;
	};

	auto enum_joystick_object_callback =
		[](LPCDIDEVICEOBJECTINSTANCEA instance, LPVOID ptr)->BOOL {
		CallbackData* data = static_cast<CallbackData*>(ptr);
		LPDIRECTINPUTDEVICE8 joy_device = *data->joystick_device_;

		DIPROPRANGE range;
		range.diph.dwSize = sizeof(DIPROPRANGE);
		range.diph.dwHeaderSize = sizeof(DIPROPHEADER);
		range.diph.dwHow = DIPH_BYID;
		range.diph.dwObj = instance->dwType;
		range.lMin = -1000;
		range.lMax = +1000;

		HRESULT result;
		result = joy_device->SetProperty(DIPROP_RANGE, &range.diph);

		if (FAILED(result)) return DIENUM_STOP;

		return DIENUM_CONTINUE;
	};

	HRESULT result;

	result = direct_input_->EnumDevices(
		DI8DEVCLASS_GAMECTRL,
		enum_joystick_devices_callback,
		&data,
		DIEDFL_ATTACHEDONLY);

	_ASSERT_EXPR(SUCCEEDED(result), L"DirectInput8Module error "
		L"joystick デバイス列挙処理関数の設定に失敗");
	if (FAILED(result)) {
		FinalizeJoystick();
		return false;
	}

	if (!joystick_device_) {
		FinalizeJoystick();
		return false;
	}

	result = joystick_device_->SetDataFormat(&c_dfDIJoystick2);
	_ASSERT_EXPR(SUCCEEDED(result), L"DirectInput8Module error "
		L"joystick データフォーマットの設定に失敗");
	if (FAILED(result)) {
		FinalizeJoystick();
		return false;
	}

	result = joystick_device_->SetCooperativeLevel(
		window_handle_,
		(DISCL_FOREGROUND | DISCL_EXCLUSIVE));

	_ASSERT_EXPR(SUCCEEDED(result), L"DirectInput8Module error "
		L"joystick 協調設定に失敗");
	if (FAILED(result)) {
		FinalizeJoystick();
		return false;
	}

	result = joystick_device_->EnumObjects(enum_joystick_object_callback,
		&data, DIDFT_ALL);
	_ASSERT_EXPR(SUCCEEDED(result), L"DirectInput8Module error "
		L"joystick オブジェクト列挙関数設定に失敗");
	if (FAILED(result)) {
		FinalizeJoystick();
		return false;
	}

	while (joystick_device_->Acquire() == DIERR_INPUTLOST);

	return true;
}

/// @fn FinalizeJoystick
/// @brief ジョイスティック終了
void DirectInput8Module::FinalizeJoystick() {
	if (!joystick_device_) return;

	joystick_device_->Release();
	joystick_device_ = nullptr;
}

/// @fn UpdateJoystick
/// @brief ジョイスティック更新
void DirectInput8Module::UpdateJoystick() {
	if (!joystick_device_) return;

	HRESULT result;
	result = joystick_device_->Poll();
	if (FAILED(result)) {
		joystick_device_->Acquire();
		return;
	}

	DIJOYSTATE2 current_data;
	result = joystick_device_->GetDeviceState(sizeof(DIJOYSTATE2), &current_data);

	memcpy_s(&joystick_state_old_, sizeof(DIJOYSTATE2),
		&joystick_state_cur_, sizeof(DIJOYSTATE2));
	memcpy_s(&joystick_state_cur_, sizeof(DIJOYSTATE2),
		&current_data, sizeof(DIJOYSTATE2));
}

} // namespace snlib

//EOF