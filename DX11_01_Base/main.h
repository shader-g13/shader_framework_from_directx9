#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include <windows.h>
#include <d3d11.h>
#include <DirectXTex.h>
#include <d3dcompiler.h>
#include <SimpleMath.h>
#include <crtdbg.h>
//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************
#pragma comment (lib, "d3d11.lib")		
#pragma comment (lib, "DirectXTex.lib")	
#pragma comment (lib, "DirectXTK.lib")	
#pragma comment (lib, "d3dcompiler.lib")

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SCREEN_WIDTH	(800)			// ウインドウの幅
#define SCREEN_HEIGHT	(600)			// ウインドウの高さ


struct Vertex3D
{
    DirectX::SimpleMath::Vector3 Position;
    DirectX::SimpleMath::Vector3 Normal;
    DirectX::SimpleMath::Vector2 TexCoord;
};


struct ConstantBuffer
{
 DirectX::SimpleMath::Matrix WorldViewProjection;
 DirectX::SimpleMath::Matrix NormalMtx;
 DirectX::SimpleMath::Vector4 LightVec;
 DirectX::SimpleMath::Vector4 LightCol;

};

#endif