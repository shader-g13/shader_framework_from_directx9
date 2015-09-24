#pragma once

#include <d3dx9.h>
#include <string>

class XModel {
public:
	/// @brief コンストラクタ
	XModel();

	/// @brief デストラクタ
	virtual ~XModel();

	/// @brief 初期化
	void Initialize(LPDIRECT3DDEVICE9 device, char* filename);

	/// @brief 終了
	void Finalize();

	/// @brief 描画
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