sampler tex;

float4 main(float2 uv : TEXCOORD0) : COLOR0 {
	return tex2D(tex, uv);
}