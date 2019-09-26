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
	float3 cameraPos;
};

cbuffer ObjectBufferData : register(b1)
{
	matrix worldMatrix;
	matrix normalMatrix;
};

//InputTypes
struct VertexInputType
{
	float3 position : POSITION;
	float3 normal : NORMAL;
	float2 uv : TEXCOORD;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float4 normal : NORMAL;
	float4 worldSpacePosition : POSITION0;
	float2 uv : TEXCOORD;
};

PixelInputType main(VertexInputType input)
{
	PixelInputType output;
	
	output.position = mul(float4(input.position, 1.0), worldMatrix);
	output.worldSpacePosition = output.position;
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	output.normal = mul(float4(input.normal, 0), normalMatrix);

	output.uv = input.uv;

	return output;
}