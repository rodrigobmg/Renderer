#pragma once

#include "IDirectionalLight.h"
#include "Light.h"

#include <General/Math/Vector3d.h>

class DirectionalLight : public IDirectionalLight, public Light
{
public:
	DirectionalLight();
	DirectionalLight(const Color& color, const Vector3d& direction, const IGraphicsPtr& graphics);
	DirectionalLight(const DirectionalLight& other);
	~DirectionalLight() {}

	virtual Vector3d GetDirection() const override { return m_direction; }

private:
	Vector3d	m_direction;
};