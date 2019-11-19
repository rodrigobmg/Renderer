#pragma once

#include <General/Math/Color.h>

enum class LightType
{
	kDirectional,
	kPoint
};

class Light
{
public:
	Light(LightType type, const Color& color, float intensity = 1.0f);
	Light(const Light& other);
	virtual ~Light() {}

	void SetColor(const Color& color) { m_color = color; }
	const Color& GetColor() const { return m_color; }
	float GetIntensity() const { return m_intensity; }
	void SetIntensity(float intensity) { m_intensity = intensity; }

protected:
	Color			m_color;
	float			m_intensity;
	LightType		m_type;
};