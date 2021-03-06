/// @file bump_ps.hlsl
/// @brief �o���v
/// @date 2015/09/17
/// @author syuki nishida

struct PixelIn {
  float2 tex : TEXCOORD0;
  float4 col : COLOR0;
  float3 nor : TEXCOORD1;
  float4 wpos: TEXCOORD2;
  float3 tan : TANGENT0;
  float3 bin : BINORMAL0;
};

struct OUT_PS
{
 float4 colorR : COLOR0;
 float4 colorG : COLOR1;
 float4 colorB : COLOR2;
 float4 zvalue : COLOR3;
};

sampler texture0;
sampler texture1;
sampler textureC;

float3 lightVec[4];
float3 lightPos[4];
float3 specCol[4];
float specPower[4];
float3 camPos = float3( 0,0,0 );
bool skybox = false;

OUT_PS main(PixelIn arg): COLOR0{
  
  //float4x4 tbn;
  //tbn[0] = float4(normalize(arg.tan), 0);
  //tbn[1] = float4(normalize(arg.bin), 0);
  //tbn[2] = float4(normalize(arg.nor), 0);
  //tbn[3] = float4(0, 0, 0, 1);

  //arg.nor = tex2D(texture1, arg.tex).rgb * 2 - 1;

  //mul(arg.nor, tbn);

  ////arg.nor = normalize(arg.nor);
  //float l = 0;
  //float4 color;
  //for(int i = 0;i < 4;++i)
  //{
  // float3 toEye = normalize(lightPos[i] - arg.wpos);
  //  float3 r = reflect(lightVec[i],arg.nor);
  //  float s = pow(max(dot(r,toEye),0.f),specPower[i]);
  // float d = distance(lightPos[i],arg.wpos);
  // float a0 = 0.000000000000000000000000000000000000000000000000001f;
  // float a1 = 0.02f;
  // float a2 = 0.0001f;

  // float a = a0 + a1 * d + a2 * d * d;
  // color += float4( ( l * arg.col.rgb + s * specCol[i] ) / a,1 );
  //}
  //color.a = 1;
  //if(skybox)
  //{
  // float3 toEye = normalize(camPos - arg.wpos);
  // float3 enbVec = reflect(toEye,arg.nor);
  //  return texCUBE(textureC,enbVec);
  //}
  //else{
  // float3 toEye = normalize(arg.wpos - camPos);
  //  float3 enbVec = reflect(toEye,arg.nor);
  //  return color * texCUBE(textureC,enbVec);
  //}
  //
 OUT_PS outColor = (OUT_PS)0;
 outColor.colorR = arg.col * tex2D( texture1,arg.tex );
 outColor.colorR.a = 1.0f;
 outColor.colorG.xyz = arg.nor;
 outColor.colorG.a = 1.0f;
 outColor.colorB.xyz = arg.wpos;
 outColor.colorB.a = 1.0f;
 outColor.zvalue = arg.wpos.z / arg.wpos.w;
 return outColor;
}

//EOF