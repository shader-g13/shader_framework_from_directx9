/// @file bump_ps.hlsl
/// @brief ƒoƒ“ƒv
/// @date 2015/09/17
/// @author syuki nishida

struct PixelIn {
  float2 tex : TEXCOORD0;
  float4 col : COLOR0;
  float3 nor : TEXCOORD1;
  float3 wpos: TEXCOORD2;
  float3 tan : TANGENT0;
  float3 bin : BINORMAL0;
};

sampler texture0;
sampler texture1;

float3 lightVec[3];
float3 lightPos[3];
float3 specCol[3];
float specPower[3];

float4 main(PixelIn arg) : COLOR0{
  
  float4x4 tbn;
  tbn[0] = float4(normalize(arg.tan), 0);
  tbn[1] = float4(normalize(arg.bin), 0);
  tbn[2] = float4(normalize(arg.nor), 0);
  tbn[3] = float4(0, 0, 0, 1);

  arg.nor = tex2D(texture1, arg.tex).rgb * 2 - 1;

  mul(arg.nor, tbn);

  //arg.nor = normalize(arg.nor);
  float l = 0;
  float4 color;
  for(int i = 0;i < 3;++i)
  {
   float3 toEye = normalize(lightPos[i] - arg.wpos);
    float3 r = reflect(lightVec[i],arg.nor);
    float s = pow(max(dot(r,toEye),0.f),specPower[i]);
   float d = distance(lightPos[i],arg.wpos);
   float a0 = 0.000000000000000000000000000000000000000000000000001f;
   float a1 = 0.01f;
   float a2 = 0.00001f;

   float a = a0 + a1 * d + a2 * d * d;
   color += float4( ( l * arg.col.rgb + s * specCol[i] ) / a,1 );
  }
  color.a = 1;
  return color * tex2D(texture0,arg.tex);
}

//EOF