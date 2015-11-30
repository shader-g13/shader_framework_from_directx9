#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <windows.h>
#include <d3d11.h>
#include <DirectXTex.h>
#include <d3dcompiler.h>
#include <SimpleMath.h>
//*****************************************************************************
// ���C�u�����̃����N
//*****************************************************************************
#pragma comment (lib, "d3d11.lib")		
#pragma comment (lib, "d3dcompiler.lib")
#pragma comment (lib, "DirectXTex.lib")	
#pragma comment (lib, "DirectXTK.lib")	

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCREEN_WIDTH	(800)			// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(600)			// �E�C���h�E�̍���


struct Vertex3D
{
    DirectX::SimpleMath::Vector3 Position;
    DirectX::SimpleMath::Vector2 TexCoord;
};


struct ConstantBuffer
{
 DirectX::SimpleMath::Matrix WorldViewProjection;
};

#endif