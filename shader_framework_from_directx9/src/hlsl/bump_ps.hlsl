/// @file bump_ps.hlsl
/// @brief ƒoƒ“ƒv
/// @date 2015/09/17
/// @author syuki nishida

struct PixelIn {
  float2 tex : TEXCOORD0;
  float4 col : COLOR0;
  float3 nor : TEXCOORD1;
  float3 wpos: TEXCOORD2;
  float3 norW: TEXCOORD3;
  float3 tanW: TEXCOORD4;
  float3 tan : TANGENT0;
  float3 bin : BINORMAL0;
};

sampler texture0;
sampler texture1;

float3 lightVec[3];
float3 lightPos[3];
float3 specCol[3];
float specPower[3];

float3 normalSampleToWorldSpace(float3 normalMapSample,float3 normalW,float3 tangentW)
{
 float3 normalT = normalMapSample * 2.0f - 1.0f;
  float3 N = normalW;
  float3 T = normalize(tangentW - dot(tangentW,N)*N);
  float3 B = cross(N,T);
  float3x3 TBN = float3x3(T,B,N);
  return mul(normalT,TBN);
}

float4 main(PixelIn arg) : COLOR0{
  
  float4x4 tbn;
  tbn[0] = float4(normalize(arg.tan), 0);
  tbn[1] = float4(normalize(arg.bin), 0);
  tbn[2] = float4(normalize(arg.nor), 0);
  tbn[3] = float4(0, 0, 0, 1);

  arg.nor = tex2D(texture1, arg.tex).rgb * 2 - 1;

  mul(arg.nor, tbn);
  
  float3 bumpnormalW = normalSampleToWorldSpace(tex2D(texture1,arg.tex).xyz,arg.norW,arg.tanW);

  arg.norW = normalize(arg.norW);
  float l = 0;
  float4 color;
  for(int i = 0;i < 3;++i)
  {
   float3 toEye = -lightPos[i] - arg.wpos;
    float distToEye = length(toEye);
   toEye /= distToEye;
   float3 A = 0.05f;
   float3 D = dot(-lightVec[i],bumpnormalW)*0.5f + 0.5f * 0.2f;
    float3 r = reflect(-lightVec[i],bumpnormalW);
    float s = pow(max(dot(r,toEye),0.f),specPower[i]);
   color += float4( ( l * arg.col.rgb + (A + D) + s * specCol[i] ),1 );
  }
  color.a = 1;
  return color * tex2D(texture0,arg.tex);
}

//EOF