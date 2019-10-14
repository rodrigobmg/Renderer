#include "structs.inc"

cbuffer FrameBufferData : register(b0)
{
	matrix viewMatrix;
	matrix projectionMatrix;
	PointLightData pointLight[1];
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