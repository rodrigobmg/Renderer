#pragma once

#include "IConstantBuffer.h"

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

class FrameConstantBuffer : public IConstantBuffer
{
};