
#include <signal.h>
#include "CRenderTarget.h"

LPDIRECT3DSURFACE9 CRenderTarget::m_pCurTexSurface;
LPDIRECT3DSURFACE9 CRenderTarget::m_pCurDepthSurface;
LPDIRECT3DDEVICE9	CRenderTarget::m_pD3DDevice;//�f�o�C�X�̃|�C���^
void CRenderTarget::initRender(LPDIRECT3DDEVICE9 device)
{
  m_pD3DDevice = device;
  if(FAILED(m_pD3DDevice->GetDepthStencilSurface(&m_pCurDepthSurface)))
 {
  ASSERT("�T�[�t�F�X�擾���s");
 }
  if(FAILED(m_pD3DDevice->GetRenderTarget(0,&m_pCurTexSurface)))
 {
  ASSERT("�T�[�t�F�X�擾���s");
 }

}
CRenderTarget::CRenderTarget(D3DXVECTOR2 size)
{
 m_surfacesize = size;
 LPDIRECT3D9 pD3D = Direct3DCreate9(D3D_SDK_VERSION);
 D3DDISPLAYMODE d3ddm;
 // ���݂̃f�B�X�v���C���[�h���擾
 if(FAILED(pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&d3ddm)))
 {
  d3ddm.Format = D3DFMT_A8B8G8R8;
 }

 SAFE_RELEASE(pD3D);
 //�e�N�X�`���쐬
 if(FAILED(m_pD3DDevice->CreateTexture(m_surfacesize.x,m_surfacesize.y,1,D3DUSAGE_RENDERTARGET,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT,&m_tex,NULL)))
 {
  ASSERT("�e�N�X�`�����s");
 }

 if(FAILED(m_tex->GetSurfaceLevel(0,&m_pTexSurface)))
 {
  ASSERT("�T�[�t�F�X���s");
 }

 if(FAILED(m_pD3DDevice->CreateDepthStencilSurface(m_surfacesize.x,m_surfacesize.y,D3DFMT_D24S8,D3DMULTISAMPLE_NONE,0,TRUE,&m_pDepthSurface,NULL)))
 {
  ASSERT("z�o�b�t�@���s");
 }
 m_pD3DDevice->Clear(0,NULL,( D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL ),D3DCOLOR_RGBA(0,0,0,0),1.0f,0);

 if(FAILED(m_pD3DDevice->SetRenderTarget(0,m_pTexSurface)))
 {
  ASSERT("�T�[�t�F�X�؂�ւ����s");
 }
 m_pD3DDevice->Clear(0,NULL,( D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL ),D3DCOLOR_RGBA(0,0,0,0),1.0f,0);

 if(FAILED(m_pD3DDevice->SetDepthStencilSurface(m_pDepthSurface)))
 {
  ASSERT("z�o�b�t�@�؂�ւ����s");
 }
 m_pD3DDevice->Clear(0,NULL,( D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL ),D3DCOLOR_RGBA(0,0,0,0),1.0f,0);
}

void CRenderTarget::Release()
{
 SAFE_RELEASE(m_pTexSurface);
 SAFE_RELEASE(m_pDepthSurface);
 SAFE_RELEASE(m_tex);
}
void CRenderTarget::setCurRenderTarget()
{
 if(FAILED(m_pD3DDevice->SetRenderTarget(0,m_pCurTexSurface)))
 {
  ASSERT("�T�[�t�F�X�؂�ւ����s");
 }
 if(FAILED(m_pD3DDevice->SetDepthStencilSurface(m_pCurDepthSurface)))
 {
  ASSERT("z�o�b�t�@�؂�ւ����s");
 }

}
void CRenderTarget::setRenderTarget()
{
 if(FAILED(m_pD3DDevice->SetRenderTarget(0,m_pTexSurface)))
 {
  ASSERT("�T�[�t�F�X�؂�ւ����s");
 }
 m_pD3DDevice->Clear(0,NULL,( D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL ),D3DCOLOR_RGBA(0,0,0,0),1.0f,0);
 if(FAILED(m_pD3DDevice->SetDepthStencilSurface(m_pDepthSurface)))
 {
  ASSERT("z�o�b�t�@�؂�ւ����s");
 }
 m_pD3DDevice->Clear(0,NULL,( D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL ),D3DCOLOR_RGBA(0,0,0,0),1.0f,0);
}