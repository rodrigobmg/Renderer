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
	const SceneObjectPtr& GetSceneObject() const { return m_sceneObject; }
	float GetIntensity() const { return m_intensity; }
	void SetIntensity(float intensity) { m_intensity = intensity; }
	void Render();

protected:
	SceneObjectPtr	m_sceneObject;
	Color			m_color;
	float			m_intensity;
};