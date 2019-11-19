#pragma once

#include <General/Math/Vector3d.h>
#include <General/Math/Quaternion.h>
#include "Light.h"

class PointLight : public Light
{
public:
	PointLight(const Color& color, const Vector3d& position);
	PointLight(const PointLight& other);
	~PointLight() {}

	const Vector3d& GetWorldPosition() const { return m_worldPosition; }
	void SetPosition(const Vector3d& position);
	const Quaternion& GetRotationAroundOrigin() const { return m_rotationAroundOrigin; }
	void SetRotationAroundOrigin(const Quaternion& rotation);

private:
	Quaternion	m_rotationAroundOrigin;
	Vector3d	m_position;
	Vector3d	m_worldPosition;
};