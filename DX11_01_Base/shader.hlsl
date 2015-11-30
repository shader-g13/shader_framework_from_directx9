

cbuffer ConstantBuffer : register( b0 )
{
	matrix WorldViewProjection;
}


void VertexShaderPolygon( in  float4 inPosition : POSITION0,
						  in  float2 inTexCoord : TEXCOORD0,
						  out float4 outPosition : SV_POSITION,
						  out float2 outTexCoord : TEXCOORD0 )
{
	outPosition = mul( inPosition, WorldViewProjection );
	outTexCoord = inTexCoord;
}



Texture2D		g_Texture : register( t0 );
SamplerState	g_SamplerState : register( s0 );


void PixelShaderPolygon( in  float4 inPosition : POSITION0,
						 in  float2 inTexCoord : TEXCOORD0,
						 out float4 outDiffuse : SV_Target )
{
    outDiffuse = g_Texture.Sample( g_SamplerState, inTexCoord );
}
