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

 // 3���_��UV�l����w����W�ł�U���iTangent�j�y��V���iBinormal�j���Z�o
 //
 // p0, p1, p2    : ���[�J����Ԃł̒��_���W�i�|���S���`�揇�ɂ��邱�Ɓj
 // uv0, uv1, uv2 : �e���_��UV���W
 // outTangent    : U���iTangent�j�o��
 // outBinormal   : V���iBinormal�j�o��
 void CalcTangentAndBinormal(
  D3DXVECTOR3* p0,D3DXVECTOR2* uv0,
  D3DXVECTOR3* p1,D3DXVECTOR2* uv1,
  D3DXVECTOR3* p2,D3DXVECTOR2* uv2,
  D3DXVECTOR3* outTangent,D3DXVECTOR3* outBinormal
  );
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