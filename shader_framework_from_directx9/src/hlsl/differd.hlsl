/// @author naritada suzuki

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
 OUT_PS outColor = (OUT_PS)0;
 outColor.colorR = arg.col * tex2D(texture1,arg.tex);
 outColor.colorR.a = 1.0f;
 outColor.colorG.xyz = arg.nor;
 outColor.colorG.a = 1.0f;
 outColor.colorB.xyz = arg.wpos;
 outColor.colorB.a = 1.0f;
 outColor.zvalue = arg.wpos.z / arg.wpos.w;
 return outColor;
}

//EOF