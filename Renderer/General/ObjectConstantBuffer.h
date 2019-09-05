#pragma once
#include <General/Matrix4d.h>

struct ObjectConstantBufferData
{
	Matrix4d	m_model;
	Matrix4d	m_modelInverseTranspose;
};