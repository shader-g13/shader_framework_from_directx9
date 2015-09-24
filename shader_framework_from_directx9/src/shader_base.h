#pragma once

#include <stdio.h>
#include <crtdbg.h>
#include <d3d9.h>
#include <d3dx9.h>

class ShaderBase {
public:
	/// @brief コンストラクタ
	ShaderBase(LPDIRECT3DDEVICE9 device, char* filename) {
		FILE* fp;
		fopen_s(&fp, filename, "rb");
		_ASSERT_EXPR(fp, L"ファイル開けない");

		fseek(fp, 0, SEEK_END);
		size_t file_size = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		raw_data_ = new char[file_size];
		fread_s(raw_data_, file_size, sizeof(char), file_size, fp);
		fclose(fp);

		D3DXGetShaderConstantTable((const DWORD*)raw_data_, &constant_table_);
	}

	/// @brief デストラクタ
	virtual ~ShaderBase() {
		delete[] raw_data_;
	}

	/// @brief 定数テーブル取得
	LPD3DXCONSTANTTABLE GetConstantTable() { return constant_table_; }

protected:
	char* raw_data_;
	LPD3DXCONSTANTTABLE constant_table_;
private:
};