//Globals
struct PointLightData
{
	float4 position;
	float4 color;
};

cbuffer FrameBufferData : register(b0)
{
	matrix viewMatrix;
	matrix projectionMatrix;
	PointLightData pointLight;
};

cbuffer ObjectBufferData : register(b1)
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
	float2 uv : TEXCOORD0;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float4 normal : NORMAL;
	float4 worldSpacePosition : POSITION0;
};

PixelInputType main(VertexInputType input)
{
	PixelInputType output;
	
	input.position.w = 1.0f;
	output.position = mul(input.position, worldMatrix);
	output.worldSpacePosition = output.position;
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	output.normal = mul(input.normal, normalMatrix);

	output.color = input.color;

	return output;
}