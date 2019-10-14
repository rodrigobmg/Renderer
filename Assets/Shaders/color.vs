#include "constantbuffers.inc"
#include "inputtypes.inc"

PixelInputType main(VertexInputType input)
{
	PixelInputType output;
	
	output.position = mul(float4(input.position, 1.0), worldMatrix);
	output.worldSpacePosition = output.position;
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	output.normal = normalize(mul(float4(input.normal, 0), normalMatrix));

	output.uv = input.uv;

	return output;
}