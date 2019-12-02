#pragma once

#include "Matrix4d.h"
#include "Vector3d.h"
#include "Quaternion.h"

class Transform
{
public:
	Transform();
	~Transform() {}
	Transform& operator=(const Transform& other);
	void Set(const Matrix4d& matrix);

	const Matrix4d GetMatrix() const;

	Vector3d	m_position;
	Quaternion	m_orientation;
	Vector3d	m_scale;
};