#pragma once

#include <d3dx9.h>
#include <string>

class XModel {
public:
	/// @brief �R���X�g���N�^
	XModel();

	/// @brief �f�X�g���N�^
	virtual ~XModel();

	/// @brief ������
	void Initialize(LPDIRECT3DDEVICE9 device, char* filename);

	/// @brief �I��
	void Finalize();

	/// @brief �`��
	void Draw(LPDIRECT3DDEVICE9 device);

protected:
private:
	struct Material {
		D3DMATERIAL9 material;
		LPDIRECT3DTEXTURE9 texture;
	};

	LPD3DXMESH mesh_;
	DWORD material_count_;
	Material* material_;
	LPDIRECT3DVERTEXDECLARATION9 declaration_;

};