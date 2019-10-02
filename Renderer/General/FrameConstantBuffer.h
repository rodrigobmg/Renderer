#pragma once
#include <General/Matrix4d.h>
#include <General/Vector4d.h>
#include <General/Vector3d.h>

struct PointLightData
{
	Vector4d	m_position;
	Vector4d	m_color;
};

static const int kNumPointLights = 1;
struct FrameConstantBufferData
{
	Matrix4d		m_view;
	Matrix4d		m_projection;
	PointLightData	m_pointLightData[kNumPointLights];
	Vector4d		m_cameraPosition;
};