//=============================================================================
//
// ���͏���[input.cpp]
// Author : Suetsugu Kazuki
//
//=============================================================================
#include "input.h"

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************
LPDIRECTINPUT8 g_pDInput = NULL;					//
LPDIRECTINPUTDEVICE8 g_pDIDevKeyboard = NULL;
BYTE g_aKeyState[256];							//�L�[���͏��
BYTE g_keyTrigger[256];							//�L�[�g���K�[���
BYTE g_keyRelease[256];							//�L�[�����[�X���
int g_keyCounter[256];							//�L�[�J�E���^

//=============================================================================
// �L�[���͏������֐�
//=============================================================================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT	hr;

	//�_�C���N�g�C���v�b�g�I�u�W�F�N�g�쐬
	if (g_pDInput == NULL)
	{
		hr = DirectInput8Create(hInstance,
			DIRECTINPUT_VERSION,
			IID_IDirectInput8,
			(void**)&g_pDInput,
			NULL);
		if (FAILED(hr))
		{
			MessageBox(NULL, "DirectInput�I�u�W�F�N�g�̐����Ɏ��s", "FAILED", MB_OK);
			return hr;
		}
	}

	//�f�o�C�X�̍쐬
	hr = g_pDInput->CreateDevice(GUID_SysKeyboard,
		&g_pDIDevKeyboard,
		NULL);
	if (FAILED(hr))
	{
		MessageBox(NULL, "�f�o�C�X�̐����Ɏ��s", "FAILED", MB_OK);
		return hr;
	}

	//�f�[�^�t�H�[�}�b�g
	hr = g_pDIDevKeyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr))
	{
		MessageBox(NULL, "�f�[�^�t�H�[�}�b�g�Ɏ��s", "FAILED", MB_OK);
		return hr;
	}

	//�������[�h��ݒ�
	hr = g_pDIDevKeyboard->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if (FAILED(hr))
	{
		MessageBox(NULL, "�������[�h�̐ݒ�Ɏ��s", "FAILED", MB_OK);
		return hr;
	}

	for (int loop = 0; loop<256; loop++)
	{
		g_keyCounter[loop] = 0;
	}

	//�L�[�{�[�h�̃A�N�Z�X�����擾
	g_pDIDevKeyboard->Acquire();
	return	S_OK;
}
//=============================================================================
// �L�[���͉���֐�
//=============================================================================
void UninitKeyboard(void)
{
	if (g_pDInput != NULL)
	{
		g_pDInput->Release();
		g_pDInput = NULL;
	}
	if (g_pDIDevKeyboard != NULL)
	{
		//�L�[�{�[�h�̃A�N�Z�X�������
		g_pDIDevKeyboard->Unacquire();
		g_pDIDevKeyboard->Release();
		g_pDIDevKeyboard = NULL;
	}
}
//=============================================================================
// �L�[���͍X�V�֐�
//=============================================================================
void UpDateKeyboard(void)
{
	BYTE aKeyState[256];

	//�L�[�{�[�h�̏�Ԃ��擾
	if (SUCCEEDED(g_pDIDevKeyboard->GetDeviceState(sizeof(aKeyState),
		&aKeyState[0])))
	{
		for (int nCntKey = 0; nCntKey<256; nCntKey++)
		{
			//�g���K�[
			g_keyTrigger[nCntKey] = (aKeyState[nCntKey] ^ g_aKeyState[nCntKey]) & aKeyState[nCntKey];
			//�����[�X
			g_keyRelease[nCntKey] = (aKeyState[nCntKey] ^ g_aKeyState[nCntKey]) & aKeyState[nCntKey];

			g_aKeyState[nCntKey] = aKeyState[nCntKey];
		}
	}
	else
	{
		g_pDIDevKeyboard->Acquire();
	}
}
//=============================================================================
// �L�[�����֐�
//=============================================================================
bool GetKeyPress(int key)
{
	return (g_aKeyState[key] && 0x80) ? TRUE : FALSE;
}
//=============================================================================
// �L�[�g���K�[�֐�
//=============================================================================
bool GetKeyTrigger(int key)
{
	return (g_keyTrigger[key] & 0x80) ? TRUE : FALSE;
}
//=============================================================================
// �L�[�����[�X�֐�
//=============================================================================
bool GetKeyRelease(int key)
{
	return (g_keyRelease[key] & 0x80) ? TRUE : FALSE;
}
//=============================================================================
// �L�[���s�[�g�֐�
//=============================================================================
bool GetKeyRepeat(int key)
{
	if (GetKeyTrigger(key) == TRUE)
	{
		return(TRUE);
	}
	if (GetKeyPress(key) == TRUE && g_keyCounter[key]>40)
	{
		return(TRUE);
	}
	else if (GetKeyPress(key) == TRUE && g_keyCounter[key] <= 40)
	{
		g_keyCounter[key] += 1;
	}
	else
	{
		g_keyCounter[key] = 0;
	}

	return(FALSE);
}