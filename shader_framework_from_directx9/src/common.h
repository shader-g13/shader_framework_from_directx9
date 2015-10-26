#ifndef FILE_COMMON
#define FILE_COMMON
#include <d3d9.h>
#include <d3dx9.h>

//*****************************************************************************
// マクロ定義
//*****************************************************************************
// ２Ｄポリゴン頂点フォーマット( 頂点座標[2D] / 反射光 / テクスチャ座標 )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
// ３Ｄポリゴン頂点フォーマット( 頂点座標[3D] / 法線 / 反射光 / テクスチャ座標 )
#define	FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
// 上記２Ｄポリゴン頂点フォーマットに合わせた構造体を定義
/*! @brief 180度のPI*/
#define DATA_PI ((float)3.141592654f)
/*! @brief 1度のPI*/
#define DATA_1BYPI ((float)0.318309886f)
/*! @brief 度からラジアンへ
@param[out]     degree    度を入れるとラジアンで返す
*/
#define DATAToRadian( degree ) ((degree) * (DATA_PI / 180.0f))
/*! @brief ラジアンから度へ
@param[out]     radian    ラジアンを入れると度で返す
*/
#define DATAToDegree( radian ) ((radian) * (180.0f / DATA_PI))

/*! @brief 角度を正規化する
@param[out]     rot    角度　0度以下や360度を超えたら0～360度に収める
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
/*! @brief 3軸の角度を正規化する
@param[out]     rots    角度　0度以下や360度を超えたら0～360度に収める
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

//アサート　メッセージボックス出す
//
inline void ASSERT(const char* message,const char* title = "INFO")
{
 MessageBox(nullptr,message,title,MB_OK | MB_ICONINFORMATION);
}
#endif