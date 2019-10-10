#pragma once
#include <General/Math/Matrix4d.h>

struct ObjectConstantBufferData
{
	Matrix4d	m_model;
	Matrix4d	m_modelInverseTranspose;
};