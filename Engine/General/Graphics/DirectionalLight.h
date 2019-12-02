#pragma once

#include "Light.h"
#include <General/Math/Quaternion.h>

class DirectionalLight : public Light
{
public:
	DirectionalLight(const Color& color, const Quaternion& orientation);
	DirectionalLight(const DirectionalLight& other);
	~DirectionalLight() {}

	const Quaternion& GetOrientation() const { return m_orientation; }
	void SetOrientation(const Quaternion& orientation) { m_orientation = orientation; }

private:
	Quaternion	m_orientation;
};