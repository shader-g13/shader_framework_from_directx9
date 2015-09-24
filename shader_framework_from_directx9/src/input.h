#pragma once

#define DIRECTINPUT_VERSION (0x0800)
#include <d3dx9.h>
#include <dinput.h>
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")

//=============================================================================
//
// 入力処理[input.h]
// Author : Suetsugu kazuki
//
//=============================================================================

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);	//キー入力初期化関数
void UninitKeyboard(void);								//キー入力解放関数
void UpDateKeyboard(void);								//キー入力更新関数
bool GetKeyPress(int key);								//キー押下関数
bool GetKeyTrigger(int key);							//キートリガー関数
bool GetKeyRelease(int key);							//キーリリース関数
bool GetKeyRepeat(int key);								//キーリピート関数
