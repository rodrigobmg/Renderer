#include "pch.h"

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
	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	Vector3d forward = Vector3d::kForward * m_transform.m_orientation;
	Vector3d up = Vector3d::kUp * m_transform.m_orientation;

	// Translate the rotated camera position to the location of the viewer.
	Vector3d lookAt = m_transform.m_position + forward;

	// Finally create the view matrix from the three updated vectors.
	m_viewMatrix = Math::MatrixLookAtLH(m_transform.m_position, lookAt, up);

	return m_viewMatrix;
}
