#pragma once

#include "IPointLight.h"
#include "Light.h"

#include <General/Math/Vector3d.h>
#include <General/Math/Quaternion.h>

class PointLight : public IPointLight, public Light
{
public:
	PointLight();
	PointLight(const Color& color, const Vector3d& position, const IGraphicsPtr& graphics);
	PointLight(const PointLight& other);
	~PointLight() {}

	virtual const Vector3d& GetWorldPosition() const override { return m_worldPosition; }
	virtual void SetPosition(const Vector3d& position) override;
	virtual const Quaternion& GetRotationAroundOrigin() const override { return m_rotationAroundOrigin; }
	virtual void SetRotationAroundOrigin(const Quaternion& rotation) override;

private:
	Quaternion		m_rotationAroundOrigin;
	Vector3d		m_position;
	Vector3d		m_worldPosition;
};