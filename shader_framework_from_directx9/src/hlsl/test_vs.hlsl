
struct In {
	float3 pos : POSITION0;
  float tex : TEXCOORD0;
};

struct Out {
	float4 pos : POSITION0;
  float2 tex : TEXCOORD0;
};

float4x4 WorldMatrix;
float4x4 ViewMatrix;
float4x4 ProjectionMatrix;

Out main(In arg) {
	Out ret;

  float4x4 wvp = mul(WorldMatrix, mul(ViewMatrix, ProjectionMatrix));

    float2 texs[4];
  texs[0] = float2(0, 0);
  texs[1] = float2(1, 0);
  texs[2] = float2(0, 1);
  texs[3] = float2(1, 1);

	ret.pos = mul(float4(arg.pos, 1), wvp);
  ret.tex = texs[arg.tex];

	return ret;
}