#pragma once
#include <General/Math/Math.h>

class Camera
{
public:
	Camera();
	Camera(const Camera& camera);
	~Camera();

	void SetPosition(float, float, float);
	void SetRotation(float, float, float);

	Vector3d GetPosition() const;
	Vector3d SetPosition() const;

	const Matrix4d& GetViewMatrix();

private:
	Matrix4d m_viewMatrix;
	float m_positionX;
	float m_positionY;
	float m_positionZ;
	float m_rotationX;
	float m_rotationY;
	float m_rotationZ;
};