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

	const Vector3d& GetPosition() const { return m_position; }
	void SetPosition(const Vector3d& position) { m_position = position; }

private:
	Vector3d	m_position;
};