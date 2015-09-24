#pragma once

#define DIRECTINPUT_VERSION (0x0800)
#include <d3dx9.h>
#include <dinput.h>
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")

//=============================================================================
//
// ���͏���[input.h]
// Author : Suetsugu kazuki
//
//=============================================================================

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);	//�L�[���͏������֐�
void UninitKeyboard(void);								//�L�[���͉���֐�
void UpDateKeyboard(void);								//�L�[���͍X�V�֐�
bool GetKeyPress(int key);								//�L�[�����֐�
bool GetKeyTrigger(int key);							//�L�[�g���K�[�֐�
bool GetKeyRelease(int key);							//�L�[�����[�X�֐�
bool GetKeyRepeat(int key);								//�L�[���s�[�g�֐�
