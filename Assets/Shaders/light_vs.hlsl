#include "constantbuffers.hlsli"
#include "inputtypes.hlsli"

PixelInputType main(VertexInputType input)
{
	PixelInputType output;
	
	output.position = mul(float4(input.position, 1.0), worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	output.uv = input.uv;

	return output;
}