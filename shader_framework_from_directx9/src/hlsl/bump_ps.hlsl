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

float3 lightVec;
float3 cameraPos;

float4 main(PixelIn arg) : COLOR0{
  
  float4x4 tbn;
  tbn[0] = float4(normalize(arg.tan), 0);
  tbn[1] = float4(normalize(arg.bin), 0);
  tbn[2] = float4(normalize(arg.nor), 0);
  tbn[3] = float4(0, 0, 0, 1);

  arg.nor = tex2D(texture1, arg.tex).rgb * 2 - 1;

  mul(arg.nor, tbn);

  //arg.nor = normalize(arg.nor);
  float l = dot(arg.nor, -lightVec) * 0.5f + 0.5f;
  float3 toEye = normalize(cameraPos - arg.wpos);
    float3 r = reflect(lightVec, arg.nor);
    float s = pow(max(dot(r, toEye), 0.f), 5);
  float d = distance(cameraPos, arg.wpos);
  float a0 = 0.0000000000000000000000000000000000000001f;
  float a1 = 0.01f;
  float a2 = 0.00001f;

  float a = a0 + a1 * d + a2 * d * d;
  return float4((l * arg.col.rgb + s * float3(1, 1, 1)) / a, 1) * tex2D(texture0, arg.tex);
}

//EOF