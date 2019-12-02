#ifndef CONSTANTBUFFERS_HLSLI
#define CONSTANTBUFFERS_HLSLI

#include "structs.hlsli"

cbuffer FrameBufferData : register(b0)
{
	matrix viewMatrix;
	matrix projectionMatrix;
	DirectionalLightData directionalLight;
	float4 cameraPos;
};

cbuffer ObjectBufferData : register(b1)
{
	matrix worldMatrix;
	matrix normalMatrix;
};

cbuffer MaterialBufferData : register(b2)
{
	float4 materialData;
};

#endif