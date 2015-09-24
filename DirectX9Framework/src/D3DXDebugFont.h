/// @file D3DXDebugFont.h
/// @brief デバッグフォント
/// @date 2015/04/18
/// @author syuki nishida

#pragma once
#ifndef SNLIB_D3DX_DEBUG_FONT_H_
#define SNLIB_D3DX_DEBUG_FONT_H_

#include <d3d9.h>
#include <d3dx9.h>
#include <map>
#include <string>
#include <functional>

/// @namespace snlib
namespace snlib {

/// @class D3DXDebugFont
class D3DXDebugFont {
public:
	/// @fn D3DXDebugFont
	/// @brief デフォルトコンストラクタ
	D3DXDebugFont();

	/// @fn Initialize
	/// @brief 初期化
	/// @return 成功：true
	bool Initialize(const LPDIRECT3DDEVICE9 device);

	/// @fn Finalize
	/// @brief 終了
	void Finalize();

	/// @fn Draw
	/// @brief 描画
	void Draw();

	/// @fn SwitchVisible
	/// @brief 表示切り替え
	__forceinline void SwitchVisible() { visible_ ^= true; }

	/// @fn IsVisible
	/// @brief 表示状況確認
	/// @return 表示中：true
	__forceinline bool IsVisible() { return visible_; }

	/// @fn SetCursor
	/// @brief カーソル移動
	/// @param[in] x X軸
	/// @param[in] y Y軸
	void SetCursor(int x, int y);

	/// @fn PrintLine
	/// @brief 文字列表示
	/// @param[in] format 書式
	/// @param[in] ... 書式に対応した変数
	void PrintLine(const char* format, ...);

	/// @fn PrintRect
	/// @brief バッファを矩形に表示
	/// @param[in] buf 表示したいバッファ
	/// @param[in] left 表示したい横の位置
	/// @param[in] top 表示したい縦の位置
	/// @param[in] width バッファの幅
	/// @param[in] height バッファの高さ
	void PrintRect(const char* buf, UCHAR left, UCHAR top, UCHAR width, UCHAR height);

	/// @fn Clear
	/// @brief 表示内容削除
	void Clear();

protected:
private:
	LPD3DXFONT font_;
	bool visible_;

	union CONSOLE_TEXT{
		char dimension1[2048];
		char dimension2[25][80];
	} console_text_;
	UCHAR cursor_x_;
	UCHAR cursor_y_;

	UCHAR font_width_;
	UCHAR font_height_;
	UCHAR buffer_width_;
	UCHAR buffer_height_;
};

} // namespace snlib

#endif // SNLIB_D3DX_DEBUG_FONT_H_

//EOF