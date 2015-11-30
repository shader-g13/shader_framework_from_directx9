

cbuffer ConstantBuffer : register( b0 )
{
 row_major matrix WorldViewProjection;
 row_major matrix NormalMtx;
 float4 LightVec;
 float4 LightCol;
}
struct StandardInputLayout {
 float4 pos : POSITION;
 float3 nor : NORMAL;
 float2 tex : TEXCOORD;
};

struct VertexOut {
 float4 pos : SV_POSITION;
 float2 tex : TEXCOORD;
 float3 nor : NORMAL;
};

VertexOut VertexShaderPolygon(StandardInputLayout arg)
{
 VertexOut ret;
	ret.pos = mul( arg.pos, WorldViewProjection );
	ret.tex = arg.tex;
 ret.nor = mul(float4( arg.nor,1 ),NormalMtx).xyz;
 ret.nor = normalize(ret.nor);
 return ret;
}

Texture2D		g_Texture : register( t0 );

SamplerState	g_SamplerState : register( s0 );


float4 PixelShaderPolygon(VertexOut arg):SV_Target
{
 float p = max(dot(normalize(arg.nor),-normalize(LightVec.xyz)),0) * 0.5f + 0.5f;
 return float4( g_Texture.Sample(g_SamplerState,arg.tex).rgb * LightCol.rgb * p,1 );
}
