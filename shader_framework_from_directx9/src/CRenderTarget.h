#ifndef _CRENDERTARGET_H_
#define _CRENDERTARGET_H_
#include <d3d9.h>
#include <d3dx9.h>
#include "common.h"
class CRenderTarget
{
 public:
 CRenderTarget(D3DXVECTOR2 size = D3DXVECTOR2(800,800));
 ~CRenderTarget(){};
 void Release();
 void setRenderTarget();
 const D3DXVECTOR2& surfacesize()const{ return m_surfacesize; }
 LPDIRECT3DSURFACE9 surface(){ return m_pCurTexSurface; }
 LPDIRECT3DTEXTURE9 surfacetex(){ return m_tex; }
 static void setCurRenderTarget();
 static void initRender(LPDIRECT3DDEVICE9 divice);
 private:
 LPDIRECT3DTEXTURE9 m_tex;
 LPDIRECT3DSURFACE9 m_pTexSurface;
 LPDIRECT3DSURFACE9 m_pDepthSurface;
 D3DXVECTOR2 m_surfacesize;

 static LPDIRECT3DDEVICE9	m_pD3DDevice;//デバイスのポインタ
 static LPDIRECT3DSURFACE9 m_pCurTexSurface;
 static LPDIRECT3DSURFACE9 m_pCurDepthSurface;
};

#endif // _CRENDERTARGET_H_
