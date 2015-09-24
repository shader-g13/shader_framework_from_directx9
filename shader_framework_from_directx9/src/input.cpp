//=============================================================================
//
// 入力処理[input.cpp]
// Author : Suetsugu Kazuki
//
//=============================================================================
#include "input.h"

//*****************************************************************************
// グローバル変数:
//*****************************************************************************
LPDIRECTINPUT8 g_pDInput = NULL;					//
LPDIRECTINPUTDEVICE8 g_pDIDevKeyboard = NULL;
BYTE g_aKeyState[256];							//キー入力情報
BYTE g_keyTrigger[256];							//キートリガー情報
BYTE g_keyRelease[256];							//キーリリース情報
int g_keyCounter[256];							//キーカウンタ

//=============================================================================
// キー入力初期化関数
//=============================================================================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT	hr;

	//ダイレクトインプットオブジェクト作成
	if (g_pDInput == NULL)
	{
		hr = DirectInput8Create(hInstance,
			DIRECTINPUT_VERSION,
			IID_IDirectInput8,
			(void**)&g_pDInput,
			NULL);
		if (FAILED(hr))
		{
			MessageBox(NULL, "DirectInputオブジェクトの生成に失敗", "FAILED", MB_OK);
			return hr;
		}
	}

	//デバイスの作成
	hr = g_pDInput->CreateDevice(GUID_SysKeyboard,
		&g_pDIDevKeyboard,
		NULL);
	if (FAILED(hr))
	{
		MessageBox(NULL, "デバイスの生成に失敗", "FAILED", MB_OK);
		return hr;
	}

	//データフォーマット
	hr = g_pDIDevKeyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr))
	{
		MessageBox(NULL, "データフォーマットに失敗", "FAILED", MB_OK);
		return hr;
	}

	//強調モードを設定
	hr = g_pDIDevKeyboard->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if (FAILED(hr))
	{
		MessageBox(NULL, "強調モードの設定に失敗", "FAILED", MB_OK);
		return hr;
	}

	for (int loop = 0; loop<256; loop++)
	{
		g_keyCounter[loop] = 0;
	}

	//キーボードのアクセス権を取得
	g_pDIDevKeyboard->Acquire();
	return	S_OK;
}
//=============================================================================
// キー入力解放関数
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
		//キーボードのアクセス権を解放
		g_pDIDevKeyboard->Unacquire();
		g_pDIDevKeyboard->Release();
		g_pDIDevKeyboard = NULL;
	}
}
//=============================================================================
// キー入力更新関数
//=============================================================================
void UpDateKeyboard(void)
{
	BYTE aKeyState[256];

	//キーボードの状態を取得
	if (SUCCEEDED(g_pDIDevKeyboard->GetDeviceState(sizeof(aKeyState),
		&aKeyState[0])))
	{
		for (int nCntKey = 0; nCntKey<256; nCntKey++)
		{
			//トリガー
			g_keyTrigger[nCntKey] = (aKeyState[nCntKey] ^ g_aKeyState[nCntKey]) & aKeyState[nCntKey];
			//リリース
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
// キー押下関数
//=============================================================================
bool GetKeyPress(int key)
{
	return (g_aKeyState[key] && 0x80) ? TRUE : FALSE;
}
//=============================================================================
// キートリガー関数
//=============================================================================
bool GetKeyTrigger(int key)
{
	return (g_keyTrigger[key] & 0x80) ? TRUE : FALSE;
}
//=============================================================================
// キーリリース関数
//=============================================================================
bool GetKeyRelease(int key)
{
	return (g_keyRelease[key] & 0x80) ? TRUE : FALSE;
}
//=============================================================================
// キーリピート関数
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