#pragma once

#include "IConstantBuffer.h"

struct FrameConstantBufferData
{
	Matrix4d m_view;
	Matrix4d m_projection;
};

class FrameConstantBuffer : public IConstantBuffer
{
};