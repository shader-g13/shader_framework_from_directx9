#ifndef FILE_COMMON
#define FILE_COMMON
#include <d3d9.h>
#include <d3dx9.h>

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// �Q�c�|���S�����_�t�H�[�}�b�g( ���_���W[2D] / ���ˌ� / �e�N�X�`�����W )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
// �R�c�|���S�����_�t�H�[�}�b�g( ���_���W[3D] / �@�� / ���ˌ� / �e�N�X�`�����W )
#define	FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
// ��L�Q�c�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
/*! @brief 180�x��PI*/
#define DATA_PI ((float)3.141592654f)
/*! @brief 1�x��PI*/
#define DATA_1BYPI ((float)0.318309886f)
/*! @brief �x���烉�W�A����
@param[out]     degree    �x������ƃ��W�A���ŕԂ�
*/
#define DATAToRadian( degree ) ((degree) * (DATA_PI / 180.0f))
/*! @brief ���W�A������x��
@param[out]     radian    ���W�A��������Ɠx�ŕԂ�
*/
#define DATAToDegree( radian ) ((radian) * (180.0f / DATA_PI))

/*! @brief �p�x�𐳋K������
@param[out]     rot    �p�x�@0�x�ȉ���360�x�𒴂�����0�`360�x�Ɏ��߂�
*/
template <class T>
inline void ROT_CHK(T &rot)
{
 if(rot > DATA_PI || rot < -DATA_PI)
 {
  if(rot > DATA_PI)
  {
   rot -= 2 * DATA_PI;
  }
  else
   if(rot < -DATA_PI)
   {
    rot += 2 * DATA_PI;
   }
 }
};
/*! @brief 3���̊p�x�𐳋K������
@param[out]     rots    �p�x�@0�x�ȉ���360�x�𒴂�����0�`360�x�Ɏ��߂�
*/
template <class T>
inline void ROTS_CHK(T &rot)
{
 ROT_CHK(rot.x);
 ROT_CHK(rot.y);
 ROT_CHK(rot.z);
};

template <class T>
inline void COLOR_CHK(T &p,T &s,T &a,T &b)
{
 if(s > a || s < b)
 {
  p *= -1;
 }

};

template <class T>
inline void SAFE_RELEASE(T &p)
{
 if(p)
 {
  ( p )->Release();
  ( p ) = NULL;
 }
};
template <class T>
inline void SAFE_DELETE(T &p)
{
 if(p)
 {
  delete ( p );
  ( p ) = NULL;
 }
};
template <class T>
inline void SAFE_DELETE_ARRAY(T &p)
{
 if(p)
 {
  delete[](p);
  ( p ) = NULL;
 }
};

#define SUM_INDEX(X,Z) ((X+1)*(Z-1)+((X+1)*(Z+1))+(Z-1)*2)

//�A�T�[�g�@���b�Z�[�W�{�b�N�X�o��
//
inline void ASSERT(const char* message,const char* title = "INFO")
{
 MessageBox(nullptr,message,title,MB_OK | MB_ICONINFORMATION);
}
#endif