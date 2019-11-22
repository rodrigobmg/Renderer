#ifndef INPUTTYPES_HLSLI
#define INPUTTYPES_HLSLI

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

#endif