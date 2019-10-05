#pragma once

#include "IPointLight.h"
#include <General/Vector3d.h>

class PointLight : public IPointLight
{
public:
	PointLight();
	PointLight(const Color& color, const Vector3d& position, const IGraphicsPtr& graphics);
	PointLight(const PointLight&) = delete;
	~PointLight() {}

	virtual const Vector3d& GetPosition() const override { return m_position; }
	virtual void SetPosition(const Vector3d& position) override;

	virtual void SetColor(const Color& color) override { m_color = color; }
	virtual const Color& GetColor() const override { return m_color; }
	virtual const SceneObjectPtr& GetSceneObject() const override { return m_sceneObject; }
	virtual void Render() override;

private:
	SceneObjectPtr	m_sceneObject;
	Color			m_color;
	Vector3d		m_position;
};