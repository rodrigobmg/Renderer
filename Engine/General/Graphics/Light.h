#pragma once

#include <General/Math/Color.h>

class Light
{
public:
	Light();
	Light(const Color& color, const IGraphicsPtr& graphics);
	Light(const Light& other);
	~Light() {}

	void SetColor(const Color& color) { m_color = color; }
	const Color& GetColor() const { return m_color; }
	const ScenePtr& GetScene() const { return m_scene; }
	float GetIntensity() const { return m_intensity; }
	void SetIntensity(float intensity) { m_intensity = intensity; }
	virtual void Render();

protected:
	ScenePtr	m_scene;
	Color		m_color;
	float		m_intensity;
};