/// @file specular_vs.hlsli
/// @brief スペキュラ
/// @date 2015/09/03
/// @author syuki nishida

#include <Transform.hlsli>
#include <Material.hlsli>

struct VertexIn {
  float3 pos : POSITION0;
  float3 nor : NORMAL0;
  float2 tex : TEXCOORD0;
  float3 tan : TANGENT0;
  float3 bin : BINORMAL0;
};

struct VertexOut {
  float4 pos : POSITION0;
  float2 tex : TEXCOORD0;
  float4 col : COLOR0;
  float3 nor : TEXCOORD1;
  float3 wpos: TEXCOORD2;
  float3 norL: TEXCOORD3;
  float3 tan : TANGENT0;
  float3 bin : BINORMAL0;
};
float3x3 WIT;
/// @fn main
/// @brief メイン
VertexOut main(VertexIn arg) {

  VertexOut ret;
  ret.pos = Transform(arg.pos);
  ret.nor = mul(float4( arg.nor,0.f ),GetWorldMatrix()).xyz;
  ret.norL = mul(float4( arg.nor,0.f ),GetWorldMatrix()).xyz;
  ret.wpos = mul(float4(arg.pos, 1.f), GetWorldMatrix()).xyz;
  ret.tex = arg.tex;
  ret.tan = arg.tan;
  ret.bin = arg.bin;
  ret.col = float4(GetMaterialDiffuseColor().rgb, 1);

  return ret;
}

//EOF