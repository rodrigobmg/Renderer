#pragma once

#include "ILight.h"

class Light : public ILight
{
public:
	Light(LightType lightType);
	Light(const Color& color, const IGraphicsPtr& graphics, LightType lightType);
	Light(const Light& other);
	~Light() {}

	virtual void SetColor(const Color& color) override { m_color = color; }
	virtual const Color& GetColor() const override { return m_color; }
	virtual const SceneObjectPtr& GetSceneObject() const override { return m_sceneObject; }
	virtual void Render() override;
	virtual LightType GetLightType() const { return m_lightType; }

protected:
	SceneObjectPtr	m_sceneObject;
	Color			m_color;
	LightType		m_lightType;
};