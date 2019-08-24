#pragma once

#include "IPointLight.h"

class PointLight : public IPointLight
{
public:
	PointLight();
	PointLight(const Color& color, const Vector3d& position);
	PointLight(const PointLight&) = delete;
	~PointLight() {}

	virtual const Vector3d& GetPosition() const override { return m_position; }
	virtual void SetColor(const Color& color) override { m_color = color; }
	virtual const Color& GetColor() const override { return m_color; }

private:
	Color		m_color;
	Vector3d	m_position;
};