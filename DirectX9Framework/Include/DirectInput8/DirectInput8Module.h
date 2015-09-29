/// @file DirectInput8Module.h
/// @brief DirectInputモジュール
/// @date 2015/04/17
/// @author syuki nishida

#pragma once
#ifndef SNLIB_DIRECT_INPUT8_MODULE_H_
#define SNLIB_DIRECT_INPUT8_MODULE_H_

#include <Windows.h>
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

/// @namespace snlib
namespace snlib {

/// @class DirectInput8Module
/// @brief インプット関係
class DirectInput8Module {
public:
	/// @enum KeyCheckType
	/// @brief キー入力判定方法
	enum KeyCheckType {
		PRESS,
		TRIGG,
		RELEASE,
		PULSE,
		KEY_CHECK_TYPE_MAX,
	};

	/// @enum CompassToPov
	/// @brief Povの方向
	enum CompassToPov {
		POV_N = 0,
		POV_NE,
		POV_E,
		POV_SE,
		POV_S,
		POV_SW,
		POV_W,
		POV_NW,
	};

	/// @fn DirectInput8Module
	/// @brief デフォルトコンストラクタ
	/// @param[in] instance_handle インスタンスハンドル
	/// @param[in] window_handle ウィンドウハンドル
	DirectInput8Module(HINSTANCE instance_handle, HWND window_handle);

	/// @fn Initialize
	/// @brief 初期化
	/// @return 成功：true
	bool Initialize();

	/// @fn Finalize
	/// @brief 終了
	void Finalize();

	/// @fn Update
	/// @brief 更新
	void Update();

	/// @fn GetKeyboardState
	/// @brief キーボードの状態取得
	/// @param[in] key 調べるキー
	/// @param[in] type 調べるタイプ
	/// @return 押されてる：true
	bool GetKeyboardState(UCHAR key, KeyCheckType type);

	/// @fn GetJoystickButtonState
	/// @brief ジョイスティックのボタン状態取得
	/// @param[in] key 調べるキー
	/// @param[in] type 調べるタイプ
	/// @return 押されてる：true
	bool GetJoystickButtonState(UCHAR key, KeyCheckType type);

	/// @fn GetJoystickPovState
	/// @brief ジョイスティックの十字キー取得
	/// @param[in] pov 調べるキー
	/// @param[in] type 調べるタイプ
	/// @return 押されてる：true
	bool GetJoystickPovState(CompassToPov pov, KeyCheckType type);

	/// @fn GetJoystickLeftAnalogState
	/// @brief ジョイスティックの左アナログ
	/// @param[in] direction 方向　斜めはだめ
	/// @return 傾き
	long GetJoystickLeftAnalogState(CompassToPov direction);

	/// @fn GetJoystickRightAnalogState
	/// @brief ジョイスティックの右アナログ
	/// @param[in] direction 方向　斜めはだめ
	/// @return 傾き
	long GetJoystickRightAnalogState(CompassToPov direction);

	/// @fn SetPulseLate
	/// @brief パルスレート設定
	/// @param[in] lase レート
	__forceinline void SetPulseLate(UCHAR late) { pulse_late_ = late; }

protected:

private:
	HINSTANCE instance_handle_;
	HWND      window_handle_;

	LPDIRECTINPUT8A direct_input_;

	LPDIRECTINPUTDEVICE8A keyboard_device_;
	LPDIRECTINPUTDEVICE8A joystick_device_;

	UCHAR pulse_late_;

	UCHAR keyboard_state_cur_[256];
	UCHAR keyboard_state_old_[256];
	UCHAR keyboard_pulse_counter_[256];

	DIJOYSTATE2 joystick_state_cur_;
	DIJOYSTATE2 joystick_state_old_;
	UCHAR joystick_pulse_counter_button_[128];
	UCHAR joystick_pulse_counter_pov_[8];

	/// @fn InitializeKeyboard
	/// @brief キーボード初期化
	/// @return 成功：ture
	bool InitializeKeyboard();

	/// @fn FinalizeKeyboard
	/// @brief キーボード終了
	void FinalizeKeyboard();

	/// @fn UpdateKeyboard
	/// @brief キーボード更新
	void UpdateKeyboard();

	/// @fn InitializeJoystick
	/// @brief ジョイスティック初期化
	/// @return 成功：true
	bool InitializeJoystick();

	/// @fn FinalizeJoystick
	/// @brief ジョイスティック終了
	void FinalizeJoystick();

	/// @fn UpdateJoystick
	/// @brief ジョイスティック更新
	void UpdateJoystick();
};

#endif // SNLIB_DIRECT_INPUT8_MODULE_H_

} // namespace snlib

//EOF