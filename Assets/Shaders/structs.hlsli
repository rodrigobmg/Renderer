#ifndef STRUCTS_HLSLI
#define STRUCTS_HLSLI

struct PointLightData
{
	float4 color;
	float3 position;
	float intensity;
};

struct DirectionalLightData
{
	float4 color;
	float3 direction;
	float intensity;
};

#endif