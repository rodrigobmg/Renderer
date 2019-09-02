#pragma once
#include <General/Math/Matrix4d.h>
#include <General/Math/Vector4d.h>

struct PointLightData
{
	Vector4d	m_position;
	Vector4d	m_color;
};

struct FrameConstantBufferData
{
	Matrix4d		m_view;
	Matrix4d		m_projection;
	PointLightData	m_pointLightData;
};