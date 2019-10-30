#pragma once

#include "Light.h"
#include <General/Math/Vector3d.h>

class DirectionalLight : public Light
{
public:
	DirectionalLight();
	DirectionalLight(const DirectionalLight& other);
	~DirectionalLight() {}

	const Vector3d& GetDirection() const { return m_direction; }
	void SetDirection(const Vector3d& direction) { m_direction = direction; }

private:
	Vector3d	m_direction;
};