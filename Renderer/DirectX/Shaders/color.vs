//Globals
cbuffer FrameBufferData
{
	matrix viewMatrix;
	matrix projectionMatrix;
};

cbuffer ObjectBufferData
{
	matrix worldMatrix;
	matrix normalMatrix;
};

//InputTypes
struct VertexInputType
{
	float4 position : POSITION;
	float4 color : COLOR;
	float4 normal : NORMAL;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float4 normal : NORMAL;
};

PixelInputType main(VertexInputType input)
{
	PixelInputType output;
	
	input.position.w = 1.0f;
	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	output.normal = mul(input.normal, normalMatrix);

	output.color = input.color;

	return output;
}