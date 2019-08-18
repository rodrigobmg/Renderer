#pragma once

#include "IConstantBuffer.h"

struct ObjectConstantBufferData
{
	Matrix4d m_model;
};

class ObjectConstantBuffer : public IConstantBuffer
{};