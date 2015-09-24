
struct In {
	float3 pos : POSITION0;
};

struct Out {
	float4 pos : POSITION0;
};

float4x4 WorldMatrix;
float4x4 ViewMatrix;
float4x4 ProjectionMatrix;

Out main(In arg) {
	Out ret;

	float4x4 wvp = mul(WorldMatrix, mul(ViewMatrix, ProjectionMatrix));

	ret.pos = mul(float4(arg.pos, 1), wvp);

	return ret;
}