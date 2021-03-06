#include "constantbuffers.hlsli"
#include "inputtypes.hlsli"

Texture2D diffuseTexture : register(t0);
SamplerState sampleType : register(s0);

float4 main(PixelInputType input) : SV_TARGET
{
	return float4(diffuseTexture.Sample(sampleType, input.uv).xyz, 1.0);
}