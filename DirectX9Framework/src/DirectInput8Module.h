/// @file DirectInput8Module.h
/// @brief DirectInput���W���[��
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
/// @brief �C���v�b�g�֌W
class DirectInput8Module {
public:
	/// @enum KeyCheckType
	/// @brief �L�[���͔�����@
	enum KeyCheckType {
		PRESS,
		TRIGG,
		RELEASE,
		PULSE,
		KEY_CHECK_TYPE_MAX,
	};

	/// @enum CompassToPov
	/// @brief Pov�̕���
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
	/// @brief �f�t�H���g�R���X�g���N�^
	/// @param[in] instance_handle �C���X�^���X�n���h��
	/// @param[in] window_handle �E�B���h�E�n���h��
	DirectInput8Module(HINSTANCE instance_handle, HWND window_handle);

	/// @fn Initialize
	/// @brief ������
	/// @return �����Ftrue
	bool Initialize();

	/// @fn Finalize
	/// @brief �I��
	void Finalize();

	/// @fn Update
	/// @brief �X�V
	void Update();

	/// @fn GetKeyboardState
	/// @brief �L�[�{�[�h�̏�Ԏ擾
	/// @param[in] key ���ׂ�L�[
	/// @param[in] type ���ׂ�^�C�v
	/// @return ������Ă�Ftrue
	bool GetKeyboardState(UCHAR key, KeyCheckType type);

	/// @fn GetJoystickButtonState
	/// @brief �W���C�X�e�B�b�N�̃{�^����Ԏ擾
	/// @param[in] key ���ׂ�L�[
	/// @param[in] type ���ׂ�^�C�v
	/// @return ������Ă�Ftrue
	bool GetJoystickButtonState(UCHAR key, KeyCheckType type);

	/// @fn GetJoystickPovState
	/// @brief �W���C�X�e�B�b�N�̏\���L�[�擾
	/// @param[in] pov ���ׂ�L�[
	/// @param[in] type ���ׂ�^�C�v
	/// @return ������Ă�Ftrue
	bool GetJoystickPovState(CompassToPov pov, KeyCheckType type);

	/// @fn GetJoystickLeftAnalogState
	/// @brief �W���C�X�e�B�b�N�̍��A�i���O
	/// @param[in] direction �����@�΂߂͂���
	/// @return �X��
	long GetJoystickLeftAnalogState(CompassToPov direction);

	/// @fn GetJoystickRightAnalogState
	/// @brief �W���C�X�e�B�b�N�̉E�A�i���O
	/// @param[in] direction �����@�΂߂͂���
	/// @return �X��
	long GetJoystickRightAnalogState(CompassToPov direction);

	/// @fn SetPulseLate
	/// @brief �p���X���[�g�ݒ�
	/// @param[in] lase ���[�g
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
	/// @brief �L�[�{�[�h������
	/// @return �����Fture
	bool InitializeKeyboard();

	/// @fn FinalizeKeyboard
	/// @brief �L�[�{�[�h�I��
	void FinalizeKeyboard();

	/// @fn UpdateKeyboard
	/// @brief �L�[�{�[�h�X�V
	void UpdateKeyboard();

	/// @fn InitializeJoystick
	/// @brief �W���C�X�e�B�b�N������
	/// @return �����Ftrue
	bool InitializeJoystick();

	/// @fn FinalizeJoystick
	/// @brief �W���C�X�e�B�b�N�I��
	void FinalizeJoystick();

	/// @fn UpdateJoystick
	/// @brief �W���C�X�e�B�b�N�X�V
	void UpdateJoystick();
};

#endif // SNLIB_DIRECT_INPUT8_MODULE_H_

} // namespace snlib

//EOF