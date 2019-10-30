#pragma once
#include <General/Math/Matrix4d.h>
#include <General/Math/Vector4d.h>
#include <General/Math/Vector3d.h>

struct PointLightData
{
	Vector4d	m_color;
	Vector3d	m_position;
	float		m_intensity;
};

static const int kNumPointLights = 1;
struct FrameConstantBufferData
{
	Matrix4d		m_view;
	Matrix4d		m_projection;
	PointLightData	m_pointLightData[kNumPointLights];
	Vector4d		m_cameraPosition;
};