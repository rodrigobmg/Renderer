#pragma once

#include "IPointLight.h"

#include <General/Math/Vector3d.h>
#include <General/Math/Quaternion.h>

class PointLight : public IPointLight
{
public:
	PointLight();
	PointLight(const Color& color, const Vector3d& position, const IGraphicsPtr& graphics);
	PointLight(const PointLight&) = delete;
	~PointLight() {}

	virtual const Vector3d& GetWorldPosition() const override { return m_worldPosition; }
	virtual void SetPosition(const Vector3d& position) override;
	virtual const Quaternion& GetRotationAroundOrigin() const override { return m_rotationAroundOrigin; }
	virtual void SetRotationAroundOrigin(const Quaternion& rotation) override;

	virtual void SetColor(const Color& color) override { m_color = color; }
	virtual const Color& GetColor() const override { return m_color; }
	virtual const SceneObjectPtr& GetSceneObject() const override { return m_sceneObject; }
	virtual void Render() override;

private:
	SceneObjectPtr	m_sceneObject;
	Color			m_color;
	Quaternion		m_rotationAroundOrigin;
	Vector3d		m_position;
	Vector3d		m_worldPosition;
};