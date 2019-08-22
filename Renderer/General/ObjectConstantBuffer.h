#pragma once

#include "IConstantBuffer.h"

struct ObjectConstantBufferData
{
	Matrix4d	m_model;
	Matrix4d	m_modelInverseTranspose;
};

class ObjectConstantBuffer : public IConstantBuffer
{};