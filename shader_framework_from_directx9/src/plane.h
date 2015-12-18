#pragma once

#include <d3d9.h>
#include <d3dx9.h>

class Plane {
public:
	/// @brief コンストラクタ
	Plane();

	/// @brief デストラクタ
	virtual ~Plane();

	/// @brief 初期化
	void Initialize(LPDIRECT3DDEVICE9 device);

	/// @brief 終了
	void Finalize();

	/// @brief 描画
	void Draw(LPDIRECT3DDEVICE9 device);

protected:
private:
	struct VertexFormat {
		D3DXVECTOR3 pos;
  D3DXVECTOR3 nor;
		D3DCOLOR color;
  D3DXVECTOR2 texcoord;
		//float tex_index;
	};

	LPDIRECT3DVERTEXBUFFER9 vertex_;
	LPDIRECT3DVERTEXDECLARATION9 declaration_;
};