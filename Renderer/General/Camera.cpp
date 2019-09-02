#include "Camera.h"

#include <General/Math/Vector4d.h>

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
	Matrix4d rotationMatrix = MatrixRotationRollPitchYawDeg(m_transform.m_rotation.m_x, m_transform.m_rotation.m_y, m_transform.m_rotation.m_z);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	lookAt = Vector4d(lookAt.m_x, lookAt.m_y, lookAt.m_z, 0.0f) * rotationMatrix;
	up = Vector4d(up.m_x, up.m_y, up.m_z, 0.0f) * rotationMatrix;

	// Translate the rotated camera position to the location of the viewer.
	lookAt = m_transform.m_position + lookAt;

	// Finally create the view matrix from the three updated vectors.
	m_viewMatrix = MatrixLookAtLH(m_transform.m_position, lookAt, up);

	return m_viewMatrix;
}
