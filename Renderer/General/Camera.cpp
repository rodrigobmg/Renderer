#include "stdafx.h"

#include "Camera.h"
#include <General/Vector4d.h>

Camera::Camera()
{
}

Camera::~Camera()
{
}

const Matrix4d& Camera::GetViewMatrix()
{
	using namespace Math;

	// Setup the vector that points upwards.
	Vector3d up(0.0f, 1.0f, 0.0f);

	// Setup where the camera is looking by default.
	Vector3d lookAt(0.0f, 0.0f, 1.0f);

	// Create the rotation matrix from the yaw, pitch, and roll values.
	Matrix4d rotationMatrix = MatrixRotationRollPitchYawDeg(m_transform.m_rotation.x, m_transform.m_rotation.y, m_transform.m_rotation.z);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	lookAt = Vector4d(lookAt.x, lookAt.y, lookAt.z, 0.0f) * rotationMatrix;
	up = Vector4d(up.x, up.y, up.z, 0.0f) * rotationMatrix;

	// Translate the rotated camera position to the location of the viewer.
	lookAt = m_transform.m_position + lookAt;

	// Finally create the view matrix from the three updated vectors.
	m_viewMatrix = MatrixLookAtLH(m_transform.m_position, lookAt, up);

	return m_viewMatrix;
}
