#pragma once

#include "SceneNode.h"

class PointLight;
class PointLightNode : public SceneNode
{
public:
	PointLightNode(const SharedPtr<PointLight>& pointLight, const string& name);
	~PointLightNode();

	virtual void Update();
	virtual void Render();
	const SharedPtr<PointLight>& GetLight() const { return m_pointLight; }

private:
	SharedPtr<PointLight>	m_pointLight;
};