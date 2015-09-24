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

 // 3頂点とUV値から指定座標でのU軸（Tangent）及びV軸（Binormal）を算出
 //
 // p0, p1, p2    : ローカル空間での頂点座標（ポリゴン描画順にすること）
 // uv0, uv1, uv2 : 各頂点のUV座標
 // outTangent    : U軸（Tangent）出力
 // outBinormal   : V軸（Binormal）出力
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