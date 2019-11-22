#include "constantbuffers.hlsli"
#include "inputtypes.hlsli"

Texture2D diffuseTexture : register(t0);
Texture2D specularTexture : register(t1);
SamplerState sampleType : register(s0);

static const float ambientStrength = 0.1;

float4 main(PixelInputType input) : SV_TARGET
{
	float4 pixelToLight = normalize(float4(pointLight[0].position, 1.0) - input.worldSpacePosition);
	float intensity = pointLight[0].intensity * clamp(dot(normalize(input.normal), pixelToLight),0,1);
	float4 textureColor = diffuseTexture.Sample(sampleType, input.uv);

	float3 ambient = textureColor.xyz * ambientStrength;
	float3 diffuse = textureColor.xyz * intensity;

	float specularStrength = specularTexture.Sample(sampleType, input.uv).x;
	float4 pixelToCamera = normalize(cameraPos - input.worldSpacePosition);
	float4 reflectDir = reflect(-pixelToLight, input.normal);
	float spec = pow(max(dot(pixelToCamera, reflectDir), 0.0), materialData.x);
	float3 specular = specularStrength * spec * pointLight[0].color.xyz * materialData.y;

	return float4(ambient + diffuse + specular, 1.0);
}