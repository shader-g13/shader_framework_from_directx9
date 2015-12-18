struct PSIn
{
 float2 texcoord:TEXCOORD0;
};

sampler texture0;

float4 main(PSIn arg):COLOR0
{
 return float4( tex2D(texture0,arg.texcoord).rgb,1 );
}